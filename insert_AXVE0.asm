.gba
.thumb
.create "test_rb.gba",0x8000000
.close
.open "axve0.gba","test_rb.gba", 0x8000000

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


//DEFINE YOUR FREE OFFSET HERE 1845A80
.org 0x8F20000
.pool
.importobj "build/linked.o"
.close

