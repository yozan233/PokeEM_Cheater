#include "header/funcs.h"

extern struct Pokemon *getCurrentPartyplayer();

const u8 ivevMap[] = {0,0,3,1,4,2,5};

void SetMousePos(u16 x,u16 y){
    if(x != 0)
        mouseXY->pos_x = x;
    if(y != 0)
        mouseXY->pos_y = y;
}

void BufferPos(){
	myTempData->posBuffer[0] = mouseXY->pos_x;
	myTempData->posBuffer[1] = mouseXY->pos_y;
}

bool8 IsPosChange(){
	return myTempData->posBuffer[0] != mouseXY->pos_x || myTempData->posBuffer[1] != mouseXY->pos_y;
}

void UpdateKeyboardMousePos(){
    u16 x,y;
    BufferPos();
    switch(myTempData->select){
        case 1:
            x = 0xE2;y = 0x4C;
            break;
        case 2:
            x = 0xE2;y = 0x5C;
            break;
        default:{
            u8 select = ~myTempData->select;
            x = 0x1C;
            y = 0x40 + udivsi3(select,10)*16;
            select = umodsi3(select,10);
            if(myTempData->fontType == FONT_CHINESE)
                x += (15*select);
            else
                x += (12*select);
        }
        break;
    }
    SetMousePos(x,y);
    if(IsPosChange())
        PlaySound(SOUND_SELECT);
}

