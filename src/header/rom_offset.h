
/**
 * RAM地址
 */
#define VAR_8004 0x020375E0
#define gSprites 0x02020630
#define gPlttBufferUnfaded 0x02037714
#define gPlttBufferFaded 0x02037b14
#define OBJ_PaletteMem 0x02037914
#define OBJ_PaletteMem2 0x02037D14
#define BG_PaletteMem 0x02037714
#define BG_PaletteMem2 0x02037B14
#define gPlayerParty 0x020244EC //精灵队伍
#define gBagPockets 0x02039dd8
#define gPlayerPartyCount 0x020244E9
#define throughWallFlag 0x020322d6
#define itemTilesArm 0x06012000
#define monTilesArm  0x06010C00
#define BUFFER_2 0x02021DC4
#define BUFFER_3 0x02021EC4
#define gSaveBlock1Ptr 0x03005D8C
#define gSaveBlock2Ptr 0x03005d90
#define gLocalTime 0x03005cf8
#define gMain 0x030022C0
#define gTasks 0x03005E00
#define gPaletteFade 0x02037FD4


/**
 * ROM地址
*/
#define gSpeciesNames_Pointer 0x08000144 //精灵种族名字
#define gBaseStats_Pointer 0x080001BC //精灵种族值
#define gMonFrontPicTable_Pointer 0x8000128 //精灵正面图
#define gMonPaletteTable_Pointer 0x8000130 //精灵普通调色板
#define gMonShinyPaletteTable_Pointer 0x8000134 //精灵闪光调色板
#define gMonIconTable_Pointer 0x8000138 //精灵小图标
#define gMoveNames_Pointer 0x08000148 //技能名称
#define gMonIconPaletteIndices_Pointer 0x800013C //精灵小图标调色板编号
#define gExperienceTables_Pointer 0x0806DFF0 //经验值表
#define gAbilityNames_Pointer 0x080001C0 //特性名字
#define qhAbilityNames 0x082E99F8 //漆黑特性名字2
#define gItems_Pointer 0x080001C8 //道具表
#define gBattleMoves_Pointer 0x080001CC //技能表
#define gTypeNames_Pointer 0x080166F4 //属性名称
#define gItemIconTable_Pointer 0x081B0034 //道具图标
#define gText_ThreeDashes 0x085e8d45 //文本"---"
#define gMonIconPalettes_Pointer 0x0857C540

#define maxLvl_Pointer 0x0804A5BE
#define eggHatchLevel_Pointer 0x8070978
#define gmaxLvlOffsetFlag 0x0806DFB2
#define gFlightPointCount 0x08122C88
#define gMonIcon_Egg 0x08d8fc74
#define gPokeMax ((u16 *)0x080DE860)[0]
#define fun_GetHealLocationIndexByMap 0x08122c5c
#define sHealLocations ((u32 *)(fun_GetHealLocationIndexByMap+0x24))[0]
#define fun_ItemUseOutOfBattle_Repel 0x080fe0bc
#define gOamData_AffineOff_ObjNormal_16x16 0x0852490c
#define gAnims_MonPic 0x082ff70c
#define gDummySpriteAffineAnimTable 0x082ec6a8
#define SpriteCallbackDummy 0x08007428|1
#define sCursorGfx 0x08570BA8
#define gFrontierPassCursor_Pal 0x08dc1674

#define sDiplomaPalettes 0x085e7088
#define sDiplomaTilemap 0x085e70c8
#define sDiplomaTiles 0x085e7804

#define sWindowFrames_offset 0x851021c