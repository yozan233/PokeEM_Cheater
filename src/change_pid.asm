.thumb @make the assembler assemble it in thumb
.global change_pid @make it a global function
.thumb_func @make the assembler know that the function is in thumb

.equ script_text_buffer3_a40, 0x02021EC4+0x40
//change_pi(pokeID,nature,sex,shininess)
change_pid:
	push {r4-r7, lr}
	mov r5, r9
	mov r7, r11
	mov r6, r10
	mov r4, r8
	push {r4-r7}
	mov r5, #0x64
	@ldr r3, [pc, 170h]    ;[00FF0D50]=0x08FF0EF0(150933232)
	ldr r1, =0x02021EC4
	ldrb r2, [r1, #0x10]
	lsl r3, r2, #0
	mul r3, r5
	ldr r5, =0x020244EC
	add r5, r3, r5
	ldrh r3, [r1, #0x12]
	lsl r2, r3, #0x0
	sub sp, #0x2C
	ldrb r7, [r1, #0x15]
	str r3, [sp, #0x14]
	ldr r3, =0x080001BC
	ldr r0, [r3]
	lsl r3, r2, #0
	lsl r2, r2, #3
	sub r3, r2, r3
	lsl r3, r3, #2
	add r3, r0, r3
	ldrb r3, [r3, #0x10]
	mov r2, #0
	mov r9, r3
	ldr r3, [r1, #0x20]
	lsl r3, r3, #0x18
	lsr r3, r3, #0x18
	mov r10, r2
	cmp r3, r9
	bcs G_FF0C1A
	mov r3, #0xFE
	mov r10, r3
G_FF0C1A:
	ldr r3, [r1, #0x24]
	str r3, [sp, #0x10]
	ldrb r3, [r1, #0x18]
	cmp r3, #1
	bne G_FF0C26
	b G8FF0D40
G_FF0C26:
	ldr r3, =0x082E7BE1
	mov r8, r3
	mov r3, #0xFF
	mov r11, r3
	ldr r6, =0x0806F5CD
G8FF0C30:
	bl BX_R6
	lsl r4, r0, #0
	bl BX_R6
	lsl r0, r0, #0x10
	orr r4, r0
	mov r1, #0x19
	lsl r0, r4, #0
	bl BX_R8
	cmp r0, r7
	bne G8FF0C30
	mov r3, r11
	mov r2, #0
	and r3, r4
	cmp r9, r3
	bls G8FF0C56
	add r2, #0xFE
G8FF0C56:
	cmp r2, r10
	bne G8FF0C30
	b check_802_pid
G8FF0C5A:
	ldr r3, =0x08000B39
	mov r0, #0x64
	bl BX_R3
	ldr r3, =0x08067A8D
	lsl r6, r0, #0
	bl BX_R3
	mov r2, #0
	mov r1, #0x38
	lsl r0, r5, #0
	ldr r7, =0x0806A519
	bl BX_R7
	ldr r3, [sp, #0x10]
	str r3, [sp, #0xC]
	mov r3, #1
	lsl r2, r0, #0x18
	str r3, [sp, #0x8]
	str r4, [sp, #0x4]
	str r3, [sp, #0x0]
	ldr r4, =0x08067B4D
	lsr r2, r2, #0x18
	ldr r1, [sp, #0x14]
	lsl r0, r6, #0
	bl BX_R4
	ldr r3, =0x0806ACAD
	mov r8, r3
	mov r3, #0
	mov r4, #0xA
	mov r10, r3
G8FF0C9A:
	mov r3, #0
	mov r9, r3
	mov r3, r10
	lsl r1, r4, #0
	mov r2, #0
	lsl r0, r5, #0
	str r3, [sp, #0x1C]
	bl BX_R7
	lsl r1, r4, #0
	add r4, #1
	str r0, [sp, #0x1C]
	add r2, sp, #0x1C
	lsl r0, r6, #0
	lsl r4, r4, #0x18
	bl BX_R8
	lsr r4, r4, #0x18
	cmp r4, #0x51
	bne G8FF0C9A
	mov r3, r9
	mov r2, #0
	mov r1, #3
	lsl r0, r5, #0
	str r3, [sp, #0x18]
	bl BX_R7
	add r2, sp, #0x18
	str r0, [sp, #0x18]
	mov r1, #3
	lsl r0, r6, #0
	bl BX_R8
	mov r3, r9
	mov r2, #0x0
	mov r1, #0x8
	lsl r0, r5, #0x0
	str r3, [sp, #0x18]
	bl BX_R7
	add r2, sp, #0x18
	str r0, [sp, #0x18]
	mov r1, #0x8
	lsl r0, r6, #0x0
	bl BX_R8
	add r2, sp, #0x1C
	mov r1, #0x2
	lsl r0, r5, #0x0
	bl BX_R7
	add r2, sp, #0x1C
	lsl r0, r6, #0x0
	mov r1, #0x2
	bl BX_R8
	add r2, sp, #0x1C
	mov r1, #0x7
	lsl r0, r5, #0x0
	bl BX_R7
	add r2, sp, #0x1C
	lsl r0, r6, #0x0
	mov r1, #0x7
	bl BX_R8
	mov r2, #0x64
	lsl r1, r6, #0x0
	lsl r0, r5, #0x0
	ldr r3, =0x082E93D5
	bl BX_R3
	lsl r0, r6, #0x0
	ldr r3, =0x08000B61
	bl BX_R3

	change_pid_end0:
	add sp, #0x2C
	pop {r2-r5}
	mov r8, r2
	mov r9, r3
	mov r10, r4
	mov r11, r5
	pop {r4-r7, pc}
G8FF0D40:
	ldr r3, [sp, #0x10]
	mov r2, r9
	mov r1, r10
	lsl r0, r7, #0x0
	bl create_shiny_pid
	lsl r4, r0, #0x0

	check_802_pid:
	ldr r1, =0x080001BC
	ldr r1, [r1]
	ldr r2, =0x08F186E0
	cmp r1, r2
	bne nomal_Emerald
	str r4, [r5]
	ldr r1, =0x02021EC4
	ldr r1, [r1, #0x24]
	str r1, [r5,#4]
	b change_pid_end0

	nomal_Emerald:
	b G8FF0C5A

	
	
create_shiny_pid:
	push {r4-r7, lr}
	mov r4, r8
	mov r7, r11
	mov r6, r10
	mov r5, r9	
	push {r4-r7}
	sub sp, #0xC
	str r0, [sp]
	lsr r0, r3, #0x10
	eor r3, r0
	ldr r0, =0x0000FFF8
	and r3, r0
	lsl r4, r3, #0x0
	ldr r3, =0x0806F5CD @;rng
	mov r11, r1
	str r2, [sp, #0x4]
	mov r9, r3
	bl BX_R3
	ldr r3, =0x082E7BE1 @;__umodsi3
	mov r1, #0x8
	bl BX_R3
	orr r0, r4
	lsl r0, r0, #0x10
	lsr r3, r0, #0x10
	mov r10, r3
	mov r3, #0x1
	mov r8, r3
G08FF1022:
	mov r6, #0x0
	mov r3, r10
	mov r5, #0x0
	mov r10, r6
	mov r7, #0x0
	lsl r6, r3, #0x0
	b G08FF103C
G08FF1030:
	cmp r0, #0x0
	beq G08FF1056
	orr r7, r4
G08FF1036:
	add r5, #0x1
	cmp r5, #0x10
	beq G08FF1062
G08FF103C:
	mov r4, r8
	lsl r4, r5
	bl BX_R9
	mov r3, r8
@	lsl r4, r4, #0x10
@	lsr r4, r4, #0x10
	and r0, r3
	tst r4, r6
	bne G08FF1030
	cmp r0, #0x0
	beq G08FF1036
	orr r7, r4
G08FF1056:
	mov r3, r10
	add r5, #0x1
	orr r3, r4
	mov r10, r3
	cmp r5, #0x10
	bne G08FF103C
G08FF1062:
	lsl r3, r6, #0x0
	mov r6, r10
	mov r10, r3
	bl BX_R9
	mov r3, r8
	tst r3, r0
	beq G08FF10A4
	ldr r3, [sp]
	lsl r6, r6, #0x10
	orr r7, r6
	cmp r3, #0x19
	bls G08FF10AE
G08FF107C:
	mov r3, r11
	cmp r3, #0xFF
	beq G08FF1094
	mov r3, #0xFF
	ldr r1, [sp, #0x4]
	and r3, r7
	mov r2, #0xFE
	cmp r3, r1
	sbc r3, r3
	and r2, r3
	cmp r2, r11
	bne G08FF1022
G08FF1094:
	lsl r0, r7, #0x0
	add sp, #0xC
	pop {r2-r5}
	mov r8, r2
	mov r9, r3
	mov r10, r4
	mov r11, r5
	pop {r4-r7, pc}
G08FF10A4:
	ldr r3, [sp]
	lsl r7, r7, #0x10
	orr r7, r6
	cmp r3, #0x19
	bhi G08FF107C
G08FF10AE:
	ldr r3, =0x082E7BE1 @;__umodsi3
	mov r1, #0x19
	lsl r0, r7, #0x0
	bl BX_R3
	ldr r3, [sp]
	cmp r3, r0
	bne G08FF1022
	b G08FF107C


BX_R3:
	bx r3
BX_R4:
	bx r4
BX_R6:
	bx r6
BX_R7:
	bx r7
BX_R8:
	bx r8
BX_R9:
	bx r9
/*
#dynamic 0xE00000

#org @1
lockall
msgbox @2 0x2
setvar 0x8004 0x0//队伍中精灵编号
setvar 0x8005 0x0//性格编号
setvar 0x8006 0xFF//性别，FF保持当前状态
setvar 0x8007 0x1//闪光
callasm 0xASM地址+1
releaseall
end

#org @2
= 2333
*/

