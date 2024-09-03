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
RtcInitLocalTimeOffset = 0x81DBD2C|1;
ZeroMonData = 0x8060238|1;
CreateMon = 0x8370E54|1;
CalculateBoxMonChecksum = 0x8061724|1;
CalculateMonStats = 0x806174A|1;
EncryptBoxMon = 0x80629E4|1;
DecryptBoxMon = 0x8062A72|1;
GetMonData = 0x8062A70|1;
SetMonData = 0x8062BB8|1;
GiveMonToPlayer = 0x806461E|1;
SpeciesToNationalPokedexNum = 0x8067BB4|1;
Random = 0x82A32AC|1;
GetMapHeaderByGroupAndId = 0x8317C88|1;
SetWarpDestination = 0x8317EBE|1;
ResetInitialPlayerAvatarState = 0x8318954|1;
CB2_ReturnToFieldContinueScript = 0x831A00C|1;
/*ScriptContext_SetupScript = |1;*/
EnableNationalPokedex = 0x801F464|1;
VarGet = 0x801F7D4|1;
VarSet = 0x801F80A|1;
/*StartMenuExitCallback = |1;*/
LoadPalette = 0x8048C5C|1;
MainCB2 = 0x81059C8|1;
ResetPaletteFade = 0x8048E64|1;
BeginNormalPaletteFade = 0x8048F0C|1;
PlaySE = 0x814DC38|1;
CreateTask = 0x823F9D0|1;
DestroyTask = 0x823FC50|1;
DoWarp = 0x830BB12|1;
GetSetPokedexFlag = 0x8181798|1;
ClearItemSlots = 0x8150558|1;
AddBagItem = 0x8150234|1;
GetPlayerIDAsU32 = 0x8204F02|1;
HealPlayerParty = 0x83345EC|1;
GetMapName = 0x8249BD0|1;
DrawStdFrameWithCustomTileAndPalette = 0x80DD992|1;
ResetTempTileDataBuffers = 0x80E0AE0|1;
FreeTempTileDataBuffersIfPossible = 0x80E0B1C|1;
DecompressAndCopyTileDataToVram = 0x80E0B84|1;
AddTextPrinterParameterized3 = 0x80E11B6|1;
/*CopyItemIconPicTo4x4Buffer = |1;*/
CheckForPlayerAvatarCollision = 0x80B3134|1;
PlayerNotOnBikeMoving = 0x80B2FE6|1;
udivsi3 = 0x806F760|1;
umodsi3 = 0x8464A7C|1;
memcpy = 0x8466080|1;
GetHealLocation = 0x82357CC|1;
ExpandBattleTextBuffPlaceholders = 0x8122F44|1;


/*ItemUseCB_RareCandy = |1;*/
sItemUseOnFieldCB = 0x201EE64;
SetUpItemUseOnFieldCallback = 0x816F6AC|1;


gSpecialVar_0x8004 = 0x201C01C;
gPaletteFade = 0x201CA7C;
gSprites = 0x203B4A0;
gPlttBufferUnfaded = 0x0201C1BC;
gPlttBufferFaded = 0x0201C5BC;

gPlayerParty = 0x201D074; /*精灵队伍*/
gPlayerPartyCount = 0x201D071; /*精灵数量(精灵队伍-0x3)*/

gBagPockets = 0x201EDF8;


gStringVar1 = 0x2023660;
throughWallFlag = 0x202365f;

gSaveBlock1Ptr = 0x3007468;
gSaveBlock2Ptr = 0x3007464;

gLocalTime = 0x30054A8;
gMain = 0x3003E18;
gTasks = 0x3005544;

gMonFrontPicTablePtr = 0x81B0264; /*精灵正面图*/
gMonPaletteTablePtr = 0x8069940; /*精灵普通调色板*/
gMonShinyPaletteTablePtr = 0x806993C; /*精灵闪光调色板*/
gMonIconTablePtr = 0x81F7010; /*精灵小图标*/
gMonIconPaletteIndicesPtr = 0x81F70A8; /*精灵小图标调色板编号*/
gMonIconPaletteTablePtr = 0x81F706C; /*精灵小图标调色板*/
gSpeciesNamesPtr = 0x8064E24; /*精灵种族名字*/
gMoveNamesPtr = 0x81F9E80; /*技能名称*/
gSpeciesInfoPtr = 0x8062750; /*精灵种族值*/
gItemsPtr = 0x8151BB4; /*道具表*/
gBattleMovesPtr = 0x8061FD4; /*技能表*/
gItemIconTablePtr = 0x80819FC; /*道具图标*/

/*ItemUseOutOfBattle_Repel = |1;*/

sDiplomaPalettes = 0x898D6D4;
sDiplomaTilemap = 0x898D714;
sDiplomaTiles = 0x898DE50;
sWindowFrames = 0x8A9A1A4;

/*sStartMenuItems = ;*/
/*HandleStartMenuInput = |1;*/

ItemUseOutOfBattle_Potion_Type = 0x89C6F87;
ItemUseOutOfBattle_Potion_Ptr = 0x89C6F88;

ItemUseOutOfBattle_Wristband_Type = 0x89CEB47;
ItemUseOutOfBattle_Wristband_Ptr = 0x89CEB48;


CreateMonIcon = 0x81F6A74|1;
DestroySprite = 0x836852E|1;
CreateMonIconSprite = 0x81F7290|1;
TryLoadAllMonIconPalettesAtOffset = 0x81F7014|1;
LoadWindowGfx = 0x8276D62|1;
GetGenderFromSpeciesAndPersonality = 0x8062754|1;
SetMonMoveSlot = 0x8061F80|1;
GetAbilityBySpecies = 0x8064A58|1;
RemoveBagItem = 0x81503A8|1;
BagGetItemIdByPocketPosition = 0x8150A98|1;


