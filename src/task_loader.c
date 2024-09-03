#include "header/data.h"
extern void sub_bg_init(void);
extern bool8 tiles_load(void);
extern void task_02(u8 task_id);
extern void CreateSprites();
extern void InitPage(u8 page);
extern u8 gTextWindowFrame1_Gfx[];
extern u8 gTextWindowFrame1_Pal[];

#ifndef RUBY_SAPPHIRE
void box_draw(u8);
#endif


//	.byte 0x00, 0x01, 0x01, 0x1C, 0xF, 0x0F, 0x57, 0x00
//	.byte 0x00, 0x01, 0x11, 0x1C, 0x02, 0x0F, 0x00, 0x00
//	@;.byte 0,/*横坐标*/4,/*纵坐标*/0x5,/*长*/10,/*高*/5,/*文本调色板*/0xF,0,0

void task_loader(u8 task_id)
{
	switch(*(*malloc_pointer_loc+2))
	{
		case 0:
			CpuFastFill(0,myTempData,0x80);
			#ifdef FIRE_RED_LEAF_GREEN
			myTempData->optionsButtonMode = gSaveBlock2Ptr->optionsButtonMode;
			gSaveBlock2Ptr->optionsButtonMode = 1;
            #endif
            #ifdef RUBY_SAPPHIRE
            myTempData->optionsButtonMode = gSaveBlock2.optionsWindowFrameType;
            gSaveBlock2.optionsWindowFrameType = 0;
            #endif
			sub_bg_init();
			CreateSprites();
			break;
		case 1:
			if(!tiles_load())
				return;
			else 
				break;
		case 2:
			#ifdef RUBY_SAPPHIRE
			Menu_DrawStdWindowFrame(0, 0x10, 0x1D, 0x13);

			SetGpuReg(0x4,0x8);
			SetGpuReg(0x0,0x1940);
    		SetGpuReg(0xE,0x4603);

			#else
			//内容盒子
            InitMainWindows();
            PutWindowTilemap(0);
			
			//活动盒子
			u8 boxId = InitSecondWindows();
			mySav->boxId = boxId;
			box_draw(boxId);

			SetGpuReg(0,0x3341);
			
			SetGpuReg(0xA,0x1E07);
			SetGpuReg(0x48,0x1F3F);
			SetGpuReg(0x4A,0x0F1F);
            CopyBgTilemapBufferToVram01();
			#endif


			InitPage(PAGE_MAIN);
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
}

#ifndef RUBY_SAPPHIRE
void box_draw(u8 box_id)
{
	LoadBgTiles(0, gTextWindowFrame1_Gfx, 0x180, 0x2FF);
    LoadPalette(gTextWindowFrame1_Pal, 0xE*0x10, 0x40);

	FillWindowPixelBuffer(box_id,0);
	PutWindowTilemap(box_id);
	DrawStdFrameWithCustomTileAndPalette(box_id,0,0x300,0xE);
}
#endif