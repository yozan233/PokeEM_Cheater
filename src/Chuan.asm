.thumb @make the assembler assemble it in thumb
.global Chuan @make it a global function
.thumb_func @make the assembler know that the function is in thumb

@;穿墙：
@;08AF0C | 00 49 08 47 [ASM+1]
	Chuan:
	ldr r1, =0x020322d6
	ldrb r1, [r1]
	cmp r1, #0
	beq notChang
	mov r0, #0
	b this_end
	notChang:
	ldr r3, =0x0808AFBD
	bl BX_R3
	
	this_end:
	lsl r0, r0,#0x18
	lsr r4, r0,#0x18
	ldr r3, =0x0808AF15
	
BX_R3:
	bx r3
	