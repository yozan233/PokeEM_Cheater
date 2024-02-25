#include "header/funcs.h"

u8 tiles_load()
{
	switch(*(*malloc_pointer_loc+1))
	{
		case 0:
			ResetTempTileDataBuffers();
			DecompressAndCopyTileDataToVram(1,sDiplomaTiles,0,0,0);
			CopyToBgTilemapBuffer(1,sDiplomaTilemap,0,0);
			break;
		case 1:
			if(FreeTempTileDataBuffersIfPossible())
				return 0;
			else break;
		case 2:
			LoadPalette(sDiplomaPalettes,0,0x40);
			return 1;
		default:
			return 1;
	}
	(*(*malloc_pointer_loc+1))++;
	return 0;
}