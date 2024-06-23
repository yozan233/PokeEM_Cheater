import sys

# 使用步骤
# 1. makefile注释掉'python CheaterBinFileTest.py'
# 2. insert.asm填写空位地址【0x8F20000】，开始编译
# 3. 复制一份编译后的gba文件和ld文件
# 4. 当前文件填写buffer_size和version变量，gba_file1.seek()参数改为【0xFB0000】，解开makefile里的注释
# 5. insert.asm填写空位地址【0x8FB0000】，开始编译，编译成功后得到空位地址偏移数据
# 6. insert.asm改回空位地址【0x8F20000】，当前文件gba_file1.seek()参数改回【0xF20000】
# 7. 根据info_cheater.txt逐行修改ld文件里的函数地址（修改从左往右数第二个字节），开始编译，编译成功后得到改函数地址偏移数据

# 版本列表
BPEE0 = "BPEE0"  # 绿宝石
BPRE0 = "BPRE0"  # 火红
AXVE0 = "AXVE0"  # 红宝石


def find_fun_data_offset():
    buffer_size = 0x57b4
    base_path = "D:/Sundries/Pokemom/Pokemon_C/PokeEM_Cheater/"

    version = BPEE0

    gba_file_name1 = version + "_TEST.gba"
    gba_file_name2 = version + "_TEST - 副本.gba"
    ld_file_name1 = version + ".ld"
    ld_file_name2 = version + " - 副本.ld"

    try:
        print("开始查找-------")

        with open(base_path + ld_file_name1, 'r', encoding='utf-8') as ld_file1, \
                open(base_path + ld_file_name2, 'r', encoding='utf-8') as ld_file2:
            for line1, line2 in zip(ld_file1, ld_file2):
                if line1 != line2:
                    sys.stdout.write(line2)
                    break

        with open(base_path + gba_file_name1, 'rb') as gba_file1, \
                open(base_path + gba_file_name2, 'rb') as gba_file2:

            gba_file1.seek(0xF20000)
            gba_file2.seek(0xF20000)

            buffer1 = gba_file1.read(buffer_size)
            buffer2 = gba_file2.read(buffer_size)

            len1 = len(buffer1)
            len2 = len(buffer2)

            comma = ""

            for i in range(min(len1, len2)):
                if buffer1[i] != buffer2[i]:
                    sys.stdout.write(f"{comma}0x{hex(i - 2)[2:].upper()}")
                    comma = ","

        print("\n查找结束-------")

    except Exception as e:
        print(e)


if __name__ == '__main__':
    find_fun_data_offset()
