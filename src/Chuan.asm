.thumb @make the assembler assemble it in thumb
.global Chuan @make it a global function
.thumb_func @make the assembler know that the function is in thumb

@;穿墙：
@;0B31B4 | 00 49 08 47 [ASM+1]
	Chuan:
	ldr r1, =throughWallFlag
	ldrb r1, [r1]
	cmp r1, #0
	beq this_end
	mov r0, #0

	this_end:
    mov sp, r7
    add sp, #0xC

	ldr r1, =CheckForPlayerAvatarCollision
	add r1, #0x88

BX_R1:
	bx r1

.pool

@;填充字节，方便以后代码扩展
.word 0
.word 0
.word 0
.word 0

