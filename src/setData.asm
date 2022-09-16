.thumb @make the assembler assemble it in thumb
.global setData @make it a global function
.thumb_func @make the assembler know that the function is in thumb

.equ script_text_buffer2, 0x02021DC4
.equ script_text_buffer3, 0x02021EC4
@;.equ pokemon_getattr, 0x0806A519
@;.equ myDiv, 0x08F2EACD
setData:
	push {r4-r7,lr}
	ldr r7, =script_text_buffer3
	
	add r7, #0x8
	ldr r0, =0x0804A5BE
	ldrb r0, [r0]
	strb r0, [r7]
	
	add r7, #0x8
	
	pokemonData:
	mov r0, #0x0 @;PID
	bl getattr
	str r0, [r7,#0x10]
	mov r5, r0
	mov r0, #0x1 @;SID
	bl getattr
	str r0, [r7,#0x14]
	mov r0, #0x2D @;isEgg
	bl getattr
	strb r0, [r7,#0x1]
	mov r0, #0xB @;种族
	bl getattr
	strh r0, [r7,#0x2]
	@;性别
	ldr r3, =0x080001BC
	ldr r3, [r3]
	mov r1, #0x1C
	mul r0, r1
	add r0, r3
	add r0, #0x10
	ldrb r0, [r0]
	ldrb r1, [r7,#0x10]
	mov r2, #0x2 @;isXY
	cmp r0, #0xFF
	beq isNotSex
	cmp r0, #0xFE
	beq isAllXX
	cmp r0, #0x0
	beq isAllXY
	cmp r1, r0
	bgt ctniu
	mov r2, #0x1 @;isXX
	b ctniu
	isNotSex:
	mov r2, #0x4
	b ctniu
	isAllXX:
	mov r2, #0x3
	b ctniu
	isAllXY:
	mov r2, #0x0
	b ctniu
	
	ctniu:
	strb r2, [r7,#0x9]
	mov r0, #0x38 @;等级
	bl getattr
	strb r0, [r7,#0x4]
	mov r0, r5 @;性格
	mov r1, #25
	ldr r3, =umodsi3
	bl BX_R3
	strb r0, [r7,#0x5]
	mov r0, #0x2E @;特性
	bl getattr
	strb r0, [r7,#0x6]
	mov r0, #0x20 @;亲密度
	bl getattr
	strb r0, [r7,#0x7]
	@;闪光
	ldrh r0, [r7,#0x10]
	ldrh r1, [r7,#0x12]
	eor r0, r1
	ldrh r1, [r7,#0x14]
	ldrh r2, [r7,#0x16]
	eor r1, r2
	eor r0, r1
	mov r1, #0x0
	cmp r0, #0x8
	bgt notShan
	mov r1, #0x1
	notShan:
	strb r1, [r7,#0x8]
	
	setImg:
	ldr r2, =0x020375E0
	ldrb  r1, [r2,#0x6]
	mov r2, #0x44
	mul r1, r2
	ldr r2, =0x02020630
	add r1, r2
	ldrb r0, [r1,#0x5]
	mov r3, #0xF
	and r0, r3
	ldr r3, =script_text_buffer3
	ldrh r3, [r3,#0x12]
	ldr r2, =0x8000138
	ldr r2, [r2,#0x4]
	add r2, r3
	ldrb r2, [r2]
	add r2, #0x1
	ldrb r5, [r7,#0x1]
	cmp r5, #1
	bne notegg
	mov r2, #2
	notegg:
	lsl r2, #0x4
	add r0, r2
	strb r0, [r1,#0x5]
	ldrb r0, [r7,#0x1]
	cmp r0, #1
	beq load_icon_egg
	ldrh r0, [r7,#0x2]
	cmp r0, #0
	beq end0

	load_icon_image:
	ldr r1, =0x8000138
	ldr r1, [r1]
	mov r2, #0x4
	mul r2, r0
	add r2, r1
	ldr r0 ,[r2]
	ldr r1, =0x06010400
	ldr r2, =0x200
	swi #0xB
	b end0

	load_icon_egg:
	ldr r0, =0x08d8fc74
	ldr r1, =0x06010400
	ldr r2, =0x200
	swi #0xB
	
	end0:
	
	mov r0, r7
	mov r1, r7
	add r1, #0x20
	mov r2, #0x6
	swi #0xB
	
	@;精灵昵称
	ldr r0, =script_text_buffer3
	ldrb r0, [r0,#0x10]
	ldr r1, =party_player @;0x020244EC
	mov r2, #0x64
	mul r0,r2
	add r1,r0
	add r1, #0x8
	ldr r0, =script_text_buffer2
	ldr r3, =strcpy_xFF_terminated @;0x08008BA1
	bl BX_R3
	ldr r0, =script_text_buffer2
	mov r1, #0xFF
	strb r1, [r0,#0xA] @;防止溢出
	ldr r0, =script_text_buffer2
	not_FFx:
	add r0, #0x1
	ldrb r2, [r0]
	cmp r2, #0xFF
	bne not_FFx
	mov r1, #0xBA
	strb r1, [r0]
	add r0, #0x1
	mov r5, r0
	ldr r0, =script_text_buffer3
	ldrh r0, [r0,#0x12]
	ldr r3, =0x08000144
	ldr r3, [r3]
	mov r2, #0xB
	mul r2, r0
	add r3, r2
	mov r0, r5
	mov r1, r3
	ldr r3, =strcpy_xFF_terminated @;0x08008BA1
	bl BX_R3
	
	pop {r4-r7,pc}

getattr:
	push {lr}
	mov r3, r0
	ldr r2, =script_text_buffer3
	add r2, #0x10
	ldrb r2, [r2]
	mov r0, #0x64
	mul r2, r0
	ldr r0, =party_player @;0x020244EC
	add r0, r2
	mov r1, r3
	ldr r3, =pokemon_getattr
	bl BX_R3
	pop {pc}

BX_R3:
	bx r3


