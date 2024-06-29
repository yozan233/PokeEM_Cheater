SetMainCallback2 = 0x080003cc|1;
SetVBlankCallback = 0x08000540|1;
gBGTilemapBuffers = 0x020211cc;

Text_LoadWindowTemplate = 0x08002a34|1;
InitMenuWindow = 0x08071c4c|1;

ScanlineEffect_Stop = 0x08089578|1;
Menu_DrawStdWindowFrame = 0x08071f08|1;
Menu_BlankWindowRect = 0x08071ebc|1;
Menu_EraseWindowRect = 0x08071e84|1;
ResetSpriteData = 0x08000748|1;
CreateSprite = 0x08000bdc|1;
FreeAllSpritePalettes = 0x080025c8|1;
StringCopy = 0x08006ab0|1;
StringCompare = 0x08006b74|1;
ConvertIntToDecimalStringN = 0x08006bc4|1;
ConvertIntToHexStringN = 0x08006d28|1;
VBlankCB_SelectScreen = 0x08145d74|1;
RtcInitLocalTimeOffset = 0x080095e0|1;
ZeroMonData = 0x0803a6d8|1;
CreateMon = 0x0803a798|1;
CalculateBoxMonChecksum = 0x0803b124|1;
CalculateMonStats = 0x0803b1b8|1;
EncryptBoxMon = 0x0803c5f0|1;
DecryptBoxMon = 0x0803c614|1;
GetMonData = 0x0803cb60|1;
SetMonData = 0x0803d1fc|1;
GiveMonToPlayer = 0x0803d91c|1;
SpeciesToNationalPokedexNum = 0x0803f898|1;
Random = 0x08040e84|1;
GetMapHeaderByGroupAndId = 0x08053310|1;
SetWarpDestination = 0x08053454|1;
ResetInitialPlayerAvatarState = 0x08053a3c|1;
CB2_ReturnToFieldContinueScript = 0x080546d4|1;
ScriptContext_SetupScript = 0x080655b8|1; /*ScriptContext1_SetupScript*/
EnableNationalPokedex = 0x080690f0|1;
VarGet = 0x08069254|1;
VarSet = 0x08069270|1;
StartMenuExitCallback = 0x08071554|1; /*StartMenu_ExitCallback*/
LoadPalette = 0x08073a58|1;
MainCB2 = 0x8145EFC|1;
ResetPaletteFade = 0x08073b94|1;
BeginNormalPaletteFade = 0x08073bf4|1;
PlaySE = 0x08075494|1;
CreateTask = 0x0807aa88|1;
DestroyTask = 0x0807ab74|1;
DoWarp = 0x08080e88|1; /*sub_8080E88*/
GetSetPokedexFlag = 0x08090d90|1;
ClearItemSlots = 0x080A9684|1;
AddBagItem = 0x080a9424|1;
GetPlayerIDAsU32 = 0x080bfb94|1; /*GetPlayerTrainerId*/
HealPlayerParty = 0x080c52b0|1;
GetMapName = 0x080fbff8|1; /*CopyMapName*/

CheckForPlayerAvatarCollision = 0x08058db4|1;
PlayerNotOnBikeMoving = 0x08058D0C|1; /*sub_8058D0C*/
udivsi3 = 0x081e0e90|1;
umodsi3 = 0x081e0f08|1;
memcpy = 0x081e26fc|1;
GetHealLocation = 0x080fa8cc|1;
ExpandBattleTextBuffPlaceholders = 0x08121a68|1;
ItemUseCB_RareCandy = 0x08070680|1; /*DoRareCandyItemEffect*/

Menu_PrintTextPixelCoords = 0x080729d8|1;


throughWallFlag = 0x02024e6d;


gSpecialVar_0x8004 = 0x0202e8cc;
gPaletteFade = 0x0202f388;
gSprites = 0x02020004;
gPlttBufferUnfaded = 0x0202eac8;
gPlttBufferFaded = 0x0202eec8;

gPlayerParty = 0x03004360; /*精灵队伍*/
gPlayerPartyCount = 0x03004350; /*精灵数量*/

gBagPockets = 0x083c1618;

gStringVar1 = 0x020231cc;

gSaveBlock2 = 0x02024ea4;
gSaveBlock1 = 0x02025734;

gLocalTime = 0x03004038;
gMain = 0x03001770;
gTasks = 0x03004b20;

gMonFrontPicTablePtr = 0x0800D324; /*精灵正面图*/
gMonPaletteTablePtr = 0x08040954; /*精灵普通调色板*/
gMonIconTablePtr = 0x08099AA0; /*精灵小图标*/
gMonIconPaletteIndicesPtr = 0x08099BB0; /*精灵小图标调色板编号*/
gMonIconPaletteTablePtr = 0x0809D53C; /*精灵小图标调色板*/
gSpeciesNamesPtr = 0x0800FA58; /*精灵种族名字*/
gMoveNamesPtr = 0x0802E18C; /*技能名称*/
gSpeciesInfoPtr = 0x08010B64; /*精灵种族值*/
gItemsPtr = 0x080A98F0; /*道具表*/
gBattleMovesPtr = 0x0800CA54; /*技能表*/

ItemUseOutOfBattle_Repel = 0x080ca014|1;

sDiplomaPalettes = 0x0840cb0c; /*gDiplomaPalettes*/
sDiplomaTilemap = 0x0840cb4c; /*gDiplomaTilemap*/
sDiplomaTiles = 0x0840d288; /*gDiplomaTiles*/

sStartMenuItems = 0x08376D24;
HandleStartMenuInput = 0x08071338|1; /*StartMenu_InputProcessCallback*/

