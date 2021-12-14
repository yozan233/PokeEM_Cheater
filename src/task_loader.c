#include "header/funcs.h"
extern void sub_bg_init(void);
extern u8 tiles_load(void);
extern void string_print(void);
extern void load_icons(void);
extern void task_02(u8 task_id);
extern void CpuFastFill(u32 value, u32 dest, u32 size) ;
void box_draw(u8,u8);

const struct rbox_short rbox_table[] = 
{
	{0x00,0x01,0x01,0x1C,0xF,0x0F,0x57},{0xFF,0,0,0,0,0,0},{0,1,0x11,28,2,0xF,0}
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
			SetVBlankCallback((void*)0);
			CpuFastFill(0,BUFFER_3,0x40);
			sub_bg_init();
			CreateSprites();
			break;
		case 1:
			if(!tiles_load())
				return;
			else break;
		case 2:
			//内容盒子
			InitWindows(rbox_table);
			DeactivateAllTextPrinters();
			PutWindowTilemap(0);
			
			//活动盒子
			temp = AddWindow(rbox_table+2);
			mySav->boxId = temp;
			box_draw(temp,0xE);
			
			InitPage(PAGE_MAIN);

			//TODO CRC
			// u16 crc = CalcCRC16WithTable(text_table[TEXT_AUTHOR],0x17);
			// if (crc != 0x97AB){
			// 	DoSoftReset();
			// }

			//TODO 不显示背景图片
			SetGpuReg(0,0x3140);
			u8* bgPal = (u8 *)BG_PaletteMem;
			bgPal[0]= 0xFF;
			bgPal[1] = 0x5F;
			
			SetGpuReg(0xA,0x1E07);
			SetGpuReg(0x48,0x1F3F);
			SetGpuReg(0x4A,0x0F1F);
			CopyBgTilemapBufferToVram(0);
			CopyBgTilemapBufferToVram(1);
			break;
		case 3:
			BeginNormalPaletteFade(-1,0,0x10,0,0); //make it come back to bright
			SetVBlankCallback(VBlankCB_SelectScreen); //will update the fade_ctrl
			break;
		default:
			if(!((pal_fade_control->mix_color) >> 8 & 0x80))
				break;
			tasks[task_id].priv[2] = 0;
			tasks[task_id].priv[3] = 0;
			tasks[task_id].fptr = task_02;
			PlaySE(31);
			break;
	}
	(*(*malloc_pointer_loc+2))++;
	return;
}

void box_draw(u8 box_id, u8 pal)
{
	struct TilesPal tilesPal = ((struct TilesPal *)sWindowFrames_offset)[0];
	LoadBgTiles(0, tilesPal.tiles, 0x120, 0x2FF);
    LoadPalette(tilesPal.pal, pal*0x10, 0x20);

	FillWindowPixelBuffer(box_id,0);
	PutWindowTilemap(box_id);
	DrawStdFrameWithCustomTileAndPalette(box_id,0,0x300,pal);
	return;
}