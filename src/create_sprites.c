#include "header/data.h"
#include "header/sprite.h"

extern struct Sprite *getSprite(u8 id);

static const union AnimCmd sAnim_MonPic_0[] =
{
    {.frame = {0}},
    {.type = -1},
};
const union AnimCmd *const gAnims_MonPic[] = { sAnim_MonPic_0 };

static const union AffineAnimCmd sDummyAffineAnim = { AFFINE_ANIM_END };
const union AffineAnimCmd * const gDummySpriteAffineAnimTable[] = { &sDummyAffineAnim };

const struct OamData gDummyOamData = 
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x16),
    .x = 0,
    .size = SPRITE_SIZE(16x16),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
};

void SpriteCallbackDummy(){

}

struct SpriteTemplate sNormalSpriteTemplate =
{
    .tileTag = 0,
    .paletteTag = 0,
    .oam = &gDummyOamData,
    .anims = gAnims_MonPic,
    .images = 0,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

u8 CreateNormalSprite(s16 x, s16 y){
    u8 spriteId = CreateSprite(&sNormalSpriteTemplate, x, y, 0);
    struct Sprite *sprite = getSprite(spriteId);
    ((u8 *)sprite)[0x3F] = 9;
    return spriteId;
}

void CreateSprites(){
//    u32* gMonIconPaletteTable = (u32 *) gMonIconPaletteTablePtr[0];
//    CpuSet((void *) gMonIconPaletteTable[0], GetOBJPaletteMem(0x10), 16 * 3);
    u8 curId = CreateNormalSprite(0x2E,0x4C);
    mySav->cursorPicId = curId;
    struct Sprite *sprite = getSprite(curId);
    sprite->oam.paletteNum = 0xC;
    sprite->oam.tileNum = 64;
    sprite->oam.matrixNum = 0x10;

    u8 monPicId = CreateNormalSprite(0x52,0x32);
    mySav->monPicId = monPicId;
    sprite = getSprite(monPicId);
    sprite->oam.paletteNum = 0xD;
    sprite->oam.tileNum = 96;
    sprite->oam.matrixNum = 0x8;
    sprite->oam.size = SPRITE_SIZE(64x64);
    sprite->oam.mosaic = TRUE;

//    u8 monIconId = CreateNormalSprite(0x1A,0x4);
//    mySav->monIconId = monIconId;
//    sprite = getSprite(monIconId);
//    sprite->oam.tileNum = 32;
//    sprite->oam.size = SPRITE_SIZE(32x32);
//    sprite->oam.mosaic = TRUE;
//    sprite->callback = (void *) MonIconSpriteCallback;

    #ifndef RUBY_SAPPHIRE
    u8 itemPicId = CreateNormalSprite(0x70,0x28);
    mySav->itemPicId = itemPicId;
    sprite = getSprite(itemPicId);
    sprite->oam.paletteNum = 0xD;
    sprite->oam.tileNum = 256;
    sprite->oam.size = SPRITE_SIZE(32x32);
    sprite->oam.mosaic = TRUE;
    #endif




}

u8 CreateMyMonIcon(u16 species){
    u8 spriteId = CreateMonIcon(species,SpriteCallbackDummy,32,12,4,0,0);

    u32 monIconPaletteIndices = gMonIconPaletteIndicesPtr[0];
    u32 monIconPaletteIndex = ((u8*)(myTempData->species+monIconPaletteIndices))[0];

    struct Sprite *sprite = getSprite(spriteId);
    sprite->oam.paletteNum = monIconPaletteIndex;

    return spriteId;
}
