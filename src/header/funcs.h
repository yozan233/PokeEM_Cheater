#include "structs.h"
void SetMainCallback2(void(*func));
void * AllocZeroed(u32 size);
void * Alloc(u32 size);
void Free(void *);
void PlaySE(u16 soundID);
void GetMapName(u8 *dest, u16 regionMapId, u16 padLength);
u32 GetPlayerIDAsU32(void);
u32 umodsi3(u32 numerator, u32 denumerator);
u8 AddBagItem(u16 item, u16 num);
//080B3964
void RtcInitLocalTimeOffset(s32 hour, s32 minute);
u16 Random(void);
void CreateMon(struct Pokemon* poke, u16 species, u8 lvl, u8 IVs, u8 pid_set, u32 PiD, u8 tid_set, u32 TiD);
void SetMonData(struct Pokemon* poke_address, u8 request, const void* new_value);
void CalculateMonStats(struct Pokemon* poke_address);

void EnableNationalPokedex(void);
void HealPlayerParty(void);
u16 VarGet(u16 varID);
bool8 VarSet(u16 id, u16 value);
void memcpy(void *destdst,void *src,u32 len);
void ResetSpriteData(void);
void ResetPaletteFade(void);
void FreeAllSpritePalettes(void);
void LoadPalette(void *src, u16 dst_index, u16 num_bytes);
u8 CreateTask(void(*func)(u8),u8 priority);
void DestroyTask(u8 task_id);
u32 GiveMonToPlayer(struct Pokemon*);
void MainCB2(void);
void SetVBlankCallback(void(*));
//lcd_io_set
void SetGpuReg(u8 reg, u16 value);
void InitBgsFromTemplates(u8 bg_mode, u8 *config_data, u8 config_num_entries);
u32 ChangeBgX(u8 bg_id, u32 delta, u8 mode);
u32 ChangeBgY(u8 bg_id, u32 delta, u8 mode);
void CopyBgTilemapBufferToVram(u8 bg_id);
u8 InitWindows(struct rbox_short *);
void DeactivateAllTextPrinters(void);
void SetBgTilemapBuffer(u8 bg_id, void *src);
void ShowBg(u8 bg_id);
void ResetTempTileDataBuffers(void);
u8 FreeTempTileDataBuffersIfPossible(void);
void CopyToBgTilemapBuffer(u8 bg_id, void *src, u16 mode, u16 offset_in_block);
void *DecompressAndCopyTileDataToVram(u8 bg_id, void *src, u16 size, u16 offset, u8 mode);
u8 BeginNormalPaletteFade(u32 bitmask, u8, u8, u8, u16 color);
void VBlankCB_SelectScreen(void);
u8 CreateSprite(struct SpriteTemplate *template, s16 x, s16 y, u8 subpriority);
u8 AddTextPrinterParameterized(u8 rbox_id, u8 font, u8 *str, u8 x_in_box, u8 y_in_box, u8 text_speed, u32 field_10_in_remo);
void AddTextPrinterParameterized3(u8 foo, u8 font, u8 x_in_pixel_inbox, u8 y_in_pixel_inbox, u8* bar, u8 baz, u8 *str);
void PutWindowTilemap(u8 rbox_id);
void FillWindowPixelBuffer(u8 rbox_id,u8 filler);
void LoadBgTiles(u8 bgid, u8 *src, u16 size, u16 offset);
void DrawStdFrameWithCustomTileAndPalette(u8 rbox_id, u8 unk, u16 char_name, u8 pal);
u8 AddWindow(struct rbox_short *);
u8 *ConvertIntToDecimalStringN(u8 *dest, u32 value, u8 mode, u8 charlength);
u8 *ConvertIntToHexStringN(u8 *dest, u32 value, u8 mode, u8 n);
u8 *StringCopy(u8 *dest, u8 *src);
void FreeAllWindowBuffers(void);
void CB2_ReturnToFieldContinueScript(void);
void SetWarpDestination(s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y);
void FillWindowPixelRect(u8 windowId, u8 fillValue, u16 x, u16 y, u16 width, u16 height);
struct MapHeader *GetMapHeaderByGroupAndId(u16 mapGroup, u16 mapNum);
void CopyItemIconPicTo4x4Buffer(void *src, void *dest);
s32 StringCompare(const u8 *str1, const u8 *str2);
u16 SpeciesToNationalPokedexNum(u16 species);
s8 GetSetPokedexFlag(u16 nationalNum, u8 caseId);
bool8 RemoveBagItem(u16 itemId, u16 count);
void ZeroMonData(struct Pokemon *mon);
extern s16 udivsi3(s16 a, s16 b);
void ItemUseCB_RareCandy(void);
extern void CpuFastSet(const void *src, void *dest, int control);
//swi 0x12
extern void LZ77UnCompVram(const void *src, void *dest);
//swi 0xB
extern void CpuSet(void *src, void *dest, int control);
extern void CpuFastFill(int value, void *dest, int size);
extern void ItemUseOutOfBattle_Repel(u8 taskId);
extern const struct HealLocation *GetHealLocation(u32 index);
extern void DoWarp(void);
extern void ResetInitialPlayerAvatarState(void);
extern void DecryptBoxMon(void *boxMon);
extern void EncryptBoxMon(void *boxMon);
extern u16 CalculateBoxMonChecksum(void *boxMon);

extern void Text_LoadWindowTemplate(const void *winConfig);
extern void InitMenuWindow(const void *winConfig);
extern u8 Menu_PrintTextPixelCoords(const u8 *text, u8 left, u16 top, u8 a4);
extern void ScanlineEffect_Stop(void);
extern void Menu_DrawStdWindowFrame(u8 left, u8 top, u8 right, u8 bottom);
extern void Menu_BlankWindowRect(u8 left, u8 top, u8 right, u8 bottom);
extern void Menu_EraseWindowRect(u8 left, u8 top, u8 right, u8 bottom);
extern void ExpandBattleTextBuffPlaceholders(const u8 *src, u8 *dst);

extern void debug();

extern u8 throughWallFlag[];
extern struct fade_ctrl *gPaletteFade;
extern u16 *gSpecialVar_0x8004;
extern struct Sprite gSprites[];
extern u16 gPlttBufferUnfaded[];
extern u16 gPlttBufferFaded[];

extern u8 gPlayerPartyCount[];
extern struct Pokemon gPlayerParty[];
extern struct BagPocket gBagPockets[];

extern u8 gStringVar1[];

extern struct SaveBlock1 *gSaveBlock1Ptr;
extern struct SaveBlock2 *gSaveBlock2Ptr;

extern struct SaveBlock1 gSaveBlock1;
extern struct SaveBlock2 gSaveBlock2;

extern struct Time gLocalTime;
extern struct Main gMain;
extern struct Task *gTasks;

extern u32 *gMonIconTablePtr;
extern u32 *gMonFrontPicTablePtr;
extern u32 gItemIconTablePtr;
extern u32 *gMonPaletteTablePtr;
extern u32 gSpeciesNamesPtr[];
extern u32 gSpeciesInfoPtr[];
extern u32 gMonIconPaletteIndicesPtr[];
extern u32 gMonIconPaletteTablePtr[];
extern u32 gMoveNamesPtr[];
extern u32 gItemsPtr[];
extern u32 gBattleMovesPtr[];

extern u8 sCursor_Gfx[];
extern u8 gFrontierPassCursor_Pal[];
extern u8 sDiplomaPalettes[];
extern u8 sDiplomaTilemap[];
extern u8 sDiplomaTiles[];
extern u8 sWindowFrames[];



