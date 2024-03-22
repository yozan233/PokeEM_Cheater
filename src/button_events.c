#include "header/funcs.h"

extern struct Pokemon *getCurrentPlayerParty();
extern void PlaySound(u16 soundID);
extern void UpdateKeyboardMousePos();
extern void initMonTempData();
extern void KeyboardPreviousFlag();
extern void get_ball_addr();
extern void InitCurrentPage();
extern u32 getMonSpeciesName(u16 species);
extern void SetShowNickNameOnly(bool8 b);
extern void ClearNewNameBuffer();
extern u16 GetItemListBuffer(u8 index);
extern void getSelectAttackNum();
extern void UpdatePageValue(u8 page);
extern u32 getCurrentMonData(u8 request);
extern void backupMonTempData();
extern void InitPage(u8 page);
extern void setCurrentMonData(u8 request, void* value);
extern void ChangePid(u8 nature,u8 gender,u8 shininess);
extern void RefreshCurrentMonData();
extern void ShowMonName();
extern u8 *getPlayerNameOffset();
extern void SetMonPidTid(struct Pokemon *mon,u32 pid,u32 tid);
extern void loadMonName();
extern void KeyboardButtonAEvent();
extern void KeyboardPreviousPage();
extern void KeyboardNextPage();
extern void KeyboardNextFlag();
extern void PrintSmallText(u8 x, u8 y, u8 *str);
extern void DeleteWord();
extern u8 *getAttackNameValid(u16 atackNum);
extern u8 *getMonSpeciesNameValid(u16 species);
extern u32 GetMonData(struct Pokemon* poke_address, u8 request);
void loadRepelStepCount();
void EggHatchNow();
void pause();

const u8 ivevMap[] = {0,0,3,1,4,2,5};

#ifdef FIRE_RED_LEAF_GREEN
#define VAR_REPEL_STEP_COUNT 0x4020
#else
#define VAR_REPEL_STEP_COUNT 0x4021
#endif

/**
 * 设置光标位置
 * @param x x坐标
 * @param y y坐标
*/
void SetMousePos(u16 x,u16 y){
    if(x != 0)
        mouseXY->pos_x = x;
    if(y != 0)
        mouseXY->pos_y = y;
}

/**
 * 缓存光标位置
*/
void BufferPos(){
	myTempData->posBuffer[0] = mouseXY->pos_x;
	myTempData->posBuffer[1] = mouseXY->pos_y;
}

/**
 * 判断光标位置是否改变
*/
bool8 IsPosChange(){
	return myTempData->posBuffer[0] != mouseXY->pos_x || myTempData->posBuffer[1] != mouseXY->pos_y;
}


/**
 * 更新选择光标位置
*/
void UpDateSelectedMousePos()
{
    BufferPos();
	u8 mode = MOUSE_POS_INFO;
	switch(myTempData->page){
		case PAGE_MAIN:
			mode = MOUSE_POS_MAIN;
			break;
		case PAGE_MOVES:
			mode = MOUSE_POS_ATTACK;
			break;
		case PAGE_SPECIE:
			mode = MOUSE_POS_SPECIE;
			break;
		case PAGE_ITEMS:
			mode = MOUSE_POS_ITEM;
			break;
		case PAGE_OTHER:
			mode = MOUSE_POS_OTHER;
            break;
        case PAGE_POKE_NAME:
        case PAGE_PLAYER_NAME:
            if(myTempData->select != 7 && myTempData->select != 8){
                UpdateKeyboardMousePos();
                return;
            }
        default:
            break;
	}
	u8 *pos = (u8 *)mouse_pos_table[mode];
    pos += (myTempData->select*2);
	SetMousePos(pos[0],pos[1]);
    if(IsPosChange())
        PlaySound(SOUND_SELECT);
}

/**
 * 选择下一个队伍精灵
*/
void SelectNextPartyMon(){
	u8 partyMax = gPlayerPartyCount[0];
	if(myTempData->party<partyMax-1){
		myTempData->party++;
		u8 t = myTempData->sex;
		initMonTempData();
		if(myTempData->page == PAGE_POKE_INFO2)
			get_ball_addr();
		if (myTempData->page == PAGE_EVS)
			myTempData->sex = t;
		PlaySound(SOUND_SELECT);
		InitCurrentPage();
	}
}
/**
 * 选择上一个队伍精灵
*/
void SelectPreviousPartyMon(){
	if(myTempData->party){
		myTempData->party--;
		u8 t = myTempData->sex;
		initMonTempData();
		if(myTempData->page == PAGE_POKE_INFO2)
			get_ball_addr();
		if (myTempData->page == PAGE_EVS)
			myTempData->sex = t;
		PlaySound(SOUND_SELECT);
		InitCurrentPage();
	}
}

/**
 * 检查精灵名字和种族是否相同
*/
bool8 checkMonNameAndSpecies(){
	u8 nickLength = textBuffer->monName[0x1F];
	textBuffer->monName[nickLength] = 0xFF;
	bool8 res;
    u32 buffer = (u32) textBuffer;

	if(StringCompare((const u8 *) (buffer + nickLength + 1), (const u8 *) buffer) != 0){
		res = FALSE;
	}
	else
		res = TRUE;
	return res;
}

/**
 * 精灵重命名为种族名称
*/
bool8 MonRenameBySpecies(){
	u8 *speciesName = (u8 *) getMonSpeciesName(myTempData->attackBuffer);
	struct Pokemon* party = getCurrentPlayerParty();
	u8 *nickName = party->nickname;
	for (u32 n = 0; n < 0xB; n++){
		nickName[n] = speciesName[n];
	}
}
/**
 * 设置图鉴flag
*/
void SetPokedexFlag(u16 species){
	u16 index = SpeciesToNationalPokedexNum(species);
	GetSetPokedexFlag(index,2); //图鉴设置已发现的标识
	GetSetPokedexFlag(index,3); //图鉴设置已捕获的标识
}
#ifdef BPEE0
/**
 * 是否为绿宝石802
*/
bool8 check_802(){
	return gBaseStatsPtr[0] == 0x08F186E0;
}
/**
 * 是否为究极绿宝石
*/
bool8 check_Ultra_Emerald(){
	u32 ultraEmerald = ((u32*)0x080BB100)[0];
	return ultraEmerald == 0x09E0FF80;
}
#endif