void UpDateSelectedMousePos()
{
    BufferPos();
	u8 mode = MOUSE_POS_INFO;
	switch(myTempData->page){
		case PAGE_MAIN:
			mode = MOUSE_POS_MAIN;
			break;
		// case PAGE_POKE_INFO:
		// case PAGE_POKE_INFO2:
		// case PAGE_IVS:
		// case PAGE_EVS:
		// 	mode = MOUSE_POS_INFO;
		//	break;
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
};

void SelectNextMon(){
	u8 partyMax = ((u8 *)gPlayerPartyCount)[0];
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
void SelectPreviousMon(){
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

bool8 checkMonNmae(){
	u8 *name = (u8 *)BUFFER_2;
	u8 nickLength = textBuffer->monName[0x1F];
	textBuffer->monName[nickLength] = 0xFF;
	bool8 res;

	if(StringCompare(BUFFER_2+nickLength+1,BUFFER_2) != 0){
		res = FALSE;
	}
	else
		res = TRUE;
	return res;
}

bool8 MonRenameBySpecies(){
	u8 *speciesName = (u8 *) getMonSpeciesName(myTempData->attackBuffer);
	struct Pokemon* party = getCurrentPartyplayer();
	u8 *nickName = party->nickname;
	for (u32 n = 0; n < 0xB; n++){
		nickName[n] = speciesName[n];
	}
}

void SetPokedexFlag(u16 species){
	u16 index = SpeciesToNationalPokedexNum(species);
	GetSetPokedexFlag(index,2); //图鉴设置已发现的标识
	GetSetPokedexFlag(index,3); //图鉴设置已捕获的标识
}

bool8 check_802(){
	u32 gBaseStats = ((u32*)gBaseStats_Pointer)[0];
	return gBaseStats == 0x08F186E0;
}
bool8 check_Ultra_Emerald(){
	u32 ultraEmerald = ((u32*)0x080BB100)[0];
	return ultraEmerald == 0x09E0FF80;
}


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
		get_attackN();
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
		ldr_var4021();
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
	u8 penWuFlag = ((u8 *)(fun_ItemUseOutOfBattle_Repel+0xF))[0];
	if(penWuFlag == 6){
		return 0xFF;
	}
	else{
		return 0xFFFF;
	}
}

void ldr_var4021(){
	u16 var4021 = VarGet(0x4021);
	if(GetPenWuMax() == 0xFF){
		var4021 = (u8)var4021;
	}
	myTempData->species = var4021;
}

void changeMouseColor(){
	u16 *pal = (u16 *)OBJ_PaletteMem2;
	u16 color = pal[11];
	u16 red = 0x109F;
	if(color == red){
		pal[11] = 0x6546;
	}
	else{
		pal[11] = red;
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
	CpuSet(&textBuffer->newName,&getCurrentPartyplayer()->nickname,5);
}

u32 lvl2exp(u8 lvl){
	u8 flag = ((u8*)gmaxLvlOffsetFlag)[0];
	u32 size;
	if(flag == 0xCA){
		size = 0xCA<<1;
	}
	else{
		size = 0x20<<5;
	}
	u16 species = getCurrentMonData(ATTR_SPECIES);
	struct BaseStats* baseStats = getSpeciesBaseStats(species);
	u8 growthRate = baseStats->growthRate;
	u32 experienceTable = ((u32*)gExperienceTables_Pointer)[0];
	experienceTable += (growthRate*size);
	experienceTable += (lvl<<2);

	return experienceTable;
}

void shiye(){
	 struct SaveBlock1 *sav1 = (struct SaveBlock1*)((u32*)gSaveBlock1Ptr)[0];
	 sav1->flashLevel = 0;
	 u8 *pyramidFlag = (u8 *)(((u32*)gSaveBlock2Ptr)[0]+0x0E68);
	 if(pyramidFlag[0] != 0){
         pyramidFlag[0] = 0xC0;
	 }
}

void setvar(u16 id,u16 value){
    u16 *varPointer = GetVarPointer(id);
    varPointer[0] = value;
}

void set_bingdu(){
    myTempData->Num = 0xF;
    u8 partyMax = ((u8 *)gPlayerPartyCount)[0];
    struct Pokemon *party = (struct Pokemon *)gPlayerParty;
    for (u8 i=0;i<partyMax;i++){
		SetMonData(party,ATTR_POKERUS,&myTempData->Num);
		party++;
    }
}

void DelLastKeyitem(){
	struct BagPocket *keyitemsPocket = (struct BagPocket*)gBagPockets;
	keyitemsPocket += KEYITEMS_POCKET;
	u16 n = 0;
	while (n < keyitemsPocket->capacity){
		if (keyitemsPocket->itemSlots[n].itemId == 0)
			break;
		n++;
	}
	SetBagItemQuantity(&keyitemsPocket->itemSlots[n-1].quantity,0);
	keyitemsPocket->itemSlots[n-1].itemId = 0;
}

void pause(){
	asm("push {lr}\nmov r0, #0\nmov r1, #0xFF\nlsl r1, #0xA\npause_t:\nadd r0, #0x1\ncmp r0, r1\nbne pause_t\npop {pc}\nBX_R3:\nbx r3");
}

bool8 chck_PID(){
	// if(myTempData->page == PAGE_POKE_INFO2){
	// 	//changePID

	// }
	// if(myTempData->sex != myTempData->sex_2){
	// 	//G_PID

	// }
	// if (myTempData->nature != myTempData->nature_2){
	// 	//changePID
		
	// }
	// if(myTempData->shiny != myTempData->shiny_2){
	// 	//changePID

	// }

	// //G_PID:
	// u8 genderRatio = getSpeciesBaseStats(myTempData->species_2)->genderRatio;
	// switch(myTempData->sex_2){
	// 	case GENDER_FEMALE:
	// 		genderRatio -= 5;
	// 		break;
	// 	case GENDER_MALE:
	// 		genderRatio += 5;
	// 		break;
	// 	default:
	// 		//changePID
	// 		break;
	// }



	// return FALSE;

	asm("\
	push {lr}\n\
	ldr r3, buffer3_pid\n\
	ldrb r2, [r3]\n\
	cmp r2, #0x11\n\
	beq changePID\n\
	mov r2, r3\n\
	add r2, #0x10\n\
	add r3, #0x30\n\
	ldrb r0, [r2,#0x9]\n\
	ldrb r1, [r3,#0x9]\n\
	cmp r0, r1\n\
	bne G_PID\n\
	ldrb r0, [r2,#0x5]\n\
	ldrb r1, [r3,#0x5]\n\
	cmp r0, r1\n\
	bne changePID\n\
	ldrb r0, [r2,#0x8]\n\
	ldrb r1, [r3,#0x8]\n\
	cmp r0, r1\n\
	bne changePID\n\
	mov r0, #0x0\n\
	b notChange\n\
	G_PID:\n\
	ldrh r0, [r3,#0x2]\n\
	ldr r2, basestat_table_pid\n\
	ldr r2, [r2]\n\
	mov r1, #0x1C\n\
	mul r0, r1\n\
	add r0, r2\n\
	add r0, #0x10\n\
	ldrb r0, [r0]\n\
	ldrb r1, [r3,#0x9]\n\
	cmp r1, #0x1\n\
	beq gXY\n\
	cmp r1, #0x2\n\
	beq gXY\n\
	b changePID\n\
	gXY:\n\
	sub r0, #0x5\n\
	cmp r1, #0x2\n\
	beq isXX\n\
	add r0, #0xA\n\
	isXX:\n\
	sub r3, #0x10\n\
	strb r0, [r3]\n\
	\
	changePID:\n\
	ldr r3, buffer3_pid\n\
	mov r2, r3\n\
	add r2, #0x10\n\
	add r3, #0x40\n\
	mov r0, #0xFF\n\
	strh r0, [r3,#0x4]\n\
	ldrb r0, [r2,#0x5]\n\
	strh r0, [r3,#0x2]\n\
	ldrb r0, [r2,#0x8]\n\
	strh r0, [r3,#0x6]\n\
	ldrb r0, [r2]\n\
	strh r0, [r3]\n\
	mov r0, #0x1\n\
	notChange:\n\
	pop {pc}\n\
	.align 2\n\
	buffer3_pid:\n\
	.word 0x02021EC4\n\
	basestat_table_pid:\n\
	.word 0x080001BC"
	);
}

void SetText_MsgBox(u32 str)
{
	u8 boxid_t = mySav->boxId;
	FillWindowPixelBuffer(boxid_t,0x11);
	AddTextPrinterParameterized(boxid_t,1,str,6,0,0,0); //按键提示
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
	
}

void OnSureClick(){
    if(myTempData->page/0x10 == PAGETYPE_POKEMON && myTempData->egg){
        EggHatchNow();
        return;
    }

    switch (myTempData->page)
    {
    case PAGE_POKE_INFO:{
        if (myTempData->lvl != myTempData->lvl_2){
            setCurrentMonData(ATTR_EXP, lvl2exp(myTempData->lvl));
        }
        struct Pokemon* party = getCurrentPartyplayer();
        party->padding = 0;
        myTempData->Num = myTempData->ability;
        setCurrentMonData(ATTR_ABILITY_BIT,&myTempData->Num);
        myTempData->Num = myTempData->happiness;
        setCurrentMonData(ATTR_HAPPINESS,&myTempData->Num);
        if(myTempData->nature != myTempData->nature_2){
            if (chck_PID()){
                change_pid();
                reLoadPid();
            }
        }
        RefreshCurrentMonData();
        backupMonTempData();
    }
    break;
    case PAGE_POKE_INFO2:{
        if(myTempData->obedience != myTempData->obedienceTemp){
            myTempData->obedienceTemp = myTempData->obedienceTemp;
            setCurrentMonData(ATTR_OBEDIENCE, &myTempData->obedience);
            u32 mTid = GetPlayerIDAsU32();
            if (myTempData->obedience == 0xFF)
            {
                if (myTempData->TID == mTid)
                {
                    myTempData->TID -= 10;
                    chck_PID();
                    change_pid();
                    reLoadPid();
                }
            }
            else
            {
                if (myTempData->TID != mTid)
                {
                    myTempData->TID = mTid;
                    chck_PID();
                    change_pid();
                    reLoadPid();
                }
                setCurrentMonData(ATTR_OT_NAME, getPlayerNameOffset());
            }
        }
        
        struct Time *getTime = (struct Time *)gLocalTime;
        u8 t = getTime->hours;
        if (t != myTempData->time)
        {
            RtcInitLocalTimeOffset(myTempData->time, 0); //设置时间
        }
        
        setCurrentMonData(ATTR_CATCH_LOCATION, &myTempData->location);

        if (myTempData->itemBuffer)
            setCurrentMonData(ATTR_POKEBALL, &myTempData->itemBuffer);

        RefreshCurrentMonData();

        if (myTempData->monCopy)
        {
            u32 r = GiveMonToPlayer(getCurrentPartyplayer());
            if (r != 2)
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
        
        if (myTempData->selectedflightPoint)
        {
            BeginNormalPaletteFade(-1, 0, 0, 0x10, 0);
            HealPlayerParty();
            DestroyTask(mySav->task_id);
            FreeAllWindowBuffers();
            Free(*malloc_pointer_loc);
            struct FlightPoint *fly_p = (struct FlightPoint *)sHealLocations;
            fly_p += (myTempData->selectedflightPoint-1);
            SetWarpDestination(fly_p->bank, fly_p->map, -1, fly_p->pos_x, fly_p->pos_y);
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
        if(checkMonNmae()){
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
            u32 successText = text_table[TEXT_INSUFFICIENT_SPACE];
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
            FlagSet(0x896);
            EnableNationalPokedex();
        }
        if (myTempData->mirageShow){
            setvar(0x4024, getCurrentMonData(ATTR_PID) & 0xFFFF);
        }
        else{
            setvar(0x4024, Random());
        }
        if (myTempData->pokerus){
            set_bingdu();
        }
        if (myTempData->visualRangeMax){
            shiye();
        }
        u8 *cq = (u8 *)throughWallFlag;
        cq[0] = myTempData->throughWall;
        setvar(0x4021, myTempData->species);
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
    u8 eggLvl = ((u8 *)eggHatchLevel_Pointer)[0];
    CreateMon(getCurrentPartyplayer(), spe, eggLvl, 32, 1, Random() | (Random() << 0x10), 0, myTempData->TID);
    myTempData->Num = 0;
    SetMonData(getCurrentPartyplayer(), 0x24, &myTempData->Num);
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
        u32 textButtonPrompt = text_table[TEXT_BUTTON_PROMPT4];
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
                if(myTempData->select == 8){
                    if(myTempData->page == PAGE_SPECIE)
                        myTempData->select = 4;
                    else{
                        myTempData->select = myTempData->attackSelect+1;
                    }
                }  
                else if (myTempData->select == 7)
                    myTempData->select = 8;
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
				else if(myTempData->lvl){
					myTempData->lvl = 0;
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
            if(myTempData->select == 4){
                if(myTempData->time > 3){
                    myTempData->time -= 3;
                }
                else{
                    myTempData->time = 24+myTempData->time-3;
                }
                UpdateCurrentPageTextAndPlaySound();
            }
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
        case PAGE_SPECIE:
            if(myTempData->select == 4 && myTempData->attackBuffer > 1){
                if(myTempData->attackBuffer > 4){
                    myTempData->attackBuffer -= 4;
                }
                else
                    myTempData->attackBuffer = 1;
                UpdateCurrentPageTextAndPlaySound();
            }
            break;
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
                u16 t = GetItembuffer(ITEM_TEXT_CURSOR_INDEX);
                if(t){
                    myTempData->itemBuffer = GetItembuffer(0);
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
            if(myTempData->select == 4){
                if(myTempData->time < 21){
                    myTempData->time += 3;
                }
                else{
                    myTempData->time = myTempData->time - 21;
                }
                UpdateCurrentPageTextAndPlaySound();
            }
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
            }
			else if(ivev[0] != max){
				ivev[0] = max;
                UpdateCurrentPageTextAndPlaySound();
            }

        }
        break;
        case PAGE_MOVES:{
            u8 rt = 1;
            while (rt <= 4){
                if(!getAttackName(myTempData->attackBuffer+rt))
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
                u16 pmax = gPokeMax;
                if(check_802())
                    pmax-=2;
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
                u16 t = GetItembuffer(ITEM_TEXT_CURSOR_INDEX);
                if(t < 6){
                    myTempData->itemBuffer = GetItembuffer(6);
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
					    get_attackN();
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
            SelectPreviousMon();
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
                    if(myTempData->sex == 1 || myTempData->sex == 2){
                        myTempData->sex = !(myTempData->sex-1)+1;
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
                if(myTempData->time == 23){
                    myTempData->time = 0;
                    UpdateCurrentPageTextAndPlaySound();
                }
                else{
                    myTempData->time ++;
                    UpdateCurrentPageTextAndPlaySound();
                }
                break;
            case 5:
                myTempData->monCopy = !myTempData->monCopy;
                UpdateCurrentPageTextAndPlaySound();
                break;
            case 6:
                myTempData->obedience = !myTempData->obedience;
                UpdateCurrentPageTextAndPlaySound();
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

            if(temp < max-1){
				ivev[0]++;
                UpdateCurrentPageTextAndPlaySound();
            }
			else if(max){
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
				u16 t = GetItembuffer(ITEM_TEXT_CURSOR_INDEX);
				if(t){
					myTempData->itemBuffer = GetItembuffer(t-1);
					UpdateCurrentPageTextAndPlaySound();
				}
			}
			else if(myTempData->Num < 99){
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
					    get_attackN();
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
                    if(myTempData->select == 1)
                        myTempData->select = 8;
                    else if(myTempData->select == 4)
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
            SelectNextMon();
            return;
        }
        switch(myTempData->page){
            case PAGE_POKE_INFO:{
                switch (myTempData->select)
                {
                case 1:
                    if(myTempData->lvl){
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
                    if(myTempData->sex == 1 || myTempData->sex == 2){
					    myTempData->sex = !(myTempData->sex-1)+1;
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
                case 3:
                    if(myTempData->selectedflightPoint <= myTempData->flightPointCount){
                        myTempData->selectedflightPoint ++;
                        UpdateCurrentPageTextAndPlaySound();
                    }
                    break;
                case 4:
                    if(myTempData->time == 0){
                        myTempData->time = 23;
                        UpdateCurrentPageTextAndPlaySound();
                    }
                    else{
                        myTempData->time --;
                        UpdateCurrentPageTextAndPlaySound();
                    }
                    break;
                case 5:
                    myTempData->monCopy = !myTempData->monCopy;
                    UpdateCurrentPageTextAndPlaySound();
                    break;
                case 6:
                    myTempData->obedience = !myTempData->obedience;
                    UpdateCurrentPageTextAndPlaySound();
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
                if(getAttackName(myTempData->attackBuffer+1)){
                    myTempData->attackBuffer++;
                    UpdateCurrentPageTextAndPlaySound();
                }
                break;
            case PAGE_SPECIE:{
                u16 pmax = gPokeMax;
                if(check_802())
                    pmax-=2;
                if(myTempData->attackBuffer < pmax){
                    myTempData->attackBuffer++;
                    UpdateCurrentPageTextAndPlaySound();
                }
            }break;
            case PAGE_ITEMS:{
                if(myTempData->select == 1){
                    u16 t = GetItembuffer(ITEM_TEXT_CURSOR_INDEX);
                    if(t < 6){
                        myTempData->itemBuffer = GetItembuffer(t+1);
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
