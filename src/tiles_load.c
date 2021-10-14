#include "header/funcs.h"

u8 tiles_load()
{
	switch(*(*malloc_pointer_loc+1))
	{
		case 0:
			ResetTempTileDataBuffers();
			DecompressAndCopyTileDataToVram(1,/*bg_tiles*/0x085E7804,0,0,0);
			CopyToBgTilemapBuffer(1,/*raw*/0x085E70C8,0,0);
			break;
		case 1:
			if(FreeTempTileDataBuffersIfPossible())
				return 0;
			else break;
		case 2:
			ItemId_GetSecondaryId();
			LoadPalette(/*bgpal*/0x085E7088,0,0x40);
			return 1;
		default:
			return 1;
	}
	(*(*malloc_pointer_loc+1))++;
	return 0;
}