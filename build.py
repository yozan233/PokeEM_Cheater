#!/usr/bin/env python3
"""Generate and package the built-in cheat binary assets."""

from __future__ import annotations

import argparse
import json
import re
import struct
import subprocess
import sys
from pathlib import Path
from typing import Any, Optional


ROOT = Path(__file__).resolve().parent
CONFIG_PATH = ROOT / "rom_offsets.json"
LINKER_OUTPUT_PATH = ROOT / "rom_offsets.ld"
ASM_OUTPUT_PATH = ROOT / "insert.asm"
EMPTY_ROM_PATH = ROOT / "EMPTY.gba"
OUTPUT_DIR = ROOT / "inner_cheater_bin"

ROM_BASE = 0x08000000
EMPTY_ROM_SIZE = 32 * 1024 * 1024
EMPTY_ROM_CHUNK = b"\xFF" * (1024 * 1024)

MAP_SYMBOLS = (
    "gNameLengthConfig",
    "gQuantityLimit",
    "gDataSizeConfig",
    "exit_text",
    "main_func",
    "ItemUseOutOfBattle_Cheater",
    "Chuan",
)
REQUIRED_MAP_SYMBOLS = {
    "gNameLengthConfig",
    "gQuantityLimit",
    "exit_text",
    "main_func",
    "Chuan",
}

MAKE = "make"

BUILD_TARGETS = {
    "BPEE0": ("BPEE0", "EMERALD", False),
    "BPEU0": ("BPEE0", "EMERALD_US", True),
    "BPRE0": ("BPRE0", "FIRE_RED", False),
    "BPRU0": ("BPRE0", "FIRE_RED_US", True),
    "AXVE0": ("AXVE0", "RUBY", False),
    "AXVU0": ("AXVE0", "RUBY_US", True),
}

VERSION_RE = re.compile(r"^[A-Z0-9_]+$")
SYMBOL_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
ADDRESS_RE = re.compile(r"^0[xX][0-9A-Fa-f]{1,8}$")
TEXT_SECTION_RE = re.compile(
    r"^\s*\.text\s+0x0*8000000\s+0x([0-9A-Fa-f]+)\b",
    re.IGNORECASE,
)
MAP_SYMBOL_RE = re.compile(
    r"^\s*0x([0-9A-Fa-f]+)\s+([A-Za-z_][A-Za-z0-9_]*)\s*$"
)


class BuildError(RuntimeError):
    pass


def reject_duplicate_keys(pairs: list[tuple[str, Any]]) -> dict[str, Any]:
    result: dict[str, Any] = {}
    for key, value in pairs:
        if key in result:
            raise BuildError(f"duplicate key in rom_offsets.json: {key}")
        result[key] = value
    return result


def parse_address(value: str, label: str) -> int:
    if not isinstance(value, str) or ADDRESS_RE.fullmatch(value) is None:
        raise BuildError(f"{label} must be a hexadecimal string such as 0x08000000")
    return int(value, 16)


