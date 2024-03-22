#include "header/funcs.h"

#ifndef RUBY_SAPPHIRE
bool8 tiles_load()
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
				return FALSE;
			else 
				break;
		case 2:
			LoadPalette(sDiplomaPalettes,0,0x40);
			return TRUE;
		default:
			return TRUE;
	}
	(*(*malloc_pointer_loc+1))++;
	return FALSE;
}
#else
bool8 tiles_load()
{
	switch(*(*malloc_pointer_loc+1))
	{
		case 0:
			LZ77UnCompVram(sDiplomaTiles, 0x6000000);
    		LZ77UnCompVram(sDiplomaTilemap, 0x6000000 + 0x3000);
			break;
		case 1:
			LoadPalette(sDiplomaPalettes, 0, 0x40);
			return TRUE;
		default:
			return TRUE;
	}
	(*(*malloc_pointer_loc+1))++;
	return 0;
}
#endif