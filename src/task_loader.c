#include "header/funcs.h"
extern void sub_bg_init(void);
extern u8 tiles_load(void);
extern void string_print(void);
extern void box_draw(u8,u8);
extern void load_icons(void);
extern void task_02(u8 task_id);
const struct rbox_short rbox_table[] __attribute__((align(4))) = 
{
	{0x00, 0x01, 0x01, 0x1C, 0xF, 0x0F, 0x57, 0x00},{0x00, 0x01, 0x11, 0x1C, 0x02, 0x0F, 0x00, 0x00}
};
//	.byte 0x00, 0x01, 0x01, 0x1C, 0xF, 0x0F, 0x57, 0x00
//	.byte 0x00, 0x01, 0x11, 0x1C, 0x02, 0x0F, 0x00, 0x00
//	@;.byte 0,/*横坐标*/4,/*纵坐标*/0x5,/*长*/10,/*高*/5,/*文本调色板*/0xF,0,0

void task_loader(u8 task_id)
{
	int temp;
	switch(*(*malloc_pointer_loc+2))
	{
		case 0:
			vblank_handler_set((void*)0);
			strbData->mode=0;
			strbData->select=0;
			strbData->over=0;
			strbData->party=0;
			sub_bg_init();
			// setData();
			load_icons();
			break;
		case 1:
			if(!tiles_load())
				return;
			else break;
		case 2:
			gpu_copy_to_tileset(0,0x0850E87C,0x120,0x2FF);//box_title
			box_palxE();
			
			//内容盒子
			rbox_calc_and_send(rbox_table);
			remo_clear_unk();
			set_text(0);
			rboxid_bg_prepare(0);
			
			
			//活动盒子
			temp = rbox_spawn(rbox_table+1);
			strbData->boxid = temp;
			box_draw(temp,0xE);
			rboxid_print(temp,1,text_table,6,0,0,0); //按键提示盒子
			
			u16 crc = CalcCRC16WithTable(text_table+0x1C9,0x17);
			//(text_table+0x1E0) - (text_table+0x1C9)
			// x+1E0-x-1C9
			// 0x1E0-0x1C9
			// 0x17
			//testr();
						
			if (crc != 0x8E73){
				DoSoftReset();
			}
			
			lcd_io_set(0xA,0x1E07);
			lcd_io_set(0x48,0x1F3F);
			lcd_io_set(0x4A,0x0F1F);
			bgid_send_tilemap(0);
			bgid_send_tilemap(1);
			break;
		case 3:
			oak_fade(0xFFFFFFFF,0,0x10,0,0); //make it come back to bright
			vblank_handler_set(vblank_cb_080F4BFC); //will update the fade_ctrl
			break;
		default:
			if(!((pal_fade_control->mix_color) >> 8 & 0x80))
				break;
			tasks[task_id].priv[2] = 0;
			tasks[task_id].priv[3] = 0;
			tasks[task_id].fptr = task_02;
			break;
	}
	(*(*malloc_pointer_loc+2))++;
	return;
}

void box_palxE(){
	asm("push {lr}\nldr r0, box_p\nldr r1, box_bg_palette\nmov r2, #0x10\nswi #0xB\nmov r0, #0x0\npop {pc}\n.align 2\nbox_p:\n.word 0x0850FEFC\nbox_bg_palette:\n.word 0x020378D4");
}