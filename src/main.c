#include "header/funcs.h"

extern void obj_callback();
extern void task_loader(u8);
extern u32 GetMonData(struct Pokemon* poke_address, u8 request);
void MainCB2(void);
void initMonTempData();
void loadMonName();
void loadMonIconSprite();
void loadMonIconTiles(u16 species);
void loadMonIsShiny();
void loadMonGender(u16 species);
u32 getCurrentMonData(u8 request);
struct Pokemon *getCurrentPartyplayer();
struct BaseStats* getSpeciesBaseStats(u16 species);
struct Sprite *getSprite(u8 id);
u32 getMonSpeciesName(u16 species);
u32 getItemName(u16 itemId);
void backupMonTempData();

void main_func()
{
	*malloc_pointer_loc = (u8 *) AllocZeroed(0x1004);
	ResetSpriteData();
	ResetPaletteFade();
	FreeAllSpritePalettes();
	mySav->task_id = CreateTask(task_loader,1);
	SetMainCallback2(MainCB2);
	return;
}

void MainCB2()
{
	RunTasks();
	AnimateSprites();
	BuildOamBuffer();
	UpdatePaletteFade();
	return;
}

/**
 * 获取精灵最大等级
*/
u8 getMonMaxLevel(){
	int fun = ItemUseCB_RareCandy;
	#ifdef BPRE0
	fun += 0x25;
	#elif AXVE0
	fun += 0x27;
	#else
	fun += 0x35;
	#endif
	u8 maxLvl = ((u8*) fun)[0];
	return maxLvl;
}

/**
 * 初始化精灵临时数据
*/
void initMonTempData(){
	myTempData->maxLvl = getMonMaxLevel();
	myTempData->PID = getCurrentMonData(ATTR_PID);
	myTempData->TID = getCurrentMonData(ATTR_TID);
	myTempData->egg = getCurrentMonData(ATTR_IS_EGG);
	myTempData->lvl = getCurrentMonData(ATTR_LEVEL);
	myTempData->ability = getCurrentMonData(ATTR_ABILITY_BIT);
	myTempData->happiness = getCurrentMonData(ATTR_HAPPINESS);

	myTempData->nature = umodsi3(myTempData->PID,25);
	u16 species = getCurrentMonData(ATTR_SPECIES);
	myTempData->species = species;
	loadMonGender(species);
	loadMonIsShiny();
	loadMonIconSprite();

	loadMonName();
	backupMonTempData();
}
/**
 * 备份精灵临时数据
*/
void backupMonTempData(){
	CpuSet(&myTempData->party,&myTempData->party_2,6);
}
/**
 * 刷新精灵临时数据
*/
void refreshMonTempData(){
	CpuSet(&myTempData->party_2,&myTempData->party,6);
}
/**
 * 加载精灵名字
*/
void loadMonName(){
    struct Pokemon *party =	getCurrentPartyplayer();
	StringCopy(textBuffer->monName,party->nickname);
	u8* nameStr = textBuffer->monName;
	nameStr[10] = 0xFF;
	u8 len = 0;
	while(nameStr[len] != 0xFF){
		len++;
	}
	nameStr[len] = 0xBA;
	nameStr[0x1F] = len;
	StringCopy(nameStr+len+1,getMonSpeciesName(myTempData->species));
}
/**
 * 获取种族名字
*/
u32 getMonSpeciesName(u16 species){
	u32 speciesNames = gSpeciesNamesPtr;
	return speciesNames + 0xB*species;
}
/**
 * 加载精灵小图标
*/
void loadMonIconSprite(){
	u16 species = getCurrentMonData(ATTR_SPECIES_2);
	u32 monIconPaletteIndices = gMonIconPaletteIndicesPtr;
	u32 monIconPaletteIndex = ((u8*)(myTempData->species+monIconPaletteIndices))[0];
	monIconPaletteIndex += 1;
	
	loadMonIconTiles(species);
	struct Sprite* sprites = getSprite(mySav->monIconId);
	sprites->oam.paletteNum = monIconPaletteIndex;
}

struct Sprite *getSprite(u8 id){
	return &gSprites[id];
}

void loadMonIconTiles(u16 species){
	u32* gMonIconTable = gMonIconTablePtr;
	u32 monIconOffset = gMonIconTable[species];
	CpuSet(monIconOffset,0x06010400,0x200);
}

