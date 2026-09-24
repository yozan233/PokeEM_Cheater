#include "header/data.h"

extern void task_loader(u8);
extern u32 GetMonData(struct Pokemon* poke_address, u8 request);
extern void SetMonPidTid(struct Pokemon *mon,u32 pid,u32 tid);
extern u8 CreateMyMonIcon(u16 species);
void initMonTempData();
void loadMonName();
void loadMonIconSprite();
void loadAbilityNums();
void loadMonIsShiny();
void loadMonGender(u16 species);
u32 getCurrentMonData(u8 request);
struct Pokemon *getCurrentPlayerParty();
struct BaseStats* getSpeciesBaseStats(u16 species);
struct Sprite *getSprite(u8 id);
u8 *getMonSpeciesName(u16 species);
u8 *getItemName(u16 itemId);
void backupMonTempData();

void main_func()
{
	*malloc_pointer_loc = (u8 *) AllocZeroed(0x1004);
    ResetAllSpriteData();
	mySav->task_id = CreateTask(task_loader,1);
	SetMainCallback2(MainCB2);
}


/**
 * 获取精灵最大等级
*/
u8 getMonMaxLevel(){
    void* fun = ItemUseCB_RareCandy;
	#ifdef FIRE_RED_LEAF_GREEN
	fun += 0x25;
	#elif RUBY_SAPPHIRE
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
	myTempData->happiness = getCurrentMonData(ATTR_HAPPINESS);

	myTempData->nature = umodsi3(myTempData->PID,25);
	u16 species = getCurrentMonData(ATTR_SPECIES);
	myTempData->species = species;
	loadMonGender(species);
	loadMonIsShiny();
	loadMonIconSprite();
    loadAbilityNums();

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
 * 获取性格名称
 */
void getNatureName(u8 nature,u8 *dest){
	u32* gNatureNamePointers = *gNatureNamePointersPtr;
	u32* namePtr = (u32*)(gNatureNamePointers + nature);
	u8* name = (u8*)namePtr[0];
	//ch<0x20 && ch!=0 && ch != 0x6 && ch != 0x1B //中文
	bool8 chinesFlag = FALSE;
	while (*name != 0xFF){
		u8 ch = *name;
		if(!chinesFlag && (ch == 0x5C || ch == 0x85))
			break;
		if(chinesFlag)
			chinesFlag = FALSE;
		else 
			chinesFlag = ch<0x20 && ch!=0 && ch != 0x6 && ch != 0x1B;
		*dest = ch;
		dest++;
		name++;
	}
	*dest = 0xFF;
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
	
	// loadMonIconTiles(species);
	// struct Sprite* sprites = getSprite(mySav->monIconId);
    // u32 monIconPaletteIndices = gMonIconPaletteIndicesPtr[0];
    // u32 monIconPaletteIndex = ((u8*)(myTempData->species+monIconPaletteIndices))[0];
	// sprites->oam.paletteNum = monIconPaletteIndex;

	destroyMonIconSprite();
	mySav->monIconId = CreateMyMonIcon(species);
}

void loadAbilityNums(){
    ((u32*)&myTempData->abilityNums)[0] = 0;
    myTempData->abilityNumPos = 0;
    int ability = 0;
	struct Pokemon *curMon = getCurrentPlayerParty();

	#ifdef FIRE_RED_LEAF_GREEN
	struct Pokemon *tempMon = NULL;
    #endif

	u8 size = 0;
    for (int num = 0;num<3;num++){
		myTempData->abilityNums.nums[num] = 0;

		#ifdef FIRE_RED_LEAF_GREEN
		if(gQuantityLimit.abilityHook == TRUE){
			if(tempMon == NULL){
				tempMon = Alloc(MON_DATA_SIZE);
				memcpy(tempMon, curMon, MON_DATA_SIZE);
			}
			SetMonPidTid(tempMon,num,myTempData->TID);
			((struct Pokemon2*)tempMon)->hiddenAbility = num == 2;
			int abilityIdTemp = GetMonAbility(tempMon);
			if(abilityIdTemp == 0)
				continue;
			if (abilityIdTemp != ability){
				ability = abilityIdTemp;
				if(abilityIdTemp == GetMonAbility(curMon)){
					myTempData->abilityNumPos = num;
				}
				myTempData->abilityNums.nums[num] = abilityIdTemp;
				size++;
			}
		}
		else
		#endif
		{
			int abilityTemp = GetAbilityBySpecies(myTempData->species,num);
			if(abilityTemp == 0)
				continue;
			if (abilityTemp != ability){
				ability = abilityTemp;
				if(GetMonData(curMon,ATTR_ABILITY_BIT) == num){
					myTempData->abilityNumPos = num;
				}
				myTempData->abilityNums.nums[num] = abilityTemp;
				size++;
			}
		}

    }

	myTempData->abilityNums.size_1 = size;

	#ifdef FIRE_RED_LEAF_GREEN
	if(tempMon != NULL){
		Free(tempMon);
	}
	#endif

}

struct Sprite *getSprite(u8 id){
	return &gSprites[id];
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

/**
 * 加载精灵性别
 * @param species 种族编号
 */
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
	return GetMonData(getCurrentPlayerParty(),request);
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
u8 *getBattleTextBuff(u8 type,u8 value){
    struct TextBuffer *textBuffer = &myTempData->textBuffer;
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
            else
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

	return (u8 *) ITEM_NAME_NONE;
}




