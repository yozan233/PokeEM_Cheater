#!/usr/bin/env python3
"""Generate build/resource_text.c from src/resource_text.json."""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path
from typing import Any


ROOT = Path(__file__).resolve().parent
CHARMAP_PATH = ROOT / "charmap.txt"
DEFAULT_INPUT_PATH = ROOT / "src" / "resource_text.json"
DEFAULT_OUTPUT_PATH = ROOT / "build" / "resource_text.c"
DEFAULT_HEADER_PATH = ROOT / "build" / "resource_text.h"

SUPPORTED_VERSIONS = {"BPEE0", "BPRE0", "AXVE0"}

RESOURCE_ORDER = (
    "textButtonPrompt1",
    "textButtonPrompt2",
    "textButtonPrompt3",
    "textButtonPrompt4",
    "textMon",
    "textBag",
    "textOther",
    "textLevel",
    "textNatures",
    "textAbility",
    "textHappiness",
    "textShiny",
    "textGender",
    "textSure",
    "textCancel",
    "textUnknownAbility",
    "textNotShiny",
    "textGenderTable",
    "textHP",
    "textAttack",
    "textDefense",
    "textSpeed",
    "textSPAttack",
    "textSPDefense",
    "textIV",
    "textEV",
    "textMovePower",
    "textMoveType",
    "textMoveAccuracy",
    "textPP",
    "textNone",
    "textQuantity",
    "textAddItem",
    "textThrowKeyItem",
    "textCircleDot",
    "textAddSuccess",
    "textInsufficientSpace",
    "textEgg",
    "textHatchNow",
    "textPokedexUpgrade",
    "textPokerus",
    "textMirageShow",
    "textThroughWall",
    "textVisualRangeMax",
    "textSpray",
    "textlimit510",
    "textPageLock",
    "textDelete",
    "textInitials",
    "textBallType",
    "textCatchLocation",
    "textTeleport",
    "textComingSoon",
    "textSomewhere",
    "textFatefulEncounter",
    "textFlightPoint",
    "textTime",
    "textHour",
    "textMonCopy",
    "textCopySuccess",
    "textSendToPC",
    "textCopyFailed",
    "textMonObedience",
    "textVersion",
    "exit_text",
)


def load_charmap(path: Path) -> dict[str, bytes]:
    if not path.is_file():
        raise ValueError(f"charmap file was not found: {path}")

    mapping: dict[str, bytes] = {}
    with path.open("r", encoding="utf-8-sig") as charmap_file:
        for line_number, source_line in enumerate(charmap_file, start=1):
            line = source_line.rstrip("\r\n")
            if not line or "=" not in line:
                continue
            encoded_text, token = line.split("=", 1)
            if re.fullmatch(r"(?:[0-9A-Fa-f]{2})+", encoded_text) is None:
                raise ValueError(
                    f"invalid charmap code at line {line_number}: {encoded_text!r}"
                )
            encoded = bytes.fromhex(encoded_text)
            previous = mapping.get(token)
            if previous is not None and previous != encoded:
                raise ValueError(
                    f"duplicate charmap token at line {line_number}: {token!r}"
                )
            mapping[token] = encoded
    return mapping


def load_text_config(path: Path) -> dict[str, Any]:
    if not path.is_file():
        raise ValueError(f"text resource file was not found: {path}")
    with path.open("r", encoding="utf-8-sig") as config_file:
        data = json.load(config_file)
    if not isinstance(data, dict):
        raise ValueError("text resource root must be a JSON object")
    return data


def require_object(value: Any, description: str) -> dict[str, Any]:
    if not isinstance(value, dict):
        raise ValueError(f"{description} must be a JSON object")
    return value


def encode_text(
    text: str,
    mapping: dict[str, bytes],
) -> bytes:
    tokens_by_first: dict[str, list[tuple[str, bytes]]] = {}
    for token, encoded in mapping.items():
        if token:
            tokens_by_first.setdefault(token[0], []).append((token, encoded))
    for candidates in tokens_by_first.values():
        candidates.sort(key=lambda entry: len(entry[0]), reverse=True)

    output = bytearray()
    offset = 0
    while offset < len(text):
        candidates = tokens_by_first.get(text[offset], ())
        for token, encoded in candidates:
            if text.startswith(token, offset):
                output.extend(encoded)
                offset += len(token)
                break
        else:
            raise ValueError(
                f"no character encoding for {text[offset]!r} at offset {offset} in {text!r}"
            )
    return bytes(output)


