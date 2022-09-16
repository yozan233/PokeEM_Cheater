#include "header/funcs.h"




void box_draw(u8 box_id, u8 pal)
{
	rboxid_fill_pixels(box_id,0);
	rboxid_bg_prepare(box_id);
	rboxid_draw_810F2E8(box_id,0,0x300,pal);
	return;
}