/**
 * 刷新当前页面
*/
void RefreshCurrentPage(){
	switch (myTempData->page)
	{
	case PAGE_POKE_INFO:
		initMonTempData();
		break;
	case PAGE_POKE_INFO2:
		get_ball_addr();
		break;
	case PAGE_EVS:
		myTempData->limit510 = FALSE;
		break;
	case PAGE_POKE_NAME:
		SetShowNickNameOnly(TRUE);
		//break;
	case PAGE_PLAYER_NAME:
		myTempData->inputCursorIndex = 0;
		ClearNewNameBuffer();
		break;
	case PAGE_MOVES:
        getSelectAttackNum();
		break;
	case PAGE_SPECIE:
		myTempData->attackBuffer = myTempData->species;
		break;
	case PAGE_ITEMS:
		myTempData->Num = 1;
		myTempData->addItemEnable = TRUE;
		myTempData->throwKeyItemEnable = FALSE;
		break;
	case PAGE_OTHER:
		((u8 *)myTempData)[0x46] = 0;
		loadRepelStepCount();
		myTempData->select = SELECT_CANCEL;
		break;
	default:
		break;
	}
	if(myTempData->page/0x10 != PAGETYPE_POKEMON || !myTempData->egg){
		UpdatePageValue(myTempData->page);
	}
}

u16 GetPenWuMax(){
    void *fun = ItemUseOutOfBattle_Repel;
    #ifdef FIRE_RED_LEAF_GREEN
    fun += 0xC;
    #else
    fun += 0xE;
    #endif
	u8 penWuFlag = ((u8 *)(fun))[0];
	if(penWuFlag == 6){
		return 0xFF;
	}
	else{
		return 0xFFFF;
	}
}

void loadRepelStepCount(){
	u16 var = VarGet(VAR_REPEL_STEP_COUNT);
	if(GetPenWuMax() == 0xFF){
		var = (u8)var;
	}
	myTempData->species = var;
}

void changeMouseColor(){
	u16 color = OBJ_PaletteMem2[11];
	u16 red = 0x109F;
	if(color == red){
		OBJ_PaletteMem2[11] = 0x6546;
	}
	else{
		OBJ_PaletteMem2[11] = red;
	}
}

void mouse_wait(){
	changeMouseColor();
	pause();
	changeMouseColor();
}

void reLoadPid(){
	u32 pid = getCurrentMonData(ATTR_PID);
	myTempData->PID = pid;
	backupMonTempData();
}

void SetMonNikename(){
	CpuSet(&textBuffer->newName,&getCurrentPlayerParty()->nickname,5);
}

void SetCurrentMonLevel(u8 lvl){
	struct Pokemon* temp = Alloc(MON_DATA_SIZE);
    CreateMon(temp,myTempData->species, lvl, 0, 0, 0, 0, 0);
    u32 exp = GetMonData(temp,ATTR_EXP);
    setCurrentMonData(ATTR_EXP,&exp);
    Free(temp);
}

/**
 * 视野最大化
*/
void shiye(){
    #ifdef RUBY_SAPPHIRE
    gSaveBlock1.flashLevel = 0;
    #else
	 gSaveBlock1Ptr->flashLevel = 0;
    #endif
    #ifdef BPEE0
    u8 *pyramidFlag = (u8 *)(((u32*)&gSaveBlock2Ptr)[0]+0x0E68);
    if(pyramidFlag[0] != 0){
        pyramidFlag[0] = 0xC0;
    }
    #endif
}

/**
 * 设置病毒
*/
void set_bingdu(){
    myTempData->Num = 0xF;
    u8 partyMax = gPlayerPartyCount[0];
    for (u8 i=0;i<partyMax;i++){
		SetMonData(&gPlayerParty[i],ATTR_POKERUS,&myTempData->Num);
    }
}

bool8 DelLastKeyitem(){
	struct BagPocket *keyitemsPocket = &gBagPockets[KEYITEMS_POCKET];
	u16 n = 0;
	while (n < keyitemsPocket->capacity){
		if (keyitemsPocket->itemSlots[n].itemId == 0)
			break;
		n++;
	}
    return RemoveBagItem(keyitemsPocket->itemSlots[n-1].itemId,1);
}

void pause(){
	asm("push {lr}\nmov r0, #0\nmov r1, #0xFF\nlsl r1, #0xA\npause_t:\nadd r0, #0x1\ncmp r0, r1\nbne pause_t\npop {pc}\nBX_R3:\nbx r3");
}

void SetText_MsgBox(u8 *str)
{
	u8 boxid_t = mySav->boxId;
    #ifdef RUBY_SAPPHIRE
    Menu_BlankWindowRect(1, 0x11, 0x1C, 0x12);
    #else
	FillWindowPixelBuffer(boxid_t,0x11);
    #endif
    #ifdef FIRE_RED_LEAF_GREEN
	AddTextPrinterParameterized(boxid_t,1,str,0,0,0,0); //按键提示
    #elif RUBY_SAPPHIRE
    Menu_PrintTextPixelCoords(str,16,0x88,0);
    #else
	AddTextPrinterParameterized(boxid_t,1,str,6,0,0,0); //按键提示
    #endif
}

void UpdateCurrentPageText(){
	UpdatePageValue(myTempData->page);
}

void UpdateCurrentPageTextAndPlaySound(){
	UpdateCurrentPageText();
	PlaySound(SOUND_SELECT);
}

void InitCurrentPage(){
	InitPage(myTempData->page);
}

u32 getIvOrEvSum(){
    u32 sum = 0;
    u8 *ivev = (u8 *)(&myTempData->hp);
    for (int i = 0; i < 6; i++){
        sum += ivev[i];
    }
    return sum;    
}

void SetAbilitySelect(){
    #ifdef BPEE0
	if(check_Ultra_Emerald())
	{
		switch (myTempData->ability)
		{
		case 0:
			myTempData->ability = 1;
			break;
		case 1:
			myTempData->ability = 4;
			break;
		case 4:
			myTempData->ability = 0;
		default:
			break;
		}
	}
	else{
		myTempData->ability = !myTempData->ability;
	}
    #else
    myTempData->ability = !myTempData->ability;
	#endif
}

