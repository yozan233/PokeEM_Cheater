SetMainCallback2 = 0x806F0CC|1;
SetVBlankCallback = 0x806F290|1;
Alloc = 0x836717C|1;
AllocZeroed = 0x83671A4|1;
Free = 0x83671CC|1;
SetGpuReg = 0x8367394|1;
InitBgsFromTemplates = 0x8362850|1;
LoadBgTiles = 0x8362AEA|1;
ShowBg = 0x8362E78|1;
ChangeBgX = 0x8363124|1;
ChangeBgY = 0x8363350|1;
SetBgTilemapBuffer = 0x83639CC|1;
CopyToBgTilemapBuffer = 0x8363AB4|1;
CopyBgTilemapBufferToVram = 0x8363B5C|1;
InitWindows = 0x8364D8A|1;
AddWindow = 0x83650A0|1;
FreeAllWindowBuffers = 0x8365598|1;
PutWindowTilemap = 0x8365834|1;
FillWindowPixelRect = 0x8365E78|1;
FillWindowPixelBuffer = 0x8365FD8|1;
DeactivateAllTextPrinters = 0x836B84C|1;
AddTextPrinterParameterized = 0x836B88C|1;
ResetSpriteData = 0x8367780|1;
CreateSprite = 0x8367F5C|1;
FreeAllSpritePalettes = 0x836B044|1;
StringCopy = 0x836FD7A|1;
StringCompare = 0x836FF0C|1;
ConvertIntToDecimalStringN = 0x837000A|1;
ConvertIntToHexStringN = 0x837025C|1;
VBlankCB_SelectScreen = 0x81057DC|1;
MainCB2 = 0x81059C8|1;
RtcInitLocalTimeOffset = 0x81DBC64|1;
ZeroMonData = |1;
CreateMon = |1;
CalculateBoxMonChecksum = |1;
CalculateMonStats = |1;
EncryptBoxMon = |1;
DecryptBoxMon = |1;
GetMonData = 0x8062A70|1;
SetMonData = |1;
GiveMonToPlayer = |1;
SpeciesToNationalPokedexNum = |1;
Random = |1;
GetMapHeaderByGroupAndId = |1;
SetWarpDestination = |1;
ResetInitialPlayerAvatarState = |1;
CB2_ReturnToFieldContinueScript = |1;
ScriptContext_SetupScript = |1;
EnableNationalPokedex = 0x801F464|1;
VarGet = 0x801F7D4|1;
VarSet = 0x801F80A|1;
StartMenuExitCallback = |1;
LoadPalette = 0x8048C5C|1;
ResetPaletteFade = 0x8048E64|1;
BeginNormalPaletteFade = 0x8048F0C|1;
PlaySE = |1;
CreateTask = 0x823F9D0|1;
DestroyTask = 0x823FC50|1;
DoWarp = |1;
GetSetPokedexFlag = |1;
RemoveBagItem = |1;
AddBagItem = |1;
GetPlayerIDAsU32 = 0x8204F02|1;
HealPlayerParty = 0x83345EC|1;
GetMapName = |1;
DrawStdFrameWithCustomTileAndPalette = |1;
ResetTempTileDataBuffers = 0x80E0AE0|1;
FreeTempTileDataBuffersIfPossible = 0x80E0B1C|1;
DecompressAndCopyTileDataToVram = 0x80E0B84|1;
AddTextPrinterParameterized3 = |1;
CopyItemIconPicTo4x4Buffer = |1;
CheckForPlayerAvatarCollision = |1;
PlayerNotOnBikeMoving = |1;
udivsi3 = |1;
umodsi3 = |1;
memcpy = |1;
GetHealLocation = |1;
ExpandBattleTextBuffPlaceholders = |1;
ItemUseCB_RareCandy = |1;


gSpecialVar_0x8004 = 0x201C01C;
gPaletteFade = 0x201CA7C;
gSprites = ;
gPlttBufferUnfaded = ;
BG_PaletteMem = ;
OBJ_PaletteMem = +0x200;
gPlttBufferFaded = ;
BG_PaletteMem2 = ;
OBJ_PaletteMem2 = +0x200;

gPlayerParty = 0x201D074; /*精灵队伍*/
gPlayerPartyCount = 0x201D071; /*精灵数量*/

gBagPockets = ;


gStringVar1 = 0x2023660;
throughWallFlag = 0x202365F;


gSaveBlock1Ptr = 0x3007468;
gSaveBlock2Ptr = 0x3007464;

gLocalTime = 0x30054A8;
gMain = 0x3003E18;
gTasks = 0x3005544;

gMonFrontPicTablePtr = ; /*精灵正面图*/
gMonPaletteTablePtr = ; /*精灵普通调色板*/
gMonIconTablePtr = ; /*精灵小图标*/
gMonIconPaletteIndicesPtr = ; /*精灵小图标调色板编号*/
gMonIconPaletteTablePtr = ; /*精灵小图标调色板*/
gSpeciesNamesPtr = ; /*精灵种族名字*/
gMoveNamesPtr = ; /*技能名称*/
gBaseStatsPtr = ; /*精灵种族值*/
gItemsPtr = ; /*道具表*/
gBattleMovesPtr = ; /*技能表*/
gItemIconTablePtr = ; /*道具图标*/

ItemUseOutOfBattle_Repel = |1;

sDiplomaPalettes = 0x898D6D4;
sDiplomaTilemap = 0x898D714;
sDiplomaTiles = 0x898DE50;
sWindowFrames = ;

sStartMenuItems = ;
HandleStartMenuInput = |1;

