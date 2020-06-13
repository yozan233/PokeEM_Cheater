.thumb
.global mouse_color
.global set_att
.global get_party_offset
.global pause
.global chck_PID
.global showpokepic
.global showicon
.global checkNmae
.global set_poke_dex
.global get_pos
.global check_pos
.global del_last_keyitem
.global check_802
.global check_Ultra_Emerald
.global party_max
.global reset_IVs_buffer
.global select_set_p
.global setvar
.global set_bingdu
.global shiye
.global check_pw

.thumb_func


.equ buffer3, 0x02021EC4
.equ set_attributesa, 0x0806ACAD
.equ party_playergt, 0x020244EC
.equ obj_objs, 0x02020630
.equ poke_na_802, 0x08000144

mouse_color:
	push {lr}
	ldr r2, =0x02037D14 @OBJ_PaletteMem2
	add r2, #0x16
	ldrb r0, [r2]
	mov r1, #0x46
	cmp r0, r1
	beq color_red
	strb r1, [r2]
	mov r1, #0x65
	strb r1, [r2,#0x1]
	b color_end
	color_red:
	mov r1, #0x9F
	strb r1, [r2]
	mov r1, #0x10
	strb r1, [r2,#0x1]
	color_end:
	pop {pc}

set_att:
	push {r4-r5,lr}
	ldr r5, =buffer3
	ldrb r1, [r5]
	cmp r1,#0x1
	beq mode1
	cmp r1,#0x2
	beq mode2or3
	cmp r1,#0x3
	beq mode2or3
	b endx
mode1:
	bl get_party
	ldrb r1, [r5,#0x14]
	mov r3, r5
	add r3, #0x34
	ldrb r3, [r3]
	cmp r1, r3
	beq notChangelvl
	ldr r3, =0x081D642D @set_poke_to_lvl
	bl BX_R3
notChangelvl:
	ldrb r1, [r5,#0x16]
	mov r2, r5
	add r2, #0x28
	strh r1, [r2]
	mov r0, #0x2E
	bl setattr
	ldrb r1, [r5,#0x17]
	mov r2, r5
	add r2, #0x28
	strh r1, [r2]
	mov r0, #0x20
	bl setattr
	b endx
mode2or3:
	sub r1, #0x2
	add r5, #0x1A
	mov r2, #0xD
	mov r4, #0x27
	mul r2, r1
	sub r4, r2
return1:
	mov r0, r4
	ldrb r1, [r5]
	ldr r2, =buffer3
	add r2, #0x28
	strh r1, [r2]
	bl setattr
	add r4, #0x1
	add r5, #0x1
	ldr r0, =buffer3
	add r0, #0x20
	cmp r5, r0
	bne return1
	endx:
	pop {r4-r5,pc}
setattr:
	push {lr}
	mov r3, r0
	bl get_party
	mov r1, r3
	ldr r3, =set_attributesa
	bl BX_R3
	pop {pc}


get_party_offset:
	get_party:
	push {lr}
	ldr r1, =buffer3
	add r1, #0x10
	ldrb r1, [r1]
	mov r0, #0x64
	mul r1, r0
	ldr r0, =party_playergt
	add r0, r1
	pop {pc}


pause:
	push {lr}
	mov r1, #0xFF
	lsl r1, #0xA
	pause_t:
	add r0, #0x1
	cmp r0, r1
	bne pause_t
	pop {pc}

chck_PID:
	push {lr}
	ldr r3, =buffer3
	mov r2, r3
	add r2, #0x10
	add r3, #0x30
	ldrb r0, [r2,#0x9]
	ldrb r1, [r3,#0x9]
	cmp r0, r1
	bne G_PID
	ldrb r0, [r2,#0x5]
	ldrb r1, [r3,#0x5]
	cmp r0, r1
	bne changePID
	ldrb r0, [r2,#0x8]
	ldrb r1, [r3,#0x8]
	cmp r0, r1
	bne changePID
	mov r0, #0x0
	b notChange
G_PID:
	ldrh r0, [r3,#0x2]
	ldr r2, =0x080001BC @basestat_table_pid
	ldr r2, [r2]
	mov r1, #0x1C
	mul r0, r1
	add r0, r2
	add r0, #0x10
	ldrb r0, [r0]
	ldrb r1, [r3,#0x9]
	cmp r1, #0x1
	beq gXY
	cmp r1, #0x2
	beq gXY
	b changePID
gXY:
	sub r0, #0x5
	cmp r1, #0x2
	beq isXX
	add r0, #0xA
isXX:
	sub r3, #0x10
	strb r0, [r3]
changePID:
	ldr r3, =buffer3
	mov r2, r3
	add r2, #0x10
	add r3, #0x40
	mov r0, #0xFF
	strh r0, [r3,#0x4]
	ldrb r0, [r2,#0x5]
	strh r0, [r3,#0x2]
	ldrb r0, [r2,#0x8]
	strh r0, [r3,#0x6]
	ldrb r0, [r2]
	strh r0, [r3]
	mov r0, #0x1
notChange:
	pop {pc}

showpokepic:
	push {lr}
	ldr r2, =buffer3
	ldrb  r1, [r2,#0xA]
	mov r2, #0x44
	mul r1, r2
	ldr r2, =obj_objs
	add r1, r2
	strb r0, [r1,#0x1]
	pop {pc}

showicon:
	push {lr}
	ldr r2, =0x020375E0 @v8004icon
	ldrb  r1, [r2,#0x6]
	mov r2, #0x44
	mul r1, r2
	ldr r2, =obj_objs
	add r1, r2
	strb r0, [r1,#0x1]
	pop {pc}

checkNmae:
	push {r4-r5,lr}
	ldr r0, buffer2_changeName
	mov r1, #0x1
	ctnChck:
	add r0, r1
	ldrb r2, [r0]
	cmp r2, #0xBA
	bne ctnChck
	mov r1, #0xFF
	strb r1, [r0]
	add r0, #0x1
	ldr r1, buffer2_changeName
	ldr r3, strcmp
	bl BX_R3
	cmp r0, #0x0
	bne end_changeName
	ldr r0, =buffer3
	ldrb r0, [r0,#0x10]
	ldr r1, =party_playergt
	mov r2, #0x64
	mul r0,r2
	add r1,r0 @;r1精灵昵称地址
	add r1, #0x8
	ldr r0, =buffer3
	ldrh r0, [r0,#0x2C]
	ldr r3, =poke_na_802
	ldr r3, [r3]
	mov r2, #0xB
	mul r0, r2
	add r0, r3
	@mov r2, #0x5
	@swi #0Xb
	mov r3, #0x0
	strbr1:
	ldrb r2, [r0,r3]
	strb r2, [r1,r3]
	add r3, #0x1
	cmp r3,#0xB
	bne strbr1
end_changeName:
	pop {r4-r5,pc}
.align 2
buffer2_changeName:
	.word 0x02021DC4
strcmp:
	.word 0x8008C45

set_poke_dex:
	push {r4,lr}
	ldr r3, get_pokedex_num
	bl BX_R3
	mov r4, r0
	mov r1, #0x2
	ldr r3, get_or_set_pokedex_flags
	bl BX_R3
	mov r0, r4
	mov r1, #0x3
	ldr r3, get_or_set_pokedex_flags
	bl BX_R3
	pop {r4,pc}
.align 2
get_or_set_pokedex_flags:
	.word 0x080C0665
get_pokedex_num:
	.word 0x0806D4A5

get_pos:
	push {lr}
	ldr r1, =obj_objs
	ldr r0, [r1,#0x20]
	ldr r1, =buffer3
	str r0, [r1,#0xC]
	pop {pc}

check_pos:
	push {lr}
	ldr r1, =obj_objs
	ldr r1, [r1,#0x20]
	ldr r2, =buffer3
	ldr r2, [r2,#0xC]
	mov r0, #0x1
	cmp r1, r2
	bne poscend
	mov r0, #0x0
poscend:
	pop {pc}

del_last_keyitem:
	push {lr}
	ldr r3, =0x02039DD8+0x20 @item_sav
	ldr r0, [r3]
	ldrh r1, [r3,#0x4]
	mov r3, #0x0
item_check:
	lsl r2, r3,#0x2
	add r2, r0
	ldrh r2, [r2]
	cmp r2, #0x0
	beq item_check_end
	add r3, #0x1
	cmp r3, r1
	bls item_check
item_check_end:
	cmp r3, #0x0
	beq del_keyitem_end
	sub r3, #0x1
	lsl r2, r3,#0x2
	add r2, r0
	ldr r1, [r2,#0x4]
	str r1, [r2]
del_keyitem_end:
	pop {pc}

check_802:
	push {lr}
	mov r0, #0x55
	ldr r1, =poke_na_802
	ldr r1, [r1]
	ldr r2, =0x08F2B790 @Emerald_802_ver
	cmp r1, r2
	beq is_Emerald_802
	mov r0, #0xFF
is_Emerald_802:
	mov r1, #0x6
	mul r0, r1
	pop {pc}

check_Ultra_Emerald:
	push {lr}
	mov r0, #0x1
	ldr r1, =0x080BB100 @Ultra_Emerald
	ldr r1, [r1]
	ldr r2, =0x09E0FF80 @Ultra_Emerald_ver
	cmp r1, r2
	beq is_Ultra_Emerald
	mov r0, #0
is_Ultra_Emerald:
	pop {pc}

party_max:
	push {lr}
	ldr r0, =0x020244E9 @pt_max
	ldrb r0, [r0]
	sub r0,#1
	pop {pc}

reset_IVs_buffer:
	push {lr}
	mov r0, #0
	ldr r1, =buffer3
	add r1, #0x1A
	strh r0, [r1]
	strh r0, [r1,#0x2]
	strh r0, [r1,#0x4]
	pop {pc}

select_set_p:
	push {lr}
	ldr r3, =buffer3
	ldrb r0, [r3,#0x1]
	add r3, r0
	add r3, #0x19
	ldrb r0, [r3]
	mov r1, #1
	neg r1, r0
	adc r0, r1
	strb r0, [r3]
	pop {pc}

setvar:
	push {r4,lr}
	mov r4, r1
	ldr r3, =0x0809D649 @get_var_address
	bl BX_R3
	strh r4, [r0]
	pop {r4,pc}

set_bingdu:
	push {r4-r6,lr}
	ldr r4, =buffer3
	add r4, #0x28
	mov r0, #0xF
	strh r0, [r4]
	ldr r5, =party_playergt
	mov r6,#0x0
ctn_set_bingdu:
	mov r0, r5
	mov r1,#0x22
	mov r2, r4
	ldr r3, =set_attributesa
	bl BX_R3
	add r5, #0x64
	add r6,#0x1
	cmp r6, #0x6
	bne ctn_set_bingdu
	mov r0, #0x1
	pop {r4-r6,pc}

shiye:
	push {lr}
	ldr r2, sav1
	ldr r0, [r2]
	add r0, #0x30
	mov r1, #0x0
	strb r1, [r0]
	ldr r0, [r2,#0x4]
	mov r1, #0xE
	lsl r1, #0x8
	add r0, r1
	add r0, #0x68
	mov r1, #0xC0
	strb r1, [r0]
	pop {pc}
.align 2
sav1:
	.word 0x03005D8C

check_pw:
	push {lr}
	mov r0, #0xFF
	ldr r1, =0x080FE0CB @check_penw_f
	ldrb r1, [r1]
	cmp r1, #0x6
	beq check_penw_end
	lsl r0, #0x8
	add r0, #0xFF
	check_penw_end:
	pop {pc}

BX_R3:
	bx r3