/**
 * 按下确认键
*/
void OnSureClick(){
    if(myTempData->page/0x10 == PAGETYPE_POKEMON && myTempData->egg){
        EggHatchNow();
        return;
    }

    switch (myTempData->page)
    {
    case PAGE_POKE_INFO:{
        if (myTempData->lvl != myTempData->lvl_2){
            SetCurrentMonLevel(myTempData->lvl);
        }
        struct Pokemon* party = getCurrentPlayerParty();
        party->padding = 0;
        myTempData->Num = myTempData->ability;
        setCurrentMonData(ATTR_ABILITY_BIT,&myTempData->Num);
        myTempData->Num = myTempData->happiness;
        setCurrentMonData(ATTR_HAPPINESS,&myTempData->Num);
        if(myTempData->nature != myTempData->nature_2
            || myTempData->shiny != myTempData->shiny_2
            || myTempData->sex != myTempData->sex_2
        ){
            ChangePid(myTempData->nature,myTempData->sex,myTempData->shiny);
        }
        
        RefreshCurrentMonData();
        backupMonTempData();
    }
    break;
    case PAGE_POKE_INFO2:{
        #ifndef RUBY_SAPPHIRE
        if(myTempData->obedience != myTempData->obedienceTemp){
            myTempData->obedienceTemp = myTempData->obedienceTemp;
            setCurrentMonData(ATTR_OBEDIENCE, &myTempData->obedience);
            u32 mTid = GetPlayerIDAsU32();
            u32 tidTemp = myTempData->TID;
            if (myTempData->obedience == 0xFF)
            {
                if (myTempData->TID == mTid){
                    tidTemp = myTempData->TID ^ 0xFF;
                }
            }
            else
            {
                if (myTempData->TID != mTid){
                    tidTemp = mTid;
                }
                setCurrentMonData(ATTR_OT_NAME, getPlayerNameOffset());
            }
            if (myTempData->TID != tidTemp){
                myTempData->TID = tidTemp;
                SetMonPidTid(getCurrentPlayerParty(),myTempData->PID,tidTemp);
            }
        }
        #endif

        #ifndef FIRE_RED_LEAF_GREEN
        u8 t = gLocalTime.hours;
        if (t != myTempData->time)
        {
            RtcInitLocalTimeOffset(myTempData->time, 0); //设置时间
        }
        #endif
        
        setCurrentMonData(ATTR_CATCH_LOCATION, &myTempData->location);

        if (myTempData->itemBuffer)
            setCurrentMonData(ATTR_POKEBALL, &myTempData->itemBuffer);

        RefreshCurrentMonData();

        if (myTempData->monCopy) //复制精灵
        {
            u32 r = GiveMonToPlayer(getCurrentPlayerParty());
            if (r != MON_CANT_GIVE)
            {
                PrintSmallText(26, 100, text_table[TEXT_COPY_SUCCESS]);
                if (r == 1)
                    PrintSmallText(66, 100, text_table[TEXT_SEND_TO_PC]);
            }
            else
            {
                PrintSmallText(26, 100, text_table[TEXT_COPY_FAILED]);
            }
        }
        
        if (myTempData->selectedflightPoint) //执行瞬移
        {
            #ifdef FIRE_RED_LEAF_GREEN
			gSaveBlock2Ptr->optionsButtonMode = myTempData->optionsButtonMode;
            #endif
            #ifdef RUBY_SAPPHIRE
            gSaveBlock2.optionsWindowFrameType = myTempData->optionsButtonMode;
            #endif
            BeginNormalPaletteFade(-1, 0, 0, 0x10, 0);
            HealPlayerParty();
            DestroyTask(mySav->task_id);
            #ifndef RUBY_SAPPHIRE
            FreeAllWindowBuffers();
            #endif
            Free(*malloc_pointer_loc);
            struct HealLocation *location = GetHealLocation(myTempData->selectedflightPoint);
            SetWarpDestination(location->group, location->map, -1, location->x, location->y);
            DoWarp();
            ResetInitialPlayerAvatarState();
        }
    }
    break;
    case PAGE_IVS:
    case PAGE_EVS:{
        u8 request;
        if (myTempData->page == PAGE_IVS)
            request = ATTR_HP_IV;
        else
            request = ATTR_HP_EV;
        
        u8 *ivev = (u8 *)&myTempData->hp;
        for (u8 i = 0; i < 6; i++,request++){
            setCurrentMonData(request,&ivev[i]);
        }
        RefreshCurrentMonData();
    }break;
    case PAGE_MOVES:
        setCurrentMonData(myTempData->attackSelect + 0xD, &myTempData->attackBuffer);
        UpdateCurrentPageText();
        break;
    case PAGE_SPECIE:{
        if(checkMonNameAndSpecies()){
            MonRenameBySpecies();
        }
        SetPokedexFlag(myTempData->attackBuffer);
        setCurrentMonData(ATTR_SPECIES, &myTempData->attackBuffer);
        myTempData->Num = 2;
        setCurrentMonData(ATTR_FONT_LANG, &myTempData->Num);
        RefreshCurrentMonData();
        initMonTempData();
        ShowMonName();
        UpdateCurrentPageText();
    }
    break;
    case PAGE_POKE_NAME:{
        if(textBuffer->newName[0] != 0xFF)
            SetMonNikename();
        else
            MonRenameBySpecies();
        myTempData->Num = 2;
        setCurrentMonData(ATTR_FONT_LANG, &myTempData->Num);
        loadMonName();
        RefreshCurrentPage();
    }
    break;
    case PAGE_PLAYER_NAME:{
        if(textBuffer->newName[0] != 0xFF)
            StringCopy(getPlayerNameOffset(),textBuffer->newName);
        RefreshCurrentPage();
    }
    break;
    case PAGE_ITEMS:{
        if (myTempData->Num && myTempData->addItemEnable){
            u8 *successText = text_table[TEXT_INSUFFICIENT_SPACE];
            if (AddBagItem(myTempData->itemBuffer, myTempData->Num))
                successText = text_table[TEXT_ADD_SUCCESS];
            PrintSmallText(120, 88, successText); //添加成功
        }
        else if (myTempData->throwKeyItemEnable){
            DelLastKeyitem();
        }
    }
    break;
    case PAGE_OTHER:{
        if (myTempData->pokedexUpgrade){
            EnableNationalPokedex();
        }
        #ifndef FIRE_RED_LEAF_GREEN
        if (myTempData->mirageShow){
            VarSet(0x4024, getCurrentMonData(ATTR_PID) & 0xFFFF);
        }
        else{
            VarSet(0x4024, Random());
        }
        #endif
        if (myTempData->pokerus){
            set_bingdu();
        }
        if (myTempData->visualRangeMax){
            shiye();
        }
        throughWallFlag[0] = myTempData->throughWall;
        VarSet(VAR_REPEL_STEP_COUNT, myTempData->species);
    }
    break;
    default:
        break;
    }
    mouse_wait();

}

