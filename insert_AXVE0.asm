.gba
.thumb
.create "AXVE0_TEST.gba",0x8000000
.close
.open "AXVE0.gba","AXVE0_TEST.gba", 0x8000000

PlayerNotOnBikeMovingHook equ PlayerNotOnBikeMoving+0xB
gText_MenuExitPtr equ sStartMenuItems+0x38
StartMenuExitCallbackPtr equ sStartMenuItems+0x3C
StartMenuExitCallbackPtr2 equ HandleStartMenuInput+0xBF

.org PlayerNotOnBikeMovingHook
ldr r1, =Chuan+1
bx r1
.pool

.org gText_MenuExitPtr
.word exit_text
.org StartMenuExitCallbackPtr
.word exit_asm+1
.org StartMenuExitCallbackPtr2
.word exit_asm+1


/* 这里填所用的ROM空位地址 */
.org 0x8FC0000
.pool
.importobj "build/linked.o"
.close

