#include "header/funcs.h"

extern void obj_callback();
extern void task_loader(u8);
void cb_execute(void);
void initMonTempData();
void loadMonName();
void loadMonIconSprite();
void loadMonIconTiles();
void loadEggIconTiles();
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
	CreateTask(task_loader,1);
	SetMainCallback2(cb_execute);
	return;
}

void cb_execute()
{
	RunTasks();
	AnimateSprites();
	BuildOamBuffer();
	UpdatePaletteFade();
	obj_callback();
	return;
}

void initMonTempData(){
	myTempData->maxLvl = ((u8*)maxLvlOffset)[0];
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

void backupMonTempData(){
	CpuSet(&myTempData->party,&myTempData->party_2,6);
}

void refreshMonTempData(){
	CpuSet(&myTempData->party_2,&myTempData->party,6);
}

void loadMonName(){
    struct Pokemon *party =	getCurrentPartyplayer();
	StringCopy(BUFFER_2,party->nickname);
	u8* nameStr = (u8*)BUFFER_2;
	nameStr[10] = 0xFF;
	u8 len = 0;
	while(nameStr[len] != 0xFF){
		len++;
	}
	nameStr[len] = 0xBA;
	StringCopy(nameStr+len+1,getMonSpeciesName(myTempData->species));
}

u32 getMonSpeciesName(u16 species){
	u32 speciesNames = ((u32*)gSpeciesNames_Pointer)[0];
	return speciesNames + 0xB*species;
}

void loadMonIconSprite(){
	struct MySaveblock* saveblock = (struct MySaveblock*)VAR_8004;
	struct Sprite* sprites = getSprite(saveblock->monIconId);
	u8 monIconPaletteIndex;
	if(myTempData->egg){
		monIconPaletteIndex = 2;
		loadEggIconTiles();
	}
	else{
		u32 monIconPaletteIndices = ((u32*)gMonIconPaletteIndices_Pointer)[0];
		monIconPaletteIndex = ((u8*)(myTempData->species+monIconPaletteIndices))[0];
		monIconPaletteIndex += 1;
		loadMonIconTiles();
	}
	sprites->oam.paletteNum = monIconPaletteIndex;
}

struct Sprite *getSprite(u8 id){
	return (struct Sprite*)(gSprites+0x44*id);
}

void loadMonIconTiles(){
	u32 monIconTable = ((u32*)gMonIconTable_Pointer)[0];
	u32 monIconOffset = ((u32*)(monIconTable+myTempData->species*4))[0];

	CpuSet(monIconOffset,0x06010400,0x200);
}

void loadEggIconTiles(){
	CpuSet(gMonIcon_Egg,0x06010400,0x200);
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
			u8 flag = ((u8*)&myTempData->PID)[0];
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

struct Pokemon *getCurrentPartyplayer(){
	return gPlayerParty+myTempData->party*0x64;
}

struct BaseStats* getSpeciesBaseStats(u16 species){
	u32 gBaseStats = ((u32*)gBaseStats_Pointer)[0];
	gBaseStats += (0x1C*species);
	return (struct BaseStats*)gBaseStats;
}
