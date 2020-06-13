.thumb @make the assembler assemble it in thumb
.global load_icons @make it a global function
.thumb_func @make the assembler know that the function is in thumb

.equ gpu_pal_obj_alloc_tag_and_apply, 0x8008745
.equ pal_gfx, 0x8DDE1F8
.equ pokemon_getattr, 0x806A519
.equ gpu_tile_obj_alloc_tag_and_upload, 0x80084F9
.equ template_instanciate_forward_search, 0x8006DF5
.equ obj_palette, 0x02037914
.equ icons_pal, 0x0857C540
.equ objects, 0x02020630
.equ var_8004, 0x020375E0
.equ script_text_buffer3, 0x02021EC4
.equ testa, 0x8F2EC05

load_icons:
push {r4,lr}

ldr r0, =icons_pal
ldr r0, [r0]
ldr r1, =obj_palette+0x20
mov r2, #0x30
swi #0xB
ldr r0, =0x08570BA8 @;光标图标
ldr r1, =0x06010000
swi #0x12
ldr r0, =0x08DC1674 @;光标调色板
ldr r1, =obj_palette
mov r2, #0x10
swi #0xB

load_mouse:
	bl mouse
	ldr r2, =var_8004
	strb  r0, [r2,#0x5]
	ldr r2, =objects
	mov r1, #0x44
	mul r1, r0
	add r1, r2
	mov r3, r1
	mov r2, #0x9
	add r1, #0x3F
	strb r2, [r1]
	mov r1, #0x60
	strb r1, [r3,#0x3]
	mov r1, #0x0
	strh r1, [r3,#0x4]

bl obj_spawn

back:
	bl mouse @;精灵图片obj
	ldr r2, =0x02021EC4
	strb  r0, [r2,#0xA]
	ldr r2, =objects
	mov r1, #0x44
	mul r1, r0
	add r1, r2
	mov r3, r1
	mov r2, #0x9
	add r1, #0x3F
	strb r2, [r1]

	@oam_1
	mov r2, #0xD0
	strb r2, [r3,#0x3]
	@oam_2
	mov r2, #0x4C
	lsl r2, #0x8
	add r2, #0x60
	strh r2, [r3,#0x4]
	@pos_x
	mov r2, #0x52
	strh r2, [r3,#0x20]
	@pos_y
	mov r2, #0x32
	strh r2, [r3,#0x22]
	@oam_0
	mov r2, #0x8
	strb r2, [r3,#0x1]

	@;道具图片obj
	bl mouse @;精灵图片obj
	ldr r2, =0x02021EC4
	add r2, #0x2E
	strb  r0, [r2]
	ldr r2, =objects
	mov r1, #0x44
	mul r1, r0
	add r1, r2
	mov r3, r1
	mov r2, #0x9
	add r1, #0x3F
	strb r2, [r1]
	@pos_x
	mov r2, #0x70
	strh r2, [r3,#0x20]
	@pos_y
	mov r2, #0x28
	strh r2, [r3,#0x22]
	@oam_1
	mov r2, #0x80
	strb r2, [r3,#0x3]
	@oam_2
	mov r2, #0x0
	strb r2, [r3,#0x4]
	mov r2, #0x4D
	strb r2, [r3,#0x5]
	@oam_0
	mov r2, #0x8
	strb r2, [r3,#0x1]
	

pop {r4,pc}

obj_spawn:
push {r4,lr}
sub sp, sp, #0x18
mov r1, sp

ldr r0, =0x1400
strh r0, [r1]
ldr r2, =0x0857C570
str r2, [r1,#0x4]
ldr r2, =0x082FF70C
str r2, [r1,#0x8]
mov r2, #0x0
str r2, [r1,#0xC]
ldr r2, =0x082EC6A8
str r2, [r1,#0x10]
ldr r2, =0x0818CFC9
str r2, [r1,#0x14]

ldr r2, =0x1300
add r0, r2, r0
strh r0, [r1, #2]

mov r0, sp
mov r1, #0x22
mov r2, #0xC
mov r3, #0
ldr r4, =template_instanciate_forward_search
bl bx_r4
ldr r4, =var_8004
strb r0, [r4,#0x6]

goam:
ldr r3, =script_text_buffer3
ldrb r2, [r3,#0x11]
cmp r2, #0x1
beq spawn_egg
ldrh r3, [r3,#0x12]
ldr r2, =0x8000138
ldr r2, [r2,#0x4]
add r2, r3
ldrb r3, [r2]
add r3, #0x1
b spawn_back

spawn_egg:
mov r3, #2

spawn_back:
lsl r3, #0x4
add r3, #0x4
ldr r2, =objects
mov r1, #0x44
mul r0, r0, r1
add r0, r0, r2
mov r2, r0
mov r1, #0x9
add r2, #0x3F
strb r1, [r2]
mov r1, #0x20
mov r2, #0x20

add r2, r1
strb r2, [r0,#0x4]
strb r3, [r0,#0x5]
mov r2, #0x8
strb r2, [r0,#0x1]

add sp, sp, #0x18
pop {r4, pc}

mouse:
push {r4, lr}
sub sp, sp, #0x18
mov r1, sp
mov r2, #0
str r2, [r1]
str r2, [r1,#0xC]
ldr r2, =0x0852490C
str r2, [r1,#0x4]
ldr r2, =0x082FF70C
str r2, [r1,#0x8]
ldr r2, =0x082EC6A8
str r2, [r1,#0x10]
ldr r2, =0x0818CFC9
str r2, [r1,#0x14]

mov r0, sp
mov r1, #0x2E	@;横坐标
mov r2, #0x4C	@;纵坐标
mov r3, #0x0
ldr r4, =template_instanciate_forward_search
bl bx_r4

add sp, sp, #0x18
pop {r4, pc}

bx_r4:
	bx r4





