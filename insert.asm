.gba
.thumb
.create "test.gba",0x8000000
.close
.open "bpee0.gba","test.gba", 0x8000000

.org 0x808AF0C
ldr r1, =Chuan+1
bx r1
.pool
.org 0x8510578
.word exit_text
.org 0x851057C
.word exit_asm+1
.org 0x809FB8C
.word exit_asm+1

//这里填所用的空位地址
.org 0x8F20000
.pool
.importobj "build/linked.o"
.close