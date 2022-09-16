.thumb @make the assembler assemble it in thumb
.global obj_callback @make it a global function
.thumb_func @make the assembler know that the function is in thumb

obj_callback:
	push {lr}
	ldr r3, RtcCalcLocalTime
	bl BX_R3_objcb
	ldr r3, var_8004
	ldrb r3, [r3,#0x6] @;r3=obj_id
	ldr r0, objects
	mov r1, #0x44
	mul r1, r3
	add r3, r0,r1 @;r3=obj数据地址
	
	ldr r0, game_time
	mov r1, #0xF
	ldrb r0, [r0]
	and r0, r1
	ldrb r1, [r3,#0x4]
	cmp r0, #0xC
	beq bisC
	cmp r0, #0x4
	beq bis4
	b last
bis4:
	mov r1, #0x20
	b last
bisC:
	add r1, #0x10
last:
	strb r1, [r3,#0x4]
	pop {pc}
BX_R3_objcb:
	bx r3

.align 2
var_8004:
	.word 0x020375E0
objects:
	.word 0x02020630
game_time:
	.word 0x030022E0
RtcCalcLocalTime:
	.word 0x0802f588|1
	