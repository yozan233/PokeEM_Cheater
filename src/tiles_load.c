#include "header/funcs.h"

u8 tiles_load()
{
	switch(*(*malloc_pointer_loc+1))
	{
		case 0:
			graphic_log_clear();
			decompress_with_fallback(1,/*bg_tiles*/0x085E7804,0,0,0);
			gpu_tilemap_apply(1,/*raw*/0x085E70C8,0,0);
			break;
		case 1:
			if(decompress_stat_check())
				return 0;
			else break;
		case 2:
			get_item_lastword();
			gpu_pal_apply(/*bgpal*/0x085E7088,0,0x40); //gpu_pal_apply,0x80A1939
			return 1;
		default:
			return 1;
	}
	(*(*malloc_pointer_loc+1))++;
	return 0;
}