//立即孵化
void EggHatchNow(){
    u16 spe = myTempData->species;
    if (spe == 0x19C)
        spe = umodsi3(Random(), 0xFB) + 1;
    u8 eggLvl = 5;
    CreateMon(getCurrentPlayerParty(), spe, eggLvl, 32, 1, Random() | (Random() << 0x10), 0, myTempData->TID);
    myTempData->Num = 0;
    SetMonData(getCurrentPlayerParty(), 0x24, &myTempData->Num);
    if(myTempData->page != PAGE_POKE_INFO)
        initMonTempData();
    InitCurrentPage();
}

void ButtonAEvent()
{
    if (super->buttons3_new_remapped != BUTTONS_A)
        return;
    if (myTempData->cursorState == TRUE) //如果光标处于选中状态
        return;
    PlaySound(SOUND_SELECT);
    if(myTempData->select == SELECT_CANCEL){
        RefreshCurrentPage();
        return;
    }
    else if (myTempData->select == SELECT_SURE)
    {
        OnSureClick();
        return;
    }
    

    switch (myTempData->page)
    {
    case PAGE_MAIN:
        switch (myTempData->select)
        {
        case 0: //精灵
            InitPage(PAGE_POKE_INFO);
            break;
        case 1: //背包
            InitPage(PAGE_ITEMS);
            break;
        case 2: //其它
            InitPage(PAGE_OTHER);
        default:
            break;
        }
        break;
    case PAGE_POKE_INFO:
    case PAGE_POKE_INFO2:
    case PAGE_IVS:
    case PAGE_EVS:
    case PAGE_MOVES:
    case PAGE_SPECIE:{
        changeMouseColor();
        myTempData->cursorState = 1;
        u8 *textButtonPrompt = text_table[TEXT_BUTTON_PROMPT4];
        if ((myTempData->page == PAGE_POKE_INFO && myTempData->select > 2) 
            || myTempData->select == 0 
            || (myTempData->page == PAGE_POKE_INFO2 && myTempData->select != 4)
            ){
                textButtonPrompt += 2;
        }

        SetText_MsgBox(textButtonPrompt);
    }
    break;
    case PAGE_POKE_NAME:
    case PAGE_PLAYER_NAME:
        KeyboardButtonAEvent();
        break;
    case PAGE_ITEMS:
    {
        switch (myTempData->select)
        {
        case 3:
            myTempData->addItemEnable = !myTempData->addItemEnable;
            UpdateCurrentPageText();
            break;
        case 4:
            myTempData->throwKeyItemEnable = !myTempData->throwKeyItemEnable;
            UpdateCurrentPageText();
            break;
        default:
            changeMouseColor();
            myTempData->cursorState = 1;
            SetText_MsgBox(text_table[TEXT_BUTTON_PROMPT4]);
            break;
        }
    }
    break;
    case PAGE_OTHER:
    {
        if (myTempData->select <= 6)
        {
            if (myTempData->select == 2)
            {
                changeMouseColor();
                myTempData->cursorState = 1;
                SetText_MsgBox(text_table[TEXT_BUTTON_PROMPT4]);
            }
            else
            {
                switch (myTempData->select)
                {
                case 1:
                    myTempData->pokedexUpgrade = !myTempData->pokedexUpgrade;
                    break;
                case 3:
                    myTempData->pokerus = !myTempData->pokerus;
                    break;
                case 4:
                    myTempData->visualRangeMax = !myTempData->visualRangeMax;
                    break;
                case 5:
                    myTempData->mirageShow = !myTempData->mirageShow;
                    break;
                case 6:
                    myTempData->throughWall = !myTempData->throughWall;
                    break;
                }
                UpdateCurrentPageText();
            }
        }
    }
    break;
    }
}

bool8 ButtonBEvent(){
    if (super->buttons3_new_remapped != BUTTONS_B)
        return FALSE;
    if (myTempData->cursorState == FALSE){
        if(myTempData->page == PAGE_MAIN){
            #ifdef FIRE_RED_LEAF_GREEN
			gSaveBlock2Ptr->optionsButtonMode = myTempData->optionsButtonMode;
            #endif
            #ifdef RUBY_SAPPHIRE
            gSaveBlock2.optionsWindowFrameType = myTempData->optionsButtonMode;
            #endif
            BeginNormalPaletteFade(-1, 0, 0, 0x10, 0);
            HealPlayerParty();
            PlaySound(36);
            return TRUE;
        }
        
        if(myTempData->pageLock){
            if(myTempData->page == PAGE_POKE_NAME || myTempData->page == PAGE_PLAYER_NAME){
                DeleteWord();
                myTempData->soundMute = TRUE;
            }
        }
        else{
            u32 pageTpye = myTempData->page/0x10;
            myTempData->select = pageTpye-1;
            InitPage(PAGE_MAIN);
        }
        
    }
    else{
        myTempData->cursorState = FALSE;
        changeMouseColor();
        if(myTempData->page == PAGE_ITEMS){
            SetText_MsgBox(text_table[TEXT_BUTTON_PROMPT2]);
        }
        else{
            SetText_MsgBox(text_table[TEXT_BUTTON_PROMPT3]);
        }
    }
    PlaySound(SOUND_SELECT);
    return FALSE;
}

