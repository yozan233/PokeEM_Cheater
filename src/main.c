#include "header/funcs.h"

extern void obj_callback();
extern void task_loader(u8);
extern u32 GetMonData(struct Pokemon* poke_address, u8 request);
void cb_execute(void);
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

void main_func()
{
	*malloc_pointer_loc = (u8 *) AllocZeroed(0x1004);
	ResetSpriteData();
	ResetPaletteFade();
	FreeAllSpritePalettes();
	mySav->task_id = CreateTask(task_loader,1);
	SetMainCallback2(cb_execute);
	return;
}

void cb_execute()
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
	u32 monIconOffset = gMonIconTable[species];//GetMonIconTiles(myTempData->species,FALSE);
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
