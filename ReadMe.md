# PokeEM_Cheater

## 编译并运行
1. 将devkitPro\devkitARM\bin目录添加到PATH环境变量
2. 将armips.exe路径添加到PATH环境变量
3. 在insert_BPEE.asm中设置要使用的空位地址
4. 将英文绿宝石gba文件放到此项目的根目录下，并改名为`BPEE0.gba`
5. 在文件资源管理器的地址栏中输入cmd打开命令行，输入`make bpee0`并回车
6. 生成的`BPEE_TEST.gba`，即为输出的ROM
7. 进入游戏打开菜单，选择作弊选项即可

## 生成bin文件和info文件
### 绿宝石
```shell
make -f makefilecmp bpee0
```
### 火红
```shell
make -f makefilecmp bpre0
```
### 红宝石
```shell
make -f makefilecmp axve0
```