void ButtonLeftEvent()
{
    if (myTempData->cursorState == FALSE)
    {
        if(myTempData->page/0x10 == PAGETYPE_POKEMON && myTempData->egg && myTempData->select == 8){
            myTempData->select = 0;
            UpDateSelectedMousePos();
            return;
        }
        switch(myTempData->page){
            case PAGE_MAIN:
                if (myTempData->select > 0)
                    myTempData->select--;
                else
                    myTempData->select = 2;
                break;
            case PAGE_MOVES:
            case PAGE_SPECIE:
                if(myTempData->select == SELECT_SURE){
                    if(myTempData->page == PAGE_SPECIE)
                        myTempData->select = 4;
                    else{
                        myTempData->select = myTempData->attackSelect+1;
                    }
                }  
                else if (myTempData->select == SELECT_CANCEL)
                    myTempData->select = SELECT_SURE;
                break;
            case PAGE_POKE_NAME:
            case PAGE_PLAYER_NAME:
                if(myTempData->select <= 8){
                    if(myTempData->select == 7){
                        myTempData->select = 8;
                    }
                    else{
                        myTempData->select = 0xFF;
                    }
                }
                else if(umodsi3((myTempData->select),10) != 5){
                    myTempData->select += 1;
                }
                break;
            case PAGE_ITEMS:
                if(myTempData->select == 7)
                    myTempData->select = 8;
                else 
                    myTempData->select = 1;
                break;
            default:
                if(myTempData->select == 8)
                    myTempData->select = 5;
                else if (myTempData->select == 7)
                    myTempData->select = 8;
                else if(myTempData->select && umodsi3(myTempData->select,2) == 0)
                    myTempData->select--;
                break;
        }

        UpDateSelectedMousePos();
    }
    else{
        switch (myTempData->page)
        {
        case PAGE_POKE_INFO:
            switch(myTempData->select){
			case 1:
				if(myTempData->lvl > 10){
					myTempData->lvl -= 10;
                    UpdateCurrentPageTextAndPlaySound();
                }
				else if(myTempData->lvl > 1){
					myTempData->lvl = 1;
                    UpdateCurrentPageTextAndPlaySound();
                }
				break;
			case 2:
				if(myTempData->happiness > 10){
                    myTempData->happiness -= 10;
                    UpdateCurrentPageTextAndPlaySound();
                }
				else if(myTempData->happiness){
					myTempData->happiness = 0;
                    UpdateCurrentPageTextAndPlaySound();
                }
				break;
		}
        break;
        case PAGE_POKE_INFO2:
            #ifndef FIRE_RED_LEAF_GREEN
            if(myTempData->select == 4){
                if(myTempData->time > 3){
                    myTempData->time -= 3;
                }
                else{
                    myTempData->time = 24+myTempData->time-3;
                }
                UpdateCurrentPageTextAndPlaySound();
            }
            #endif
            break;
        case PAGE_IVS:
        case PAGE_EVS:{
            u8 *ivev = (u8 *)(&myTempData->hp);
            ivev += ivevMap[myTempData->select];
            u8 temp = ivev[0];
            if(temp > 10){
                ivev[0] -= 10;
                UpdateCurrentPageTextAndPlaySound();
            }
            else if(ivev[0]){
                ivev[0] = 0;
                UpdateCurrentPageTextAndPlaySound();
            }
        }
        break;
        case PAGE_MOVES:
        case PAGE_SPECIE:{
            u8 rt = 1;
            while (rt<=4)
            {
                if(myTempData->attackBuffer-rt < 1)
                    break;
                else
                    rt++;
                
            }
            if(rt != 1){
                myTempData->attackBuffer-=(rt-1);
                UpdateCurrentPageTextAndPlaySound();
            }
        }break;
        case PAGE_ITEMS:{
            if(myTempData->select == 2){
                u16 numt = myTempData->Num;
                if(numt<10)
                    myTempData->Num = 0;
                else
                    myTempData->Num -= 10;
                if(numt)
                    UpdateCurrentPageTextAndPlaySound();
            }
            else{
                u16 t = GetItemListBuffer(ITEM_TEXT_CURSOR_INDEX);
                if(t){
                    myTempData->itemBuffer = GetItemListBuffer(0);
                    UpdateCurrentPageTextAndPlaySound();
                }
            }
        }
        break;
        case PAGE_OTHER:{
            u16 buShu = myTempData->species;
            u16 diff;
            if(GetPenWuMax() == 255)
                diff = 10;
            else
                diff = 100;
			if(buShu > diff)
				myTempData->species -= diff;
			else
				myTempData->species = 0;
			if(buShu)
				UpdateCurrentPageTextAndPlaySound();
        }
        break;
        default:
            break;
        }
    }
}

