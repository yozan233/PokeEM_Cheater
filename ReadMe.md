# PokeEM_Cheater

## 环境依赖

1. Python 3.9 或更高版本。
2. GNU Make。
3. 将 `devkitPro/devkitARM/bin` 添加到 `PATH`。
4. 将 `armips` 添加到 `PATH`。

构建流程不再需要任何真实 ROM。`build.py` 会在缺少 `EMPTY.gba` 时自动生成一份 32 MiB、全部填充为 `0xFF` 的空 ROM。

## 生成 bin 和 info 文件

### 绿宝石

```shell
python build.py
```

也可以明确指定版本：

```shell
python build.py bpee0
```

### 火红／叶绿公共资源

```shell
python build.py bpre0
```

### 红宝石／蓝宝石公共资源

```shell
python build.py axve0
```

生成结果位于 `inner_cheater_bin`：

- `cheater_EMERALD.bin` 和 `info_cheater_EMERALD.txt`
- `cheater_FIRE_RED.bin` 和 `info_cheater_FIRE_RED.txt`
- `cheater_RUBY.bin` 和 `info_cheater_RUBY.txt`

## 配置和临时文件

- `rom_offsets.json` 保存全部版本的 ROM 符号地址。
- `build.py` 是唯一对外构建入口，它在内部调用 `makefile` 完成编译、链接和 armips。
- `rom_offsets.ld` 和 `insert.asm` 由 `build.py` 自动生成。
- 构建会分别在 `0x08F20000` 和 `0x08FC0000` 插入代码，再比较两份结果、生成重定位信息。
- `BPGE0` 和 `AXPE0` 偏移仍保留在 JSON 中，但不是正式发布目标，不会覆盖 FIRE_RED 或 RUBY 公共资源。

## 清理

```shell
python build.py clean
```

该命令只删除 `build`、`rom_offsets.ld` 和 `insert.asm`，不会删除 `EMPTY.gba` 或正式生成的 bin/info 文件。
