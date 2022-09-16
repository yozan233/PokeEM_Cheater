.thumb @make the assembler assemble it in thumb
.global exit_asm @make it a global function
.thumb_func @make the assembler know that the function is in thumb

@;.equ KWDZ, 0x0820BAE0
@;text_EXIT = KWDZ+2C
exit_asm:

Main0:
	push {r4, lr}
	ldr r4, =0x0809FD65
	bl BX_R4
	bl Main
	pop {r4, pc}

BX_R4:
	bx r4

Main:
	push {r0-r3, lr}
	ldr r0, =script_adress
	ldr r3, =0x08098EF9
	bl BX_R3
	pop {r0-r3, pc}

BX_R3:
	bx r3

.align 2
script_adress:
.byte 0x97,01,0x23
.word main_func+1
.byte 0x02

/*
fadescreen 0x1
callasm main
end

*/