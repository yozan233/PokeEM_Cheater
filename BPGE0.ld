SetMainCallback2 = 0x08000544|1;
SetVBlankCallback = 0x080006f4|1;
Alloc = 0x08002b9c|1;
AllocZeroed = 0x08002bb0|1;
Free = 0x08002bc4|1;
SetGpuReg = 0x08000a38|1;
InitBgsFromTemplates = 0x08001658|1;
LoadBgTiles = 0x080017d0|1;
ShowBg = 0x080019bc|1;
ChangeBgX = 0x08001b90|1;
ChangeBgY = 0x08001d08|1;
SetBgTilemapBuffer = 0x08001fa0|1;
CopyToBgTilemapBuffer = 0x08002040|1;
CopyBgTilemapBufferToVram = 0x080020bc|1;
InitWindows = 0x08003b24|1;
AddWindow = 0x08003ce4|1;
FreeAllWindowBuffers = 0x08003ecc|1;
PutWindowTilemap = 0x08003fa0|1;
FillWindowPixelRect = 0x08004378|1;
FillWindowPixelBuffer = 0x0800445c|1;
DeactivateAllTextPrinters = 0x08002c28|1;
AddTextPrinterParameterized = 0x08002c48|1;
ResetSpriteData = 0x08006b10|1;
CreateSprite = 0x08006f8c|1;
FreeAllSpritePalettes = 0x080088f0|1;
StringCopy = 0x08008d84|1;
StringCompare = 0x08008e28|1;
ConvertIntToDecimalStringN = 0x08008e78|1;
ConvertIntToHexStringN = 0x08008f18|1;
VBlankCB_SelectScreen = 0x080f4bd4|1; /*VBlankCB_Diploma*/
ZeroMonData = 0x0803d994|1;
CreateMon = 0x0803da54|1;
CalculateBoxMonChecksum = 0x0803e3e8|1;
CalculateMonStats = 0x0803e47c|1;
EncryptBoxMon = 0x0803f8f8|1;
DecryptBoxMon = 0x0803f91c|1;
GetMonData = 0x0803fbe8|1;
SetMonData = 0x0804037c|1;
GiveMonToPlayer = 0x08040b14|1;
SpeciesToNationalPokedexNum = 0x08043298|1;
Random = 0x08044ec8|1;
GetMapHeaderByGroupAndId = 0x08055238|1;
SetWarpDestination = 0x0805538c|1;
ResetInitialPlayerAvatarState = 0x080559e4|1;
CB2_ReturnToFieldContinueScript = 0x080568c4|1;
ScriptContext_SetupScript = 0x08069ae4|1;
EnableNationalPokedex = 0x0806e22c|1;
VarGet = 0x0806e568|1;
VarSet = 0x0806e584|1;
StartMenuExitCallback = 0x0806f540|1;
LoadPalette = 0x080703ec|1;
MainCB2 = 0x80F4C28|1;
ResetPaletteFade = 0x08070528|1;
BeginNormalPaletteFade = 0x08070588|1;
PlaySE = 0x080722cc|1;
CreateTask = 0x0807741c|1;
DestroyTask = 0x08077508|1;
DoWarp = 0x0807e40c|1;
GetSetPokedexFlag = 0x08088e48|1;
RemoveBagItem = 0x0809a1ac|1;
AddBagItem = 0x0809a058|1;
GetPlayerIDAsU32 = 0x080cc1b8|1; /*GetPlayerTrainerId*/
HealPlayerParty = 0x080a002c|1;
GetMapName = 0x080c4d4c|1;
DrawStdFrameWithCustomTileAndPalette = 0x0810f2c0|1;
ResetTempTileDataBuffers = 0x080f67e0|1;
FreeTempTileDataBuffersIfPossible = 0x080f6804|1;
DecompressAndCopyTileDataToVram = 0x080f6850|1;
AddTextPrinterParameterized3 = 0x0812e4f4|1;
CopyItemIconPicTo4x4Buffer = 0x08098700|1;
CheckForPlayerAvatarCollision = 0x0805bb1c|1;
PlayerNotOnBikeMoving = 0x0805b9d4|1;
udivsi3 = 0x081e45e8|1;
umodsi3 = 0x081e4660|1;
memcpy = 0x081e5e54|1;
GetHealLocation = 0x080bfc84|1;
ExpandBattleTextBuffPlaceholders = 0x080d83ec|1;
ItemUseCB_RareCandy = 0x08126284|1;


throughWallFlag = 0x0203f465;


gSpecialVar_0x8004 = 0x020370c0;
gPaletteFade = 0x02037ab8;
gSprites = 0x0202063c;
gPlttBufferUnfaded = 0x020371f8;
BG_PaletteMem = 0x020371f8;
OBJ_PaletteMem = 0x020371f8+0x200;
gPlttBufferFaded = 0x020375f8;
BG_PaletteMem2 = 0x020375f8;
OBJ_PaletteMem2 = 0x020375f8+0x200;

gPlayerParty = 0x02024284;
gPlayerPartyCount = 0x02024029;

gBagPockets = 0x0203988c;

gStringVar1 = 0x02021cd0;

gSaveBlock1Ptr = 0x03005008;
gSaveBlock2Ptr = 0x0300500c;

gMain = 0x030030f0;
gTasks = 0x03005090;

gMonFrontPicTablePtr = 0x8000128; /*精灵正面图*/
gMonPaletteTablePtr = 0x8000130; /*精灵普通调色板*/
gMonIconTablePtr = 0x8000138; /*精灵小图标*/
gMonIconPaletteIndicesPtr = 0x800013C; /*精灵小图标调色板编号*/
gMonIconPaletteTablePtr = 0x8000140; /*精灵小图标调色板*/
gSpeciesNamesPtr = 0x8000144; /*精灵种族名字*/
gMoveNamesPtr = 0x08000148; /*技能名称*/
gSpeciesInfoPtr = 0x080001BC; /*精灵种族值*/
gItemsPtr = 0x080001C8; /*道具表*/
gBattleMovesPtr = 0x080001CC; /*技能表*/
gItemIconTablePtr = 0x08098970; /*道具图标*/

ItemUseOutOfBattle_Repel = 0x080a196c|1; /*FieldUseFunc_Repel*/

sDiplomaPalettes = 0x08415790; /*sDiplomaPal*/
sDiplomaTilemap = 0x08415324; /*sDiplomaTilemap*/
sDiplomaTiles = 0x084145fc; /*sDiplomaGfx*/
sWindowFrames = 0x08471768; /*gUserFrames*/

sStartMenuItems = 0x083a7324; /*sStartMenuActionTable*/

HandleStartMenuInput = 0x0806f394|1; /*StartMenu_FadeScreenIfLeavingOverworld*/


