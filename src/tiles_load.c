#include "header/data.h"

extern const u8 mouse_tile[];
extern const u8 mouse_pal[];

#ifndef RUBY_SAPPHIRE
bool8 tiles_load()
{
	switch(*(*malloc_pointer_loc+1))
	{
		case 0:
            ResetTempTileDataBuffers();
            DecompressAndCopyTileDataToVram(1,sDiplomaTiles,0,0,0);
            CopyDiplomaTilemapBuffer();
            CpuSet(&mouse_tile,(void *)cursorTilesArm,0x40);
			break;
		case 1:
			if(FreeTempTileDataBuffersIfPossible())
				return FALSE;
			else 
				break;
		case 2:
            TryLoadAllMonIconPalettesAtOffset(0);
            CpuSet(GetBGPaletteMem(0),GetOBJPaletteMem(0),0x80);
			LoadPalette(sDiplomaPalettes,0,0x40);
            LoadPalette(&mouse_pal,0x1C0,0x20);
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