#include "header/funcs.h"
// extern struct rbox_short rbox_table[];
void *VRAM = (void *)0x6000000;
void *PRAM = (void *)0x5000000;
void *OAM = (void *)0x7000000;
void *volatile*DMA3SAD = (void *volatile*)0x40000D4;
void *volatile*DMA3DAD = (void *volatile*)0x40000D8;
vu32 *DMA3CNT = (vu32 *)0x40000DC;

const struct bg_cfg bg_config_table[2] __attribute__((align(4))) = 
{
	{0,0,31,0,0,2,1,0},{1,1,29,1,0,3,0,0}
};
void sub_bg_init()
{
	void* v0;
	v0 = VRAM;
	u32 v1 = 0x18000;
	u32 v6;
	union DISPCNT_CON v3;
	union DMACNT_CON v2;
	v2.DMACNT_S = (struct DMACNT){0x800,0,0,2,0,0,0,0,0,1};
	u16 v5 = 0;
	do
	{
		*DMA3SAD = &v5;
		*DMA3DAD = v0;
		*DMA3CNT = v2.DMACNT_D;
		v0 += 0x1000;
		v1 -= 0x1000;
	}
	while(v1 > 0);
	v6 = 0;
	*DMA3SAD = &v6;
	*DMA3DAD = OAM;
	v2.DMACNT_S = (struct DMACNT){0x100,0,0,2,0,1,0,0,0,1};
	*DMA3CNT = v2.DMACNT_D;
	*DMA3SAD = &v5;
	*DMA3DAD = PRAM;
	v2.DMACNT_S = (struct DMACNT){0x200,0,0,2,0,0,0,0,0,1};
	*DMA3CNT = v2.DMACNT_D;
	v3.DISPCNT_S = (struct DISPCNT){0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	lcd_io_set(0,v3.DISPCNT_D);
	gpu_tile_bg_drop_all_sets(0);
	bg_vram_setup(0,bg_config_table,2);
	for (u32 i=0;i<4;i++)
	{
		bgid_mod_x_offset(i,0,0);
		bgid_mod_y_offset(i,0,0);
	}
	v3.DISPCNT_S = (struct DISPCNT){0,0,0,0,1,0,0,0,0,0,1,1,0,0};
	lcd_io_set(0,v3.DISPCNT_D);
	bgid_set_tilemap(1,*malloc_pointer_loc+4);
	gpu_sync_bg_show(0);
	gpu_sync_bg_show(1);
	bg_config_2_something(0,0,0,0,0x1E,0x14);
	bg_config_2_something(1,0,0,0,0x1E,0x14);
	return;
}