void ButtonRightEvent()
{
    if (myTempData->cursorState == FALSE)
    {
        switch(myTempData->page){
            case PAGE_MAIN:
                if (myTempData->select < 2)
                    myTempData->select++;
                else
                    myTempData->select = 0;          
                break;
            case PAGE_MOVES:
            case PAGE_SPECIE:
                if(myTempData->select <= 4)
                    myTempData->select = 8;
                else if(myTempData->select == 8)
                    myTempData->select = 7;
                break;
            case PAGE_POKE_NAME:
            case PAGE_PLAYER_NAME:
                if(myTempData->select <= 8){
                    if(myTempData->select == 8)
                        myTempData->select = 7;
                }
                else{
                    if(umodsi3((myTempData->select),10) != 6){
                        myTempData->select -= 1;
                    }
                    else{
                        if(myTempData->select>=0xEC)
                            myTempData->select = 1;
                        else if (myTempData->select == 0xE2)
                            myTempData->select = 2;
                        else
                            myTempData->select = 8;
                    }
                }
                break;
            case PAGE_ITEMS:
                if(myTempData->select == 1)
                    myTempData->select = 2;
                else if (myTempData->select == 8)
                    myTempData->select = 7;
                break;
            default:
                if(myTempData->select == 0){
                    if(myTempData->egg)
                        myTempData->select = 8;
                    else
                    myTempData->select = 2;
                }
                else if (myTempData->select == 8)
                    myTempData->select = 7;
                else if(umodsi3(myTempData->select,2) != 0 && myTempData->select != 7)
                    myTempData->select++;
                break;
        }
    
        UpDateSelectedMousePos();
    }
    else{
        switch (myTempData->page)
        {
        case PAGE_POKE_INFO:
            switch(myTempData->select){
			case 1:{
                u8 maxLvl = myTempData->maxLvl;
                if(myTempData->lvl < maxLvl-10){
                    myTempData->lvl += 10;
                    UpdateCurrentPageTextAndPlaySound();
                }
                else if(myTempData->lvl != maxLvl){
                    myTempData->lvl = maxLvl;
                    UpdateCurrentPageTextAndPlaySound();
                }
            }break;
			case 2:
				if(myTempData->happiness < 255-10){
					myTempData->happiness += 10;
                    UpdateCurrentPageTextAndPlaySound();
				}
				else if(myTempData->happiness != 255){
					myTempData->happiness = 255;
                    UpdateCurrentPageTextAndPlaySound();
				}
		    }
            break;
        case PAGE_POKE_INFO2:
            #ifndef FIRE_RED_LEAF_GREEN
            if(myTempData->select == 4){
                if(myTempData->time < 21){
                    myTempData->time += 3;
                }
                else{
                    myTempData->time = myTempData->time - 21;
                }
                UpdateCurrentPageTextAndPlaySound();
            }
            #endif
            break;
        case PAGE_IVS:
        case PAGE_EVS:{
            u8 *ivev = (u8 *)(&myTempData->hp);
            ivev += ivevMap[myTempData->select];
            u8 temp = ivev[0];
			u8 max;
			if(myTempData->page == PAGE_IVS)
				max = 31;
			else{
				if (myTempData->limit510){
					u32 sum = getIvOrEvSum();
					if (sum >= 510){
                        break;
                    }
					else
					{
                        u8 ff = 255;
						u32 dValue = 510 - sum;
                        if(dValue + temp >= ff){
                            max = ff;
                        }
                        else{
                            max = dValue + temp;
                        }
						
					}
				}
				else{
					max = 255;
				}
			}

            if(temp < max-10){
				ivev[0] += 10;
                UpdateCurrentPageTextAndPlaySound();
            }else if(ivev[0] != max){
				ivev[0] = max;
                UpdateCurrentPageTextAndPlaySound();
            }

        }
        break;
        case PAGE_MOVES:{
            u8 rt = 1;
            while (rt <= 4){
                if(!getAttackNameValid(myTempData->attackBuffer+rt))
                    break;
                else
                    rt++;
            }
            if(rt != 1){
                myTempData->attackBuffer+=(rt-1);
                UpdateCurrentPageTextAndPlaySound();
            }
        }
        break;
        case PAGE_SPECIE:
            if(myTempData->select == 4){
                u16 pmax = MON_COUNT;
                #ifdef BPEE0
                if(check_802())
                    pmax-=2;
                #endif
                if(myTempData->attackBuffer < pmax-4){
                    myTempData->attackBuffer += 4;
                    UpdateCurrentPageTextAndPlaySound();
                }
                else if(myTempData->attackBuffer != pmax){
                    myTempData->attackBuffer = pmax;
                    UpdateCurrentPageTextAndPlaySound();
                }
            }
            break;
        case PAGE_ITEMS:{
            if(myTempData->select == 2){
                u16 numTemp = myTempData->Num;
                u16 max = 99;
                if(numTemp > max-10)
                    myTempData->Num = max;
                else
                    myTempData->Num += 10;
                if(numTemp < max)
                    UpdateCurrentPageTextAndPlaySound();
            }
            else{
                u16 t = GetItemListBuffer(ITEM_TEXT_CURSOR_INDEX);
                if(t < 6){
                    myTempData->itemBuffer = GetItemListBuffer(6);
                    UpdateCurrentPageTextAndPlaySound();
                }
            }
        }break;
        case PAGE_OTHER:{
            u16 buShu = myTempData->species;
			u16 max = GetPenWuMax();
            u16 diff;
            if(max == 255)
                diff = 10;
            else
                diff = 100;
			if(buShu < max-diff)
				myTempData->species += diff;
			else
				myTempData->species = max;
			if(buShu != max)
				UpdateCurrentPageTextAndPlaySound();
        }
        break;
        default:
            break;
        }
    }
}

void ButtonShoulderL(){
    if (super->buttons3_new_remapped != BUTTONS_L || myTempData->cursorState || (myTempData->page & 0xf) == 0)
        return;
    if ((myTempData->page == PAGE_POKE_NAME || myTempData->page == PAGE_PLAYER_NAME) && myTempData->pageLock)
    {
        PlaySound(SOUND_SELECT);
        KeyboardPreviousPage();
    }
    else{
        myTempData->page --;
        PlaySound(SOUND_PAGE);
        InitCurrentPage();
    }
}

void ButtonShoulderR(){
    if (super->buttons3_new_remapped != BUTTONS_R || myTempData->cursorState || myTempData->page == PAGE_MAIN || myTempData->page == PAGE_ITEMS)
        return;
    if (myTempData->page == PAGE_POKE_NAME || myTempData->page == PAGE_PLAYER_NAME)
    {
        if(myTempData->pageLock){
            PlaySound(SOUND_SELECT);
            KeyboardNextPage();
        }
            
    }
    else {
        if(myTempData->page/0x10 == PAGETYPE_POKEMON && myTempData->egg)
            return;
        myTempData->page ++;
        PlaySound(SOUND_PAGE);
        InitCurrentPage();
    }
    
}

void ButtonUpEvent(){
    if(myTempData->page == PAGE_MAIN)
        return;
    if(myTempData->cursorState == FALSE){
        if(myTempData->select){
            if(myTempData->page == PAGE_OTHER && myTempData->select <= 2)
                return;
            if(myTempData->page/0x10 == PAGETYPE_POKEMON && myTempData->egg){
                myTempData->select = 0;
                UpDateSelectedMousePos();
                return;
            }
            switch(myTempData->page){
                case PAGE_MOVES:
                    if(myTempData->select > 1 && myTempData->select <= 4){
                        myTempData->attackSelect--;
                        myTempData->select --;
                        getSelectAttackNum();
                        UpdateCurrentPageText();
                    }
                    else if(myTempData->select == 1){
                        myTempData->select = 0;
                    }
                    else{
                        myTempData->select = myTempData->attackSelect+1;
                    }
                    break;
                case PAGE_SPECIE:
                    if(myTempData->select == 7 || myTempData->select == 8)
                        myTempData->select = 4;
                    else
                        myTempData->select = 0;
                    break;
                case PAGE_POKE_NAME:
                case PAGE_PLAYER_NAME:
                    if(myTempData->select == 7||myTempData->select == 8)
                        myTempData->select = 2;
                    else if(myTempData->select == 2){
                        myTempData->select = 1;
                    }
                    else if(myTempData->select > 8 && myTempData->select < 0xF6){
                            myTempData->select += 10;
                        }
                    break;
                case PAGE_ITEMS:
                    if(myTempData->select == 7 || myTempData->select == 8)
                        myTempData->select = 4;
                    else if(myTempData->select > 1)
                        myTempData->select --;
                    break;
                default:
                    if(myTempData->select == 7 || myTempData->select == 1)
                        myTempData->select --;
                    else
                        myTempData->select -= 2;
                    break;
            }
            
            UpDateSelectedMousePos();
        }
        

    }
    else
    {
        if(myTempData->select == 0 && myTempData->page > PAGE_MAIN && myTempData->page < PAGE_POKE_NAME){
            SelectPreviousPartyMon();
            return;
        }
        switch (myTempData->page)
        {
        case PAGE_POKE_INFO:
            switch(myTempData->select){
                case 1:
                    if(myTempData->lvl < myTempData->maxLvl){
                        myTempData->lvl++;
                        UpdateCurrentPageTextAndPlaySound();
                    }
                    break;
                case 2:
                    if(myTempData->happiness < 255){
                        myTempData->happiness++;
                        UpdateCurrentPageTextAndPlaySound();
                    }
                    break;
                case 3:
                    if(myTempData->nature<0x18){
                        myTempData->nature++;
                        UpdateCurrentPageTextAndPlaySound();
                    }
                    break;
                case 4:
                    myTempData->shiny = !myTempData->shiny;
                    UpdateCurrentPageTextAndPlaySound();
                    break;
                case 5:
                    SetAbilitySelect();
                    UpdateCurrentPageTextAndPlaySound();
                    break;
                case 6:
                    if(myTempData->sex < 2){
                        myTempData->sex = !myTempData->sex;
                        UpdateCurrentPageTextAndPlaySound();
                    }
                    break;
		}
        break;
        case PAGE_POKE_INFO2:
            switch (myTempData->select)
            {
            case 1:
                if(myTempData->selectedBall){
                    myTempData->selectedBall --;
                    UpdateCurrentPageTextAndPlaySound();
                }
                break;
            case 2:
                if(myTempData->location == 0xFF){
                    myTempData->location = 0xD4;
                    UpdateCurrentPageTextAndPlaySound();
                }
                else if(myTempData->location){
                    myTempData->location --;
                    UpdateCurrentPageTextAndPlaySound();
                }
                break;
            case 3:
                if(myTempData->selectedflightPoint){
                    myTempData->selectedflightPoint --;
                    UpdateCurrentPageTextAndPlaySound();
                }
                break;
            case 4:
                #ifndef FIRE_RED_LEAF_GREEN
                if(myTempData->time == 23){
                    myTempData->time = 0;
                    UpdateCurrentPageTextAndPlaySound();
                }
                else{
                    myTempData->time ++;
                    UpdateCurrentPageTextAndPlaySound();
                }
                #endif
                break;
            case 5:
                myTempData->monCopy = !myTempData->monCopy;
                UpdateCurrentPageTextAndPlaySound();
                break;
            case 6:
                #ifndef RUBY_SAPPHIRE
                myTempData->obedience = !myTempData->obedience;
                UpdateCurrentPageTextAndPlaySound();
                #endif
                break;
            default:
                break;
            }
            break;
        case PAGE_IVS:
        case PAGE_EVS:{
            u8 *ivev = (u8 *)(&myTempData->hp);
            ivev += ivevMap[myTempData->select];
            u8 temp = ivev[0];
			u8 max;
			if(myTempData->page == PAGE_IVS) {
                max = 31;
            }else{
				if (myTempData->limit510){
					u32 sum = getIvOrEvSum();
					if (sum >= 510){
                        break;
                    }
					else
					{
                        u8 ff = 255;
						u32 dValue = 510 - sum;
                        if(dValue + temp >= ff){
                            max = ff;
                        }
                        else{
                            max = dValue + temp;
                        }
						
					}
				}
				else{
					max = 255;
				}
			}

            if (temp < max - 1) {
                ivev[0]++;
                UpdateCurrentPageTextAndPlaySound();
            } else if (max) {
                ivev[0] = max;
                UpdateCurrentPageTextAndPlaySound();
            }

        }
        break;
        case PAGE_MOVES:
        case PAGE_SPECIE:
            if(myTempData->attackBuffer > 1){
				myTempData->attackBuffer --;
				UpdateCurrentPageTextAndPlaySound();
			}
            break;
        case PAGE_ITEMS:{
            if(myTempData->select == 1){
				u16 t = GetItemListBuffer(ITEM_TEXT_CURSOR_INDEX);
				if(t){
					myTempData->itemBuffer = GetItemListBuffer(t-1);
					UpdateCurrentPageTextAndPlaySound();
				}
			}else if(myTempData->Num < 99){
				myTempData->Num++;
				UpdateCurrentPageTextAndPlaySound();
			}
        }
        break;
        case PAGE_OTHER:{
            u16 max = GetPenWuMax();
			if(myTempData->species < max){
				myTempData->species++;
				UpdateCurrentPageTextAndPlaySound();
			}
        }
        break;
        case PAGE_POKE_NAME:
        case PAGE_PLAYER_NAME:
            PlaySound(SOUND_SELECT);
            KeyboardNextFlag();
            break;
        default:
            break;
        }
    }
    
}

