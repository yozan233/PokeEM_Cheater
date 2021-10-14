#include "header/funcs.h"




void box_draw(u8 box_id, u8 pal)
{
	FillWindowPixelBuffer(box_id,0);
	PutWindowTilemap(box_id);
	DrawStdFrameWithCustomTileAndPalette(box_id,0,0x300,pal);
	return;
}