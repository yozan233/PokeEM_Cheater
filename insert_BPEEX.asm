.gba
.thumb
.create "BPEEX_TEST.gba",0x8000000
.close
.open "BPEEX.gba","BPEEX_TEST.gba", 0x8000000


PlayerNotOnBikeMovingHook equ CheckForPlayerAvatarCollision+0x7F

.org PlayerNotOnBikeMovingHook
ldr r1, =Chuan+1
bx r1
.pool


.org ItemUseOutOfBattle_Potion_Type
.byte 0x02
.org ItemUseOutOfBattle_Potion_Ptr
.word ItemUseOutOfBattle_Cheater+1

.org ItemUseOutOfBattle_Wristband_Type
.byte 0x02
.org ItemUseOutOfBattle_Wristband_Ptr
.word ItemUseOutOfBattle_Cheater+1


/* 这里填所用的ROM空位地址 */
.org 0x9A70000
.pool
.importobj "build/linked.o"
.close


