SetMainCallback2 = 0x08000541;
SetVBlankCallback = 0x80006F0|1;
Alloc = 0x08000B38|1;
AllocZeroed = 0x8000B4C|1;
Free = 0x8000B60|1;
SetGpuReg = 0x80010B4|1;
InitBgsFromTemplates = 0x80017E8|1;
LoadBgTiles = 0x8001944|1;
ShowBg = 0x8001B30|1;
ChangeBgX = 0x8001D04|1;
ChangeBgY = 0x8001E7C|1;
SetBgTilemapBuffer = 0x8002250|1;
CopyToBgTilemapBuffer = 0x80022F0|1;
CopyBgTilemapBufferToVram = 0x800236C|1;
InitWindows = 0x80031C0|1;
AddWindow = 0x8003380|1;
FreeAllWindowBuffers = 0x8003604|1;
PutWindowTilemap = 0x800378C|1;
FillWindowPixelRect = 0x08003b64|1;
FillWindowPixelBuffer = 0x8003C48|1;
DeactivateAllTextPrinters = 0x80045B0|1;
AddTextPrinterParameterized = 0x80045D0|1;
ResetSpriteData = 0x8006974|1;
AnimateSprites = 0x80069C0|1;
BuildOamBuffer = 0x8006A0C|1;
CreateSprite = 0x8006DF4|1;
FreeAllSpritePalettes = 0x800870C|1;
StringCopy = 0x8008BA0|1;
StringCompare = 0x08008c44|1;
ConvertIntToDecimalStringN = 0x8008CC0|1;
ConvertIntToHexStringN = 0x08008e20|1;
VBlankCB_SelectScreen = 0x80096BC|1;
RtcInitLocalTimeOffset = 0x0802f5b4|1;
ZeroMonData = 0x08067a8c|1;
CreateMon = 0x08067B4C|1;
CalculateBoxMonChecksum = 0x8068c78|1;
CalculateMonStats = 0x08068D0C|1;
EncryptBoxMon = 0x806a228|1;
DecryptBoxMon = 0x0806a24c|1;
GetMonData = 0x0806A518|1;
SetMonData = 0x0806ACAC|1;
GiveMonToPlayer = 0x0806b414|1;
SpeciesToNationalPokedexNum = 0x0806d4a4|1;
Random = 0x0806F5CC|1;
GetMapHeaderByGroupAndId = 0x08084a90|1;
SetWarpDestination = 0x08084bec|1;
ResetInitialPlayerAvatarState = 0x08085268|1;
CB2_ReturnToFieldContinueScript = 0x80861B0|1;
ScriptContext_SetupScript = 0x08098ef8|1;
EnableNationalPokedex = 0x0809D3E8|1;
VarGet = 0x0809D694|1;
VarSet = 0x0809d6b0|1;
FlagSet = 0x0809D740|1;
StartMenuExitCallback = 0x0809FD64|1;
LoadPalette = 0x80A1938|1;
UpdatePaletteFade = 0x80A1A1C|1;
ResetPaletteFade = 0x80A1A74|1;
BeginNormalPaletteFade = 0x80A1AD4|1;
PlaySE = 0x080A37A4|1;
CreateTask = 0x80A8FB0|1;
DestroyTask = 0x80A909C|1;
RunTasks = 0x080A910C|1;
DoWarp = 0x080af734|1;
GetSetPokedexFlag = 0x080c0664|5;
RemoveBagItem = 0x080d6aa4|1;
AddBagItem = 0x080D6928|1;
GetPlayerIDAsU32 = 0x080F0020|1;
HealPlayerParty = 0x080F9180|1;
GetMapName = 0x0812456C|1;
DrawStdFrameWithCustomTileAndPalette = 0x8197E80|1;
ResetTempTileDataBuffers = 0x8199A20|1;
FreeTempTileDataBuffersIfPossible = 0x8199A44|1;
DecompressAndCopyTileDataToVram = 0x8199A90|1;
AddTextPrinterParameterized3 = 0x8199E64|1;
CopyItemIconPicTo4x4Buffer = 0x81afe44|1;
CheckForPlayerAvatarCollision = 0x0808AFBC|1;
PlayerNotOnBikeMoving = 0x0808af00|1;
udivsi3 = 0x082e7b68|1;
umodsi3 = 0x082E7BE0|1;
memcpy = 0x082E93D4|1;
GetHealLocation = 0x08122cbc|1;
ExpandBattleTextBuffPlaceholders = 0x0814f648|1;
ItemUseCB_RareCandy = 0x081b7404|1;


throughWallFlag = 0x020322d6;


gSpecialVar_0x8004 = 0x020375E0;
gPaletteFade = 0x02037FD4;
gSprites = 0x02020630;
gPlttBufferUnfaded = 0x02037714;
BG_PaletteMem = 0x02037714;
OBJ_PaletteMem = 0x02037714+0x200;
gPlttBufferFaded = 0x02037b14;
BG_PaletteMem2 = 0x02037b14;
OBJ_PaletteMem2 = 0x02037b14+0x200;

gPlayerParty = 0x020244EC; /*精灵队伍*/
gPlayerPartyCount = 0x020244E9; /*精灵数量*/

gBagPockets = 0x02039dd8;

gStringVar4 = 0x02021fc4;

gSaveBlock1Ptr = 0x03005D8C;
gSaveBlock2Ptr = 0x03005d90;

gLocalTime = 0x03005cf8;
gMain = 0x030022C0;
gTasks = 0x03005E00;

gMonFrontPicTablePtr = 0x8000128; /*精灵正面图*/
gMonPaletteTablePtr = 0x8000130; /*精灵普通调色板*/
gMonIconTablePtr = 0x8000138; /*精灵小图标*/
gMonIconPaletteIndicesPtr = 0x800013C; /*精灵小图标调色板编号*/
gMonIconPaletteTablePtr = 0x8000140; /*精灵小图标调色板*/
gSpeciesNamesPtr = 0x8000144; /*精灵种族名字*/
gMoveNamesPtr = 0x08000148; /*技能名称*/
gBaseStatsPtr = 0x080001BC; /*精灵种族值*/
gAbilityNamesPtr = 0x080001C0; /*特性名字*/
gItemsPtr = 0x080001C8; /*道具表*/
gBattleMovesPtr = 0x080001CC; /*技能表*/
gItemIconTablePtr = 0x081B0034; /*道具图标*/

ItemUseOutOfBattle_Repel = 0x080fe0bc|1;

sCursor_Gfx = 0x08570BA8;
gFrontierPassCursor_Pal = 0x08dc1674;
sDiplomaPalettes = 0x085e7088;
sDiplomaTilemap = 0x085e70c8;
sDiplomaTiles = 0x085e7804;
sWindowFrames_offset = 0x851021c;

sStartMenuItems = 0x08510540;
HandleStartMenuInput = 0x0809fac4|1;

