#include "header/data.h"

extern void task_loader(u8);
extern u32 GetMonData(struct Pokemon* poke_address, u8 request, const void* data);
extern u8 CreateMyMonIcon(u16 species);
void initMonTempData();
void loadMonName();
void loadMonIconSprite();
void loadMonIconTiles(u16 species);
void loadMonIsShiny();
void loadMonGender(u16 species);
u32 getCurrentMonData(u8 request);
struct Pokemon *getCurrentPlayerParty();
struct Sprite *getSprite(u8 id);
u8 *getMonSpeciesName(u16 species);
u8 *getItemName(u16 itemId);
void backupMonTempData();

void main_func(u8 taskId)
{
	*malloc_pointer_loc = (u8 *) AllocZeroed(0x1004);
    ResetAllSpriteData();
	mySav->task_id = CreateTask(task_loader,1);
	SetMainCallback2(MainCB2);
    DestroyTask(taskId);
}

void ItemUseOutOfBattle_Cheater(u8 taskId){
    sItemUseOnFieldCB[0] = main_func;
    SetUpItemUseOnFieldCallback(taskId);
}

/**
 * 获取精灵最大等级
*/
u8 getMonMaxLevel(){
//    void* fun = ItemUseCB_RareCandy;
//	#ifdef FIRE_RED_LEAF_GREEN
//	fun += 0x25;
//	#elif RUBY_SAPPHIRE
//	fun += 0x27;
//	#else
//	fun += 0x35;
//	#endif
//	u8 maxLvl = ((u8*) fun)[0];
//	return maxLvl;
    return 100;
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
    struct Pokemon *party =	getCurrentPlayerParty();
    struct TextBuffer *textBuffer = &myTempData->textBuffer;
    GetMonData(party,ATTR_NAME,&textBuffer->monName);
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
u8 *getMonSpeciesName(u16 species){
	u32 speciesNames = gSpeciesNamesPtr[0];
	return (u8*)(speciesNames + 0xB*species);
}

void destroyMonIconSprite(){
    u8 id = mySav->monIconId;
    if(id){
        struct SpriteFrameImage image = { NULL, 32 * 32 / 2 };
        getSprite(id)->images = &image;

        DestroySprite(getSprite(id));
        mySav->monIconId = 0;
    }
}

/**
 * 加载精灵小图标
*/
void loadMonIconSprite(){
	u16 species = getCurrentMonData(ATTR_SPECIES_2);
//	u32 monIconPaletteIndices = gMonIconPaletteIndicesPtr[0];
//	u32 monIconPaletteIndex = ((u8*)(myTempData->species+monIconPaletteIndices))[0];
//	monIconPaletteIndex += 1;
//
//	loadMonIconTiles(species);
//	struct Sprite* sprites = getSprite(mySav->monIconId);
//	sprites->oam.paletteNum = monIconPaletteIndex;

//    //menuBox->monSpriteId = CreateMonIcon(species, SpriteCB_MonIcon, menuBox->spriteCoords[0], menuBox->spriteCoords[1], 4, pid, handleDeoxys);
//    mySav->monIconId = CreateMonIcon(species,debug,0x1A,0x4,4,0,0);

//    mySav->monIconId = CreateMonIconSprite(&gMonIconTemplate, 0x1A,0x4, 4);

    destroyMonIconSprite();
    mySav->monIconId = CreateMyMonIcon(species);

}

struct Sprite *getSprite(u8 id){
	return &gSprites[id];
}

/**
 * 加载精灵图标图块
 * @param species 种族编号
 */
void loadMonIconTiles(u16 species){
	u32* gMonIconTable = gMonIconTablePtr;
	u32 monIconOffset = gMonIconTable[species];
	CpuSet((void *) monIconOffset, (void *) 0x06010400, 0x200);
}

/**
 * 加载精灵是否闪光
 */
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

u8 CalcGender2(u16 species, u32 personality){
    u8 genderRatio = GetGenderFromSpeciesAndPersonality(species,personality);
    if (genderRatio == 0xFF){
        return GENDER_NONE;
    }

    //当 flag < 1 时，代码恒返回 0xFE。
    //当 flag >= 0xFE 时，代码恒返回 0x00。
    //所以当genderRatio等于0xFE时flag取0xFF，否则flag取0x00
    u8 flag = genderRatio == 0xFE ? 0xFF : 0x00;

    u8 genderRatio2 = GetGenderFromSpeciesAndPersonality(species,flag);
    if (genderRatio == genderRatio2){
        return genderRatio == 0xFE ? GENDER_ALL_FEMALE : GENDER_ALL_MALE;
    }

    return genderRatio == 0xFE ? GENDER_FEMALE : GENDER_MALE;
}

/**
 * 加载精灵性别
 * @param species 种族编号
 */
void loadMonGender(u16 species){
	myTempData->sex = CalcGender2(species,myTempData->PID);
}

u32 getCurrentMonData(u8 request){
	return GetMonData(getCurrentPlayerParty(),request,0);
}

void setCurrentMonData2(u8 request, void *value){
    SetMonData(getCurrentPlayerParty(),request,value);
}

void setCurrentMonData(u8 request, u32 value){
    u32 valueAddr = value;
//	SetMonData(getCurrentPlayerParty(),request,&valueAddr);
    setCurrentMonData2(request,&valueAddr);
}

void RefreshCurrentMonData(){
	CalculateMonStats(getCurrentPlayerParty());
}

/**
 * 获取当前精灵数据
*/
struct Pokemon *getCurrentPlayerParty(){
	return &gPlayerParty[myTempData->party];
}

/**
 * 获取种族值数据
*/
struct BaseStats* getSpeciesBaseStats(u16 species){
	u32 gBaseStats = gSpeciesInfoPtr[0];
	gBaseStats += (gDataSizeConfig.speciesDataSize*species);
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
u8 *getBattleTextBuff(u8 type,u16 value,u8 bitSize){
    struct TextBuffer *textBuffer = &myTempData->textBuffer;
	CpuFastFill(-1,textBuffer->temp,16);
	u8 data[] = {0xFD,type,value & 0xFF,bitSize != 2 ? 0xFF : (value >> 8),0xFF};
	ExpandBattleTextBuffPlaceholders(data,textBuffer->temp);
	return textBuffer->temp;
}

/**
 * 获取技能名称地址
 * @param atackNum 技能编号
 * @return 技能名称地址，如果不存在则返回0
*/
u8 *getAttackName(u16 attackNum){
	u32 moveNames = gMoveNamesPtr[0];
	moveNames += (attackNum*gNameLengthConfig.moveNameLength);
	return (u8 *) moveNames;
}

/**
 * 获取道具数据
 * @param itemId 道具编号
 */
struct Item *getItemData(u16 itemId){
    struct Item *itemTable = (struct Item *)(gItemsPtr[0]);
    struct Item *item = itemTable + itemId;
    return item;
}

/**
 * 获取道具名字
 * @param itemId 道具编号
 */
u8 *getItemName(u16 itemId){
	struct Item *item = getItemData(itemId);
	return item->name;
}

/**
 * 检查名字字符串是否有效
*/
bool8 checkNameString(const u8 *str,u32 length){
	u8 firstChar = str[0];
    //如果第一个字符是空格、终止符、-，则名字无效
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

/**
 * 校验的种族名字
 * @param species 种族编号
 */
bool8 validMonSpeciesNameValid(u16 species){
	u32 count = gQuantityLimit.pokemonCount;
	if (count != 0){
		if(species <= count){
            return TRUE;
        } else{
            return FALSE;
        }
	}

    if (species < 411)
        return TRUE;

	if (checkNameString(getMonSpeciesName(species),gNameLengthConfig.pokemonNameLength)){
		return TRUE;
	}
	return FALSE;
}

/**
 * 校验的技能名字
 * @param attackNum 技能编号
 */
bool8 validAttackName(u16 attackNum){
	u32 count = gQuantityLimit.moveCount;
	if (count != 0){
		if(attackNum <= count){
            return TRUE;
        } else{
            return FALSE;
        }
	}

    if (attackNum < 0x162)
        return TRUE;

	if (checkNameString(getAttackName(attackNum),gNameLengthConfig.moveNameLength)){
		return TRUE;
	}
	return FALSE;
}

/**
 * 获取校验的道具名字地址
 * @param itemId 道具编号
 */
u8 *getItemNameValid(u16 itemId){
	u32 count = gQuantityLimit.itemCount;

    struct Item *item = getItemData(itemId);
    u8 *name = item->name;

    u8 firstChar = name[0];
    //如果开头第一个字符是？?-，那么就是临时道具，需要跳过
    if(firstChar == 0x3D || firstChar == 0xAC || firstChar == 0xAE){
        return (u8 *) ITEM_NAME_TEMP;
    }

	if (count != 0){
        if(itemId <= count) {
            if (firstChar == 0 || firstChar == 0xFF)
                return (u8 *) ITEM_NAME_TEMP;

            return name;
        } else{
            return (u8 *) ITEM_NAME_NONE;
        }
	}

	u8 nameLen = gNameLengthConfig.itemNameLength;

	if(name[nameLen] == itemId){
		return name;
	}

	if(checkNameString(name,nameLen)){
		return name;
	}

    if (itemId < 0x317)
        return (u8 *) ITEM_NAME_TEMP;

	return (u8 *) ITEM_NAME_NONE;
}




