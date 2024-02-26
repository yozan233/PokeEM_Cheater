#include "header/funcs.h"
#include "header/sprite.h"

extern struct Sprite *getSprite(u8 id);
#ifdef BPRE0
extern const u8 mouse_tile[];
extern const u8 mouse_pal[];
#endif

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
    .priority = 2,
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

void MonIconSpriteCallback(struct Sprite* sprite){
    u8 flag = super->ptr_vblank_counter2 & 0xF;
    
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
    u32 gMonIconPaletteTable = gMonIconPaletteTablePtr;
    CpuSet(((u32*)gMonIconPaletteTable)[0],&OBJ_PaletteMem[0x10],16*3);
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
    sprite->oam.size = SPRITE_SIZE(64x64);
    sprite->oam.mosaic = TRUE;

    u8 monIconId = CreateNormalSprite(0x1A,0x4);
    mySav->monIconId = monIconId;
    sprite = getSprite(monIconId);
    sprite->oam.tileNum = 32;
    sprite->oam.size = SPRITE_SIZE(32x32);
    sprite->oam.mosaic = TRUE;
    sprite->callback = MonIconSpriteCallback;

    u8 itemPicId = CreateNormalSprite(0x70,0x28);
    mySav->itemPicId = itemPicId;
    sprite = getSprite(itemPicId);
    sprite->oam.paletteNum = 4;
    sprite->oam.tileNum = 256;
    sprite->oam.size = SPRITE_SIZE(32x32);
    sprite->oam.mosaic = TRUE;
    #ifdef BPRE0
    CpuSet(&mouse_tile,0x06010000,0x40);
    CpuSet(&mouse_pal,OBJ_PaletteMem,0x10);
    #else
    LZ77UnCompVram(sCursor_Gfx,0x06010000);
    CpuSet(gFrontierPassCursor_Pal,OBJ_PaletteMem,0x10);
    #endif

}