void loadMonIsShiny(){
	u16* pid = (u16*)&myTempData->PID;
	u16 pidXor = pid[0]^pid[1];
	u16* tid = (u16*)&myTempData->TID;
	u16 tidXor = tid[0]^tid[1];
	if ((pidXor^tidXor) > 8){
		myTempData->shiny = FALSE;
	}
	else{
		myTempData->shiny = TRUE;
	}
}

void loadMonGender(u16 species){
	struct BaseStats* baseStats = getSpeciesBaseStats(species);
	u8 genderRatio = baseStats->genderRatio;
	u8 gender;
	switch (genderRatio){
		case 0xFF:
			gender = GENDER_NONE;
			break;
		case 0xFE:
			gender = GENDER_ALL_FEMALE;
			break;
		case 0:
			gender = GENDER_ALL_MALE;
			break;
		
		default:{
			u8 flag = myTempData->PID & 0xFF;
			if (flag > genderRatio){
				gender = GENDER_MALE;
			}
			else{
				gender = GENDER_FEMALE;
			}
		}break;
	}
	myTempData->sex = gender;	
}

u32 getCurrentMonData(u8 request){
	return GetMonData(getCurrentPartyplayer(),request);
}

void setCurrentMonData(u8 request, void* value){
	SetMonData(getCurrentPartyplayer(),request,value);
}

void RefreshCurrentMonData(){
	CalculateMonStats(getCurrentPartyplayer());
}

/**
 * 获取当前精灵数据
*/
struct Pokemon *getCurrentPartyplayer(){
	return &gPlayerParty[myTempData->party];
}

/**
 * 获取种族值数据
*/
struct BaseStats* getSpeciesBaseStats(u16 species){
	u32 gBaseStats = gBaseStatsPtr;
	gBaseStats += (0x1C*species);
	return (struct BaseStats*)gBaseStats;
}

/**
 * 播放声音
 * @param soundID 声音ID
*/
void PlaySound(u16 soundID){
	if(myTempData->soundMute){
		myTempData->soundMute = FALSE;
	}
	else
		PlaySE(soundID);
}

/**
 * 获取战斗文本缓存
*/
u32 getBattleTextBuff(u8 type,u8 value){
	CpuFastFill(-1,textBuffer->temp,16);
	u8 data[] = {0,type,value,0xFF};
	ExpandBattleTextBuffPlaceholders(data,textBuffer->temp);
	return textBuffer->temp;
}

/**
 * 获取技能名称地址
 * @param atackNum 技能编号
 * @return 技能名称地址，如果不存在则返回0
*/
u32 getAttackName(u16 atackNum){
	u32 moveNames = gMoveNamesPtr;
	moveNames += (atackNum*gNameLengthConfig.moveNameLength);
	return moveNames;
}

u32 getItemName(u16 itemId){
	struct Item *itemTable = (struct Item *)((u32*)gItemsPtr);
	struct Item *item = itemTable + itemId;
	return item->name;
}

/**
 * 检查名字字符串是否有效
*/
bool8 checkNameString(u8 *str,u32 length){
	u8 firstChar = str[0];
	if(firstChar == 0 || firstChar == 0xAE || firstChar == 0xFF){
		return FALSE;
	}
	for (int i = 1; i < length; i++){
		if(str[i] == 0xFF){
			return TRUE;
		}
	}
	return FALSE;
}

u32 getMonSpeciesNameValid(u16 species){
	u32 limit = gQuantityLimit.pokemonCount;
	if (limit != 0){
		return species < limit;
	}
	u32 name = getMonSpeciesName(species);
	if (checkNameString(name,gNameLengthConfig.pokemonNameLength)){
		return name;
	}
	return 0;
}

u32 getAttackNameValid(u16 atackNum){
	u32 limit = gQuantityLimit.moveCount;
	if (limit != 0){
		return atackNum < limit;
	}
	u32 name = getAttackName(atackNum);
	if (checkNameString(name,gNameLengthConfig.moveNameLength)){
		return name;
	}
	return 0;
}

u32 getItemNameValid(u16 itemId){
	u32 limit = gQuantityLimit.itemCount;
	if (limit != 0){
		return itemId < limit;
	}

	u8 *name = getItemName(itemId);


	u8 firstChar = name[0];
	if(firstChar == 0x3D || firstChar == 0xAC || firstChar == 0xAE){
		return ITEM_NAME_TEMP;
	}
	u8 nameLen = gNameLengthConfig.itemNameLength;

	if(name[nameLen] == itemId){
		return name;
	}

	if(checkNameString(name,nameLen)){
		return name;
	}

	return ITEM_NAME_NONE;
}




