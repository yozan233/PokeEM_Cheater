#include "header/funcs.h"

extern struct Sprite *getSprite(u8 id);

u32 **gMonIconPalettes = (u32 **)gMonIconPalettes_Pointer;

struct SpriteTemplate sNormalSpriteTemplate =
{
    .tileTag = 0,
    .paletteTag = 0,
    .oam = gOamData_AffineOff_ObjNormal_16x16,
    .anims = gAnims_MonPic,
    .images = 0,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

void MonIconSpriteCallback(struct Sprite* sprite){
    u8 flag = super->ptr_vblank_counter & 0xF;
    
    if(flag == 0x0)
        sprite->oam.tileNum = 0x30;
    else if(flag == 0x8)
        sprite->oam.tileNum = 0x20;
    
}

u8 CreateNormalSprite(s16 x, s16 y){
    u8 spriteId = CreateSprite(&sNormalSpriteTemplate, x, y, 0);
    struct Sprite *sprite = getSprite(spriteId);
    ((u8 *)sprite)[0x3F] = 9;
    return spriteId;
}

void CreateSprites(){
    CpuSet(*gMonIconPalettes,OBJ_PaletteMem+0x20,16*3);
    u8 curId = CreateNormalSprite(0x2E,0x4C);
    mySav->cursorPicId = curId;
    struct Sprite *sprite = getSprite(curId);
    sprite->oam.paletteNum = 0;
    sprite->oam.tileNum = 0;
    sprite->oam.matrixNum = 0x10;

    u8 monPicId = CreateNormalSprite(0x52,0x32);
    mySav->monPicId = monPicId;
    sprite = getSprite(monPicId);
    sprite->oam.paletteNum = 4;
    sprite->oam.tileNum = 96;
    sprite->oam.matrixNum = 0x8;
    sprite->oam.size = 3;
    sprite->oam.mosaic = TRUE;

    u8 monIconId = CreateNormalSprite(0x1A,0x4);
    mySav->monIconId = monIconId;
    sprite = getSprite(monIconId);
    sprite->oam.tileNum = 32;
    sprite->oam.size = 2;
    sprite->oam.mosaic = TRUE;
    sprite->callback = MonIconSpriteCallback;

    u8 itemPicId = CreateNormalSprite(0x70,0x28);
    mySav->itemPicId = itemPicId;
    sprite = getSprite(itemPicId);
    sprite->oam.paletteNum = 4;
    sprite->oam.tileNum = 256;
    sprite->oam.size = 2;
    sprite->oam.mosaic = TRUE;
    
    LZ77UnCompVram(sCursorGfx,0x06010000);
    CpuSet(gFrontierPassCursor_Pal,OBJ_PaletteMem,16);

}