def load_version(version: str) -> dict[str, Any]:
    if VERSION_RE.fullmatch(version) is None:
        raise BuildError(f"invalid version name: {version}")

    with CONFIG_PATH.open("r", encoding="utf-8") as config_file:
        config = json.load(config_file, object_pairs_hook=reject_duplicate_keys)

    if not isinstance(config, dict):
        raise BuildError("rom_offsets.json must contain a top-level object")
    if "versions" in config:
        raise BuildError("rom_offsets.json must not contain a top-level 'versions' object")

    version_config = config.get(version)
    if not isinstance(version_config, dict):
        supported = ", ".join(config.keys())
        raise BuildError(f"unknown version {version}; supported versions: {supported}")

    project = version_config.get("project")
    publish = version_config.get("publish")
    defines = version_config.get("defines")
    symbols = version_config.get("symbols")
    if not isinstance(project, str) or not project:
        raise BuildError(f"{version}.project must be a non-empty string")
    if not isinstance(publish, bool):
        raise BuildError(f"{version}.publish must be a boolean")
    if not isinstance(defines, list):
        raise BuildError(f"{version}.defines must be an array")
    for define in defines:
        if not isinstance(define, str) or SYMBOL_RE.fullmatch(define) is None:
            raise BuildError(f"invalid compiler define in {version}: {define!r}")
    if not isinstance(symbols, dict) or not symbols:
        raise BuildError(f"{version}.symbols must be a non-empty object")

    for name, symbol in symbols.items():
        if not isinstance(name, str) or SYMBOL_RE.fullmatch(name) is None:
            raise BuildError(f"invalid linker symbol name in {version}: {name!r}")
        if not isinstance(symbol, dict):
            raise BuildError(f"{version}.{name} must be an object")
        parse_address(symbol.get("address"), f"{version}.{name}.address")
        if not isinstance(symbol.get("thumb"), bool):
            raise BuildError(f"{version}.{name}.thumb must be a boolean")
        note = symbol.get("note")
        if note is not None:
            if not isinstance(note, str) or "\n" in note or "\r" in note or "*/" in note:
                raise BuildError(f"{version}.{name}.note is not a valid one-line comment")

    return version_config


def atomic_write_text(path: Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temp_path = path.with_name(f".{path.name}.tmp")
    with temp_path.open("w", encoding="utf-8", newline="\n") as output_file:
        output_file.write(content)
    temp_path.replace(path)


def atomic_write_bytes(path: Path, content: bytes) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temp_path = path.with_name(f".{path.name}.tmp")
    temp_path.write_bytes(content)
    temp_path.replace(path)


def ensure_empty_rom() -> None:
    if EMPTY_ROM_PATH.exists():
        if EMPTY_ROM_PATH.stat().st_size != EMPTY_ROM_SIZE:
            raise BuildError(
                f"{EMPTY_ROM_PATH.name} must be exactly {EMPTY_ROM_SIZE} bytes"
            )
        with EMPTY_ROM_PATH.open("rb") as rom_file:
            while True:
                chunk = rom_file.read(len(EMPTY_ROM_CHUNK))
                if not chunk:
                    break
                if chunk != EMPTY_ROM_CHUNK[: len(chunk)]:
                    raise BuildError(f"{EMPTY_ROM_PATH.name} must contain only 0xFF bytes")
        return

    temp_path = EMPTY_ROM_PATH.with_name(f".{EMPTY_ROM_PATH.name}.tmp")
    with temp_path.open("wb") as rom_file:
        for _ in range(EMPTY_ROM_SIZE // len(EMPTY_ROM_CHUNK)):
            rom_file.write(EMPTY_ROM_CHUNK)
    temp_path.replace(EMPTY_ROM_PATH)


def prepare(version: str) -> None:
    version_config = load_version(version)
    ensure_empty_rom()
    lines = [f"/* Generated by build.py for {version}. Do not edit. */"]
    for name, symbol in version_config["symbols"].items():
        value = symbol["address"]
        if symbol["thumb"]:
            value += "|1"
        line = f"{name} = {value};"
        note = symbol.get("note")
        if note:
            line += f" /* {note} */"
        lines.append(line)

    atomic_write_text(LINKER_OUTPUT_PATH, "\n".join(lines) + "\n")


def resolve_path(value: str) -> Path:
    path = Path(value)
    return path if path.is_absolute() else ROOT / path


def asm_path(value: str) -> str:
    if '"' in value or "\n" in value or "\r" in value:
        raise BuildError(f"invalid armips path: {value!r}")
    return value.replace("\\", "/")


def render(version: str, insert_address_text: str, output_rom_text: str) -> None:
    load_version(version)
    insert_address = parse_address(insert_address_text, "insert address")
    if not ROM_BASE <= insert_address < ROM_BASE + EMPTY_ROM_SIZE:
        raise BuildError("insert address is outside the 32 MiB GBA ROM range")

    ensure_empty_rom()
    output_rom = resolve_path(output_rom_text)
    output_rom.parent.mkdir(parents=True, exist_ok=True)
    if output_rom.resolve() == EMPTY_ROM_PATH.resolve():
        raise BuildError("the armips output must not overwrite EMPTY.gba")

    output_value = asm_path(output_rom_text)
    lines = [
        ".gba",
        ".thumb",
        f'.create "{output_value}", 0x{ROM_BASE:08X}',
        ".close",
        f'.open "{EMPTY_ROM_PATH.name}", "{output_value}", 0x{ROM_BASE:08X}',
        "",
        f".org 0x{insert_address:08X}",
        ".pool",
        '.importobj "build/linked.o"',
        ".close",
        "",
    ]
    atomic_write_text(ASM_OUTPUT_PATH, "\n".join(lines))


def read_map(map_path: Path) -> tuple[int, dict[str, int]]:
    text_size: Optional[int] = None
    symbol_addresses: dict[str, int] = {}
    needed_symbols = set(MAP_SYMBOLS)

    with map_path.open("r", encoding="utf-8", errors="replace") as map_file:
        for line in map_file:
            if text_size is None:
                section_match = TEXT_SECTION_RE.match(line)
                if section_match:
                    text_size = int(section_match.group(1), 16)

            symbol_match = MAP_SYMBOL_RE.match(line)
            if symbol_match:
                name = symbol_match.group(2)
                if name in needed_symbols:
                    symbol_addresses[name] = int(symbol_match.group(1), 16)

    if text_size is None or text_size <= 0:
        raise BuildError(f"could not read the .text size from {map_path}")
    missing = sorted(REQUIRED_MAP_SYMBOLS - symbol_addresses.keys())
    if missing:
        raise BuildError(f"missing required symbols in {map_path}: {', '.join(missing)}")
    return text_size, symbol_addresses


def read_payload(rom_path: Path, insert_address: int, size: int) -> bytes:
    offset = insert_address - ROM_BASE
    if offset < 0 or offset + size > EMPTY_ROM_SIZE:
        raise BuildError(f"payload range is outside the GBA ROM: {rom_path}")
    if rom_path.stat().st_size != EMPTY_ROM_SIZE:
        raise BuildError(f"temporary ROM has an unexpected size: {rom_path}")

    with rom_path.open("rb") as rom_file:
        rom_file.seek(offset)
        payload = rom_file.read(size)
    if len(payload) != size:
        raise BuildError(f"could not read the complete payload from {rom_path}")
    return payload


def hex_value(value: int) -> str:
    return f"0x{value & 0xFFFFFFFF:X}"


def package(
    version: str,
    output_project: str,
    map_text: str,
    f2_rom_text: str,
    fc_rom_text: str,
) -> None:
    version_config = load_version(version)
    if not version_config["publish"]:
        raise BuildError(f"{version} is available for linking but is not a publish version")

    map_path = resolve_path(map_text)
    f2_rom_path = resolve_path(f2_rom_text)
    fc_rom_path = resolve_path(fc_rom_text)
    text_size, map_symbols = read_map(map_path)
    f2_payload = read_payload(f2_rom_path, 0x08F20000, text_size)
    fc_payload = read_payload(fc_rom_path, 0x08FC0000, text_size)

    rom_space_offsets = [
        index - 2
        for index, (fc_byte, f2_byte) in enumerate(zip(fc_payload, f2_payload))
        if fc_byte != f2_byte
    ]

    symbols = version_config["symbols"]
    address_to_name: dict[int, str] = {}
    for name, symbol in symbols.items():
        value = parse_address(symbol["address"], f"{version}.{name}.address")
        if symbol["thumb"]:
            value += 1
        address_to_name.setdefault(value, name)

    reference_offsets: dict[str, list[int]] = {}
    for offset in range(max(0, text_size - 3)):
        value = struct.unpack_from("<I", f2_payload, offset)[0]
        name = address_to_name.get(value)
        if name is not None:
            reference_offsets.setdefault(name, []).append(offset)

    lines = [
        "Size",
        hex_value(text_size),
        "",
        "RomSpace",
        ",".join(hex_value(offset) for offset in rom_space_offsets),
    ]

    for name in MAP_SYMBOLS:
        address = map_symbols.get(name)
        if address is None:
            continue
        lines.extend(("", name, hex_value(address - ROM_BASE)))

    for name, symbol in symbols.items():
        offsets = reference_offsets.get(name)
        if not offsets:
            continue
        address = parse_address(symbol["address"], f"{version}.{name}.address")
        lines.extend(
            (
                "",
                f"{name}={hex_value(address)}",
                ",".join(hex_value(offset) for offset in offsets),
            )
        )

    info_path = OUTPUT_DIR / f"info_cheater_{output_project}.txt"
    bin_path = OUTPUT_DIR / f"cheater_{output_project}.bin"
    atomic_write_text(info_path, "\n".join(lines) + "\n")
    atomic_write_bytes(bin_path, f2_payload)

    f2_rom_path.unlink()
    fc_rom_path.unlink()


def run_command(arguments: list[str]) -> None:
    display_command = subprocess.list2cmdline(arguments)
    print(f"> {display_command}")
    try:
        result = subprocess.run(arguments, cwd=ROOT, check=False)
    except FileNotFoundError as error:
        raise BuildError(f"required tool was not found: {arguments[0]}") from error
    if result.returncode != 0:
        raise BuildError(
            f"command exited with status {result.returncode}: {display_command}"
        )


def compile_project(target: str) -> None:
    build_target = BUILD_TARGETS.get(target)
    if build_target is None:
        choices = ", ".join(BUILD_TARGETS)
        raise BuildError(f"unknown build target {target}; expected one of: {choices}")

    version, output_project, english_resource = build_target
    version_config = load_version(version)
    if not version_config["publish"]:
        raise BuildError(f"{version} is available for linking but is not a publish version")

    prepare(version)
    run_command(
        [
            sys.executable,
            "build_text.py",
            "--version",
            version,
            "--language",
            "en" if english_resource else "zh",
            "--output",
            "build/resource_text.c",
            "--header-output",
            "build/resource_text.h",
        ]
    )
    defines = list(version_config["defines"])
    if english_resource:
        defines.append("ENGLISH_RESOURCE")
    defines_text = " ".join(defines)
    map_file = f"build/{target}.map"
    run_command(
        [
            MAKE,
            "-f",
            "makefile",
            f"GAME_VERSION={version}",
            f"DEFINES={defines_text}",
            f"MAP_FILE={map_file}",
            "link",
        ]
    )

    f2_rom = f"build/{target}_0x08F20000.gba"
    fc_rom = f"build/{target}_0x08FC0000.gba"
    render(version, "0x08F20000", f2_rom)
    run_command([MAKE, "-f", "makefile", "armips"])
    render(version, "0x08FC0000", fc_rom)
    run_command([MAKE, "-f", "makefile", "armips"])
    package(version, output_project, map_file, f2_rom, fc_rom)
    print(f"Generated cheater_{output_project}.bin and its info file.")


def clean() -> None:
    run_command([MAKE, "-f", "makefile", "clean"])


def create_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "target",
        nargs="?",
        default="BPEE0",
        help=(
            "build target (BPEE0, BPEU0, BPRE0, BPRU0, AXVE0, AXVU0) "
            "or all/clean; default: BPEE0"
        ),
    )
    return parser


def main() -> int:
    target = create_parser().parse_args().target.upper()
    try:
        if target == "CLEAN":
            clean()
        elif target == "ALL":
            for build_target in BUILD_TARGETS:
                compile_project(build_target)
        else:
            compile_project(target)
    except (BuildError, OSError, json.JSONDecodeError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