def encode_resource(
    name: str,
    value: Any,
    mapping: dict[str, bytes],
) -> bytes:
    if not isinstance(value, str):
        raise ValueError(f"{name} must be a string")
    return encode_text(value, mapping)


def collect_resources(
    config: dict[str, Any],
    version: str,
    language: str,
) -> dict[str, Any]:
    version_texts = require_object(config.get("textVersion"), "textVersion")
    version_text = version_texts.get(version)
    if not isinstance(version_text, str):
        raise ValueError(f"textVersion.{version} must be a string")

    language_config = require_object(config.get(language), language)
    language_versions = require_object(
        language_config.get("versions"), f"{language}.versions"
    )

    sections = (
        ("textVersion", {"textVersion": version_text}),
        (
            f"{language}.common",
            require_object(language_config.get("common"), f"{language}.common"),
        ),
        (
            f"{language}.versions.{version}",
            require_object(
                language_versions.get(version), f"{language}.versions.{version}"
            ),
        ),
    )

    resources: dict[str, Any] = {}
    for section_name, section in sections:
        for name, value in section.items():
            if name in resources:
                raise ValueError(f"duplicate resource {name!r} in {section_name}")
            resources[name] = value

    expected = set(RESOURCE_ORDER)
    actual = set(resources)
    missing = sorted(expected - actual)
    extra = sorted(actual - expected)
    if missing or extra:
        details = []
        if missing:
            details.append("missing: " + ", ".join(missing))
        if extra:
            details.append("unknown: " + ", ".join(extra))
        raise ValueError("invalid resource set; " + "; ".join(details))
    return resources


def format_c_array(name: str, data: bytes) -> str:
    rows = []
    for offset in range(0, len(data), 16):
        values = ", ".join(f"0x{value:02X}" for value in data[offset : offset + 16])
        rows.append(f"    {values},")
    return f"const u8 {name}[] = {{\n" + "\n".join(rows) + "\n};"


def calculate_crc(data: bytes) -> int:
    crc = 0x1121
    for value in data:
        crc ^= value
        for _ in range(8):
            if crc & 1:
                crc = (crc >> 1) ^ 0x8408
            else:
                crc >>= 1
    return (~crc) & 0xFFFF


def atomic_write_text(path: Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temp_path = path.with_name(f".{path.name}.tmp")
    with temp_path.open("w", encoding="utf-8", newline="\n") as output_file:
        output_file.write(content)
    temp_path.replace(path)


def generate(
    version: str,
    language: str,
    input_path: Path,
    output_path: Path,
    header_path: Path,
) -> None:
    mapping = load_charmap(CHARMAP_PATH)
    config = load_text_config(input_path)
    resources = collect_resources(config, version, language)

    language_name = "English" if language == "en" else "Chinese"
    blocks = [
        "typedef unsigned char u8;",
        "",
        f"// Generated by build_text.py for {version} ({language_name}). Do not edit.",
        "",
    ]
    version_crc = None
    version_length = None
    for name in RESOURCE_ORDER:
        data = encode_resource(name, resources[name], mapping)
        if name == "textVersion":
            data = bytes(value ^ 0xAB for value in data)
            version_crc = calculate_crc(data)
            version_length = len(data)
        blocks.append(format_c_array(name, data) + "\n")

    if version_crc is None or version_length is None:
        raise ValueError("textVersion was not generated")

    header = "\n".join(
        (
            "#ifndef POKEEM_CHEATER_RESOURCE_TEXT_H",
            "#define POKEEM_CHEATER_RESOURCE_TEXT_H",
            "",
            f"#define VERSION_TEXT_LENGTH {version_length}",
            f"#define CRC_VERSION_TEXT 0x{version_crc:04X}",
            "",
            "#endif",
            "",
        )
    )
    atomic_write_text(output_path, "\n".join(blocks))
    atomic_write_text(header_path, header)


def resolve_path(path_text: str) -> Path:
    path = Path(path_text)
    return path if path.is_absolute() else ROOT / path


def create_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--version", required=True, choices=sorted(SUPPORTED_VERSIONS))
    parser.add_argument("--language", required=True, choices=("zh", "en"))
    parser.add_argument("--input", default=str(DEFAULT_INPUT_PATH))
    parser.add_argument("--output", default=str(DEFAULT_OUTPUT_PATH))
    parser.add_argument("--header-output", default=str(DEFAULT_HEADER_PATH))
    return parser


def main() -> int:
    args = create_parser().parse_args()
    try:
        generate(
            args.version,
            args.language,
            resolve_path(args.input),
            resolve_path(args.output),
            resolve_path(args.header_output),
        )
    except (OSError, ValueError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