void ButtonDownEvent(){
    if(myTempData->page == PAGE_MAIN)
        return;
    if(myTempData->cursorState == FALSE){
        if(myTempData->page == PAGE_POKE_NAME || myTempData->page == PAGE_PLAYER_NAME){
            if(myTempData->select == 1){
                myTempData->select = 2;
            }
            else if (myTempData->select == 2){
                myTempData->select = 7;
            }
            else if(myTempData->select > 0xD7){
                myTempData->select -= 10;
            }
        }
        else if(myTempData->select < 7){
            switch(myTempData->page){
                case PAGE_MOVES:
                    if(myTempData->select && myTempData->select < 4){
                        myTempData->attackSelect++;
                        getSelectAttackNum();
                        UpdateCurrentPageText();
                    }
                    if(myTempData->select != 4)
                        myTempData->select ++;
                    else
                        myTempData->select = 8;
                    break;
                case PAGE_SPECIE:
                    if(myTempData->select == 0)
                        myTempData->select = 4;
                    else if(myTempData->select == 4)
                        myTempData->select = 8;
                    break;
                case PAGE_ITEMS:
                    if(myTempData->select == 1 || myTempData->select == 4)
                        myTempData->select = 8;
                    else if(myTempData->select <= 4)
                        myTempData->select ++;
                    break;
                default:
                    if(myTempData->select == 0){
                        if(myTempData->egg)
                            myTempData->select = 8;
                        else
                            myTempData->select ++;
                    }
                        
                    else if(myTempData->select == 5)
                        myTempData->select = 8;
                    else
                        myTempData->select += 2; 
                    break;
            }
            
        }
        UpDateSelectedMousePos();
    }
    else
    {
        if(myTempData->select == 0 && myTempData->page > PAGE_MAIN && myTempData->page < PAGE_POKE_NAME){
            SelectNextPartyMon();
            return;
        }
        switch(myTempData->page){
            case PAGE_POKE_INFO:{
                switch (myTempData->select)
                {
                case 1:
                    if(myTempData->lvl > 1){
                        myTempData->lvl--;
                        UpdateCurrentPageTextAndPlaySound();
                    }
                    break;
                case 2:
                    if(myTempData->happiness){
                        myTempData->happiness--;
                        UpdateCurrentPageTextAndPlaySound();
                    }
                    break;
                case 3:
                    if(myTempData->nature){
                        myTempData->nature--;
                        UpdateCurrentPageTextAndPlaySound();
                    }
                    break;
                case 4:
                    myTempData->shiny = !myTempData->shiny;
                    UpdateCurrentPageTextAndPlaySound();
                    break;
                case 5:
                    SetAbilitySelect();
                    UpdateCurrentPageTextAndPlaySound();
                    break;
                case 6:
                    if(myTempData->sex < 2){
					    myTempData->sex = !myTempData->sex;
                        UpdateCurrentPageTextAndPlaySound();
                    }
                    break;
                }
            }break;
            case PAGE_POKE_INFO2:
                switch (myTempData->select)
                {
                case 1:
                    if(myTempData->selectedBall < myTempData->ballCount){
                        myTempData->selectedBall ++;
                        UpdateCurrentPageTextAndPlaySound();
                    }
                    break;
                case 2:
                    if(myTempData->location == 0xD4){
                        myTempData->location = 0xFF;
                        UpdateCurrentPageTextAndPlaySound();
                    }
                    else if(myTempData->location < 0xFF){
                        myTempData->location ++;
                        UpdateCurrentPageTextAndPlaySound();
                    }
                    break;
                case 3:{
                    u8 temp = myTempData->selectedflightPoint + 1;
                    struct HealLocation *location = GetHealLocation(temp);
                    if(location){
                        myTempData->selectedflightPoint = temp;
                        UpdateCurrentPageTextAndPlaySound();
                    }
                }break;
                case 4:
                    #ifndef FIRE_RED_LEAF_GREEN
                    if(myTempData->time == 0){
                        myTempData->time = 23;
                        UpdateCurrentPageTextAndPlaySound();
                    }
                    else{
                        myTempData->time --;
                        UpdateCurrentPageTextAndPlaySound();
                    }
                    #endif
                    break;
                case 5:
                    myTempData->monCopy = !myTempData->monCopy;
                    UpdateCurrentPageTextAndPlaySound();
                    break;
                case 6:
                    #ifndef RUBY_SAPPHIRE
                    myTempData->obedience = !myTempData->obedience;
                    UpdateCurrentPageTextAndPlaySound();
                    #endif
                    break;
                default:
                    break;
                }
                break;
            case PAGE_IVS:
            case PAGE_EVS:{
                u8 *ivev = (u8 *)(&myTempData->hp);
                ivev += ivevMap[myTempData->select];
                u8 temp = ivev[0];
                if(temp){
                    ivev[0] --;
                    UpdateCurrentPageTextAndPlaySound();
                }
            }
            break;
            case PAGE_MOVES:
                if(getAttackNameValid(myTempData->attackBuffer+1)){
                    myTempData->attackBuffer++;
                    UpdateCurrentPageTextAndPlaySound();
                }
                break;
            case PAGE_SPECIE:{
                if(getMonSpeciesNameValid(myTempData->attackBuffer+1)){
                    myTempData->attackBuffer++;
                    UpdateCurrentPageTextAndPlaySound();
                }
            }break;
            case PAGE_ITEMS:{
                if(myTempData->select == 1){
                    u16 t = GetItemListBuffer(ITEM_TEXT_CURSOR_INDEX);
                    if(t < 6){
                        myTempData->itemBuffer = GetItemListBuffer(t+1);
                        UpdateCurrentPageTextAndPlaySound();
                    }
                }
                else if(myTempData->Num){
                    myTempData->Num--;
                    UpdateCurrentPageTextAndPlaySound();
                }
            }
            break;
            case PAGE_OTHER:{
                if(myTempData->species){
                    myTempData->species--;
			        UpdateCurrentPageTextAndPlaySound();
                }
            }
            break;
            case PAGE_POKE_NAME:
            case PAGE_PLAYER_NAME:
                PlaySound(SOUND_SELECT);
                KeyboardPreviousFlag();
            break;
            
        }
    }
    
}

void ButtonSelectEvent(){
    switch (myTempData->page)
    {
    case PAGE_POKE_NAME:
    case PAGE_PLAYER_NAME:
        myTempData->pageLock = !myTempData->pageLock;
        UpdateCurrentPageTextAndPlaySound();
        break;
    case PAGE_EVS:
        myTempData->limit510 = !myTempData->limit510;
        UpdateCurrentPageTextAndPlaySound();
        break;
    }
}

void ButtonStartEvent(){
    if (super->buttons3_new_remapped != BUTTONS_START)
        return;
    if(myTempData->page && myTempData->select != 8 && myTempData->cursorState == FALSE){
        myTempData->select = SELECT_SURE;
        UpDateSelectedMousePos();
    }
}
