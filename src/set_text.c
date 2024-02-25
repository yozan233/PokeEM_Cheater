#include "header/funcs.h"

extern u32 check_802();
// extern void set_zi();
extern u32 GetPenWuMax();
extern struct Pokemon *getCurrentPartyplayer();
extern u32 getCurrentMonData(u8 request);
extern struct BaseStats* getSpeciesBaseStats(u16 species);
extern u32 getMonSpeciesName(u16 species);
u8 getMapId(u16 mapGroup, u16 mapNum);
u32 getPlayerNameOffset();
u16 get_ballNum(u8 index);
u16 get_attackN0(u8 n);
u8 getMoveAttr(u8 n);
u32 getTypeName(u8 type);
bool8 checkString(u8 *str,u32 length);
u32 getAttackName(u16 atackNum);
u32 getAbilityName();
bool8 checkPicLZ(struct LZData *data);
bool8 checkLZ(struct LZData *data);
u32 getItemName(u16 itemId);
u16 GetItembuffer(u8 index);
void UpdatePageValue(u8 page);
u32 GetAuthorText();
u32 GetVersionText();

const u8 sTrainerCardTextColors[] = {0, 2, 3};

void UpdatePageValue(u8 page)
{
	switch(page){
		case PAGE_POKE_INFO:{
			u32 temp = &myTempData->numTextBuff;
			ConvertUIntToDecimalStringN(temp,myTempData->lvl,2,3);
			UpdateString(60,28,temp,3);//等级
			ConvertUIntToDecimalStringN(temp,myTempData->happiness,2,3);
			UpdateString(168,28,temp,3);//亲密度
			u32 naturesTable = text_table[TEXT_NATURES_TABLE];
			temp = naturesTable+5*myTempData->nature;
			UpdateString(60,56,temp,5);//性格
			temp = getAbilityName();
			if(!temp){
				temp = text_table[TEXT_UNKNOWN_ABILITY]+6*myTempData->ability;
			}
			UpdateString(60,84,temp,5);//特性
			temp = text_table[TEXT_NOTSHINY]+2*myTempData->shiny;
			UpdateString(160,56,temp,3);//闪光
			temp = text_table[TEXT_GENDER_TABLE]+4*myTempData->sex;
			UpdateString(160,84,temp,1);//性别
		}return;
		case PAGE_POKE_INFO2:{
			ConvertUIntToDecimalStringN(&myTempData->numTextBuff,myTempData->time,2,2);
			ClearStringForWidth(156,56,12);
			PrintText(156,56,&myTempData->numTextBuff);//时间
			UpdateString(76,84,text_table[TEXT_CIRCLE_DOT]+(myTempData->monCopy)*4,1);
			UpdateString(172,84,text_table[TEXT_CIRCLE_DOT]+(myTempData->obedience)*4,1);

			u32 mapName = textBuffer->temp;
			if(myTempData->location <= 0xD4)
				GetMapName(mapName,myTempData->location,0);
			else if (myTempData->location == 0xFF)
				mapName = text_table[TEXT_FATEFUL_ENCOUNTER];
			else
				mapName = text_table[TEXT_SOMEWHERE];
			UpdateString(164,28,mapName,5);//捕获地

			if(myTempData->selectedBall == 0){
				UpdateString(60,28,text_table[TEXT_NONE],5);
				myTempData->itemBuffer = 0;
			}
			else{
				u16 ball = get_ballNum(myTempData->selectedBall-1);
				UpdateString(60,28,getItemName(ball),5);//球种
				myTempData->itemBuffer = ball;
			}
				
			//飞行点
			if(myTempData->selectedflightPoint == 0)
				UpdateString(60,56,text_table[TEXT_NONE],5);
			else{
				struct HealLocation *location = GetHealLocation(myTempData->selectedflightPoint);
				u16 m = getMapId(location->group, location->map);
				u32 mapName2 = textBuffer->temp+0x20;
				GetMapName(mapName2,m,0);
				UpdateString(60,56,mapName2,5);
			}
			
		}return;
		case PAGE_IVS:
		case PAGE_EVS:
			if(myTempData->cursorState == FALSE || myTempData->select == 0)
				LoadMonIVEV();
			if(myTempData->page == PAGE_EVS){
				PrintSmallText(40,104,text_table[TEXT_LIMIT510]);
				UpdateSmallString(32,104,text_table[TEXT_CIRCLE_DOT]+myTempData->limit510*4,1);//添加[点]
			}
			
			UpdateNumString(60,28,myTempData->hp);//HP
			UpdateNumString(60,56,myTempData->attack);//物攻
			UpdateNumString(60,84,myTempData->defence);//物防
			UpdateNumString(160,28,myTempData->speed);//速度
			UpdateNumString(160,56,myTempData->SP_attack);//特攻
			UpdateNumString(160,84,myTempData->SP_defence);//特防
			return;
		case PAGE_MOVES:{
			u32 textNone = text_table[TEXT_NONE];
			FillWindowPixelRect(0,0,18,20,12*6,4*16);
			FillWindowPixelRect(0,0,128,16,12*8,5*16+8);

			for(u8 i = 0;i <= 3;i++){
				if(get_attackN0(i))
					UpdateString(18,20+i*18,getAttackName(get_attackN0(i)),6);
				else
					UpdateString(18,20+i*18,textNone,6);
			}
			
			u8 power = getMoveAttr(1);//威力
			if(power){
				UpdateNumSmallString(44,92,power);
			}
			else
				UpdateSmallString(44,92,textNone,3);
			UpdateSmallString(102,92,getTypeName(getMoveAttr(2)),3);//属性
			u8 accuracy = getMoveAttr(3);//命中率
			if(accuracy){
				UpdateNumSmallString(44,106,accuracy);
			}
			else{
				UpdateSmallString(44,106,textNone,3);
			}
			UpdateNumSmallString(102,106,getMoveAttr(4));//PP
			u16 attN = myTempData->attackBuffer;
			u32 a = 0;
			while(a < 2){
				attN--;
				if(attN == 0)
					break;
				a++;
			}
			attN = myTempData->attackBuffer;
			u32 b = 0;
			while(b < 2){
				attN++;
				if(!getAttackName(attN))
					break;
				b++;
			}
			if(a+b<4){
				if(a<2)
					b=4-a;
				else
					a=4-b;
			}
			attN = myTempData->attackBuffer;
			u32 n = 0;
			while (a){
				UpdateNumHexString(136,n*18+16,attN-a);//技能编号
				PrintText(156,n*18+16,getAttackName(attN-a));//前
				n++;
				a--;
			}
			PrintText(128,n*18+16,text_table[TEXT_CURSOR]);
			UpdateNumHexString(136,n*18+16,attN);//技能编号
			PrintText(156,n*18+16,getAttackName(attN));//中
			n++;
			u32 m = 1;
			while (m<=b){
				UpdateNumHexString(136,n*18+16,attN+m);
				PrintText(156,n*18+16,getAttackName(attN+m));//后
				m++;
				n++;
			}
		}return;
		case PAGE_SPECIE:{
			set_poke_tile();
			loadSpecieData();
			
			u8 *specieData = (u8 *)&myTempData->hp;
			for(int k = 0; k < 6; k++){
				UpdateNumSmallString(42,28+k*14,specieData[k]);
			}

			u32 a5 = 0;
			u16 pokeN = myTempData->attackBuffer;

			UpdateNumHexString(94,98,pokeN);//精灵编号

			FillWindowPixelRect(0,0,128,16,12*8,5*16+8);
			
			while(a5 < 2){
				pokeN--;
				if(pokeN == 0)
					break;
				a5++;
			}
			pokeN = myTempData->attackBuffer;
			u32 b5 = 0;
			while(b5 < 2){
				pokeN++;
				u16 pmax = MON_COUNT;
				if(check_802())
					pmax-=2;
				if(pokeN > pmax)
					break;
				b5++;
			}
			if(a5+b5<4){
				if(a5<2)
					b5=4-a5;
				else
					a5=4-b5;
			}
			
			pokeN = myTempData->attackBuffer;
			u32 n5 = 0;
			while (a5){
				PrintText(156,n5*18+16,getMonSpeciesName(pokeN-a5));//前
				n5++;
				a5--;
			}
			PrintText(148,n5*18+16,text_table[TEXT_CURSOR]);
			PrintText(156,n5*18+16,getMonSpeciesName(pokeN));//中
			n5++;
			u32 m5 = 1;
			while (m5<=b5){
				PrintText(156,n5*18+16,getMonSpeciesName(pokeN+m5));//后
				m5++;
				n5++;
			}
		}return;
		case PAGE_POKE_NAME:
		case PAGE_PLAYER_NAME:
			UpdateKeyboardValue();
			return;
		case PAGE_ITEMS:{
			set_item_tile();
			ConvertUIntToDecimalStringN(&myTempData->numTextBuff,myTempData->Num,2,2);
			UpdateString(156,26,&myTempData->numTextBuff,2);//数值
			UpdateString(108,50,text_table[TEXT_CIRCLE_DOT]+ 4*myTempData->addItemEnable,1);//添加[点]
			UpdateString(108,70,text_table[TEXT_CIRCLE_DOT]+ 4*myTempData->throwKeyItemEnable,1);//扔掉一个重要道具[空心点]
			
			FillWindowPixelRect(0,0,0,0,12*7+6*4,16*7+4);
			u16 S=myTempData->itemBuffer;
			u32 a6=0,i6=0;
			while(a6 < 3){
				if(S==1)
					break;
				S--;
				u32 itemN = getItemName(S);
				if (itemN == 0)
					break;
				else if(itemN != 1){
						SetItembuffer(i6,S);
						a6++;
						i6++;
					}
			}
			SortItemBuffer(a6);
			
			SetItembuffer(i6,myTempData->itemBuffer);
			i6++;

			u32 b6 = 3;
			if(a6 < 3)
				b6 = 6-a6;
			S=myTempData->itemBuffer;
			while(b6){
				S++;
				u32 itemN = getItemName(S);
				if (itemN == 0)
					break;
				else if(itemN != 1){
						SetItembuffer(i6,S);
						b6--;
						i6++;
					}
			}
			
			if(b6){
				MoveItemBuffer(b6);
				S = GetItembuffer(0);
				a6=0,i6=0;
				while(a6 < b6){
					S--;
					u32 itemN = getItemName(S);
					if (itemN == 0)
						break;
					else if(itemN != 1){
							SetItembuffer(i6,S);
							a6++;
							i6++;
						}
				}
				SortItemBuffer(a6);
			}
			u32 text6t = &myTempData->numTextBuff;
			for(u8 k=0;k<7;k++){
				u16 Na = GetItembuffer(k);
				if(Na == myTempData->itemBuffer)
				{
					PrintText(0,k*17,text_table[TEXT_CURSOR]);
					SetItembuffer(ITEM_TEXT_CURSOR_INDEX,k);
				}
				PrintText(30,k*17,getItemName(Na));//道具名称
				ConvertIntToHexStringN(text6t,Na,2,3);
				PrintText(9,k*17,text6t);//道具编号
			}
		}return;
		case PAGE_OTHER:{
			u8 numLength = 5;
			if(GetPenWuMax() == 255)
				numLength -= 2;
			ConvertUIntToDecimalStringN(&myTempData->numTextBuff,myTempData->species,2,numLength);
			UpdateString(156,20,&myTempData->numTextBuff,4);
			UpdateString(20,20,text_table[TEXT_CIRCLE_DOT] + 4 * myTempData->pokedexUpgrade,1);
			UpdateString(20,48,text_table[TEXT_CIRCLE_DOT] + 4 * myTempData->pokerus,1);
			UpdateString(20,76,text_table[TEXT_CIRCLE_DOT] + 4 * myTempData->mirageShow,1);
			UpdateString(120,48,text_table[TEXT_CIRCLE_DOT] + 4 * myTempData->visualRangeMax,1);
			UpdateString(120,76,text_table[TEXT_CIRCLE_DOT] + 4 * myTempData->throughWall,1);
		}return;
		default:
			return;
	}
	
}

void InitPage(u8 page){
	myTempData->page = page;
	switch (page)
	{
	case PAGE_MAIN:
		HideSprite(mySav->itemPicId);
		HideSprite(mySav->monIconId);
		HideSprite(mySav->monPicId);
		break;
	case PAGE_POKE_INFO:
		initMonTempData();
		ShowSprite(mySav->monIconId);
		break;
	case PAGE_POKE_INFO2:
		get_ball_addr();
		break;
	case PAGE_EVS:{
		myTempData->limit510 = FALSE;
	}break;
	case PAGE_POKE_NAME:
		SetShowNickNameOnly(TRUE);
	case PAGE_PLAYER_NAME:
		myTempData->select = SELECT_CANCEL;
		HideSprite(mySav->monPicId);
		InitKeyboard();
		break;
	case PAGE_MOVES:
		myTempData->attackSelect = 0;
		if(myTempData->select > 4)
			myTempData->select = 7;
		HideSprite(mySav->monPicId);
		get_attackN();
		break;
	case PAGE_SPECIE:
		ShowSprite(mySav->monPicId);
		SetShowNickNameOnly(FALSE);
		myTempData->attackBuffer = myTempData->species;
		if(myTempData->select > 4)
			myTempData->select = 7;
		else if(myTempData->select != 0)
			myTempData->select = 4;
		myTempData->attackSelect = 3;
		break;
	case PAGE_ITEMS:
		myTempData->Num = 1;
		myTempData->itemBuffer = 1;
		myTempData->addItemEnable = TRUE;
		myTempData->throwKeyItemEnable = FALSE;
		ShowSprite(mySav->itemPicId);
		CpuFastFill(0,itemTilesArm,0x800);
		break;
	case PAGE_OTHER:
		throughWallFlag[0] = FALSE;
		((u8 *)myTempData)[0x46] = 0;
		ldr_var4021();
		myTempData->select = SELECT_CANCEL;
		break;
	default:
		break;
	}
	SetPageTxet(page);
	if(page/0x10 != PAGETYPE_POKEMON || !myTempData->egg){
		UpdatePageValue(page);
	}
	myTempData->soundMute = TRUE;
	UpDateSelectedMousePos();
	myTempData->soundMute = FALSE;
}

void SetPageTxet(u8 page){
	FillWindowPixelBuffer(0,0); //清空全部文本
	if(page != PAGE_MAIN){
		PrintSmallText(176,104,text_table[TEXT_SURE]);//确认
		PrintSmallText(204,104,text_table[TEXT_CANCEL]);//取消
	}
	u32 pageTpye = page/0x10;
	if(pageTpye == PAGETYPE_POKEMON){
		ShowMonName();
		if(myTempData->egg){
			HideSprite(mySav->monPicId);
			PrintText(80,56,text_table[TEXT_HATCH_NOW]);
			return;
		}
	}
	
	switch (page)
	{
	case PAGE_MAIN:
		PrintText(24,56,text_table[TEXT_MON]); //精灵
		PrintText(96,56,text_table[TEXT_BAG]); //背包
		PrintText(168,56,text_table[TEXT_OTHER]); //其它
		SetText_MsgBox(text_table[TEXT_BUTTON_PROMPT1]);//按键提示
		PrintSmallText(0,0,GetAuthorText());//作者
		PrintSmallText(176,0,GetVersionText());//版本号
		break;
	case PAGE_POKE_INFO:
		PrintText(24, 28, text_table[TEXT_LEVEL]);		 //等级
		PrintText(24, 56, text_table[TEXT_NATURES]);	 //性格
		PrintText(24, 84, text_table[TEXT_ABILITY]);	 //特性
		PrintText(124, 28, text_table[TEXT_HAPPINESS]); //亲密度
		PrintText(124, 56, text_table[TEXT_SHINY]);	 //闪光
		PrintText(124, 84, text_table[TEXT_GENDER]);	 //性别
		SetText_MsgBox(text_table[TEXT_BUTTON_PROMPT3]);
		break;
	case PAGE_POKE_INFO2:{
		PrintText(24,28,text_table[TEXT_BALL_TYPE]);//球种
		PrintText(120,28,text_table[TEXT_CATCH_LOCATION]);//捕获地
		PrintText(24,56,text_table[TEXT_TELEPORT]);//瞬移
		PrintText(120,56,text_table[TEXT_TIME]);//时间
		PrintText(170,56,text_table[TEXT_HOUR]);//时
		PrintText(24,84,text_table[TEXT_MON_COPY]);//复制精灵
		PrintText(120,84,text_table[TEXT_MON_OBEDIENCE]);//精灵听话
	}break;
	case PAGE_IVS:
	case PAGE_EVS:{
		PrintText(30,28,text_table[TEXT_HP]);//HP
		PrintText(24,56,text_table[TEXT_ATTACK]);//物攻
		PrintText(24,84,text_table[TEXT_DEFENSE]);//物防
		PrintText(124,28,text_table[TEXT_SPEED]);//速度
		PrintText(124,56,text_table[TEXT_SP_ATTACK]);//特攻
		PrintText(124,84,text_table[TEXT_SP_DEFENSE]);//特防
		u32 ivevTitle = text_table[TEXT_IV+(myTempData->page-PAGE_IVS)];
		PrintText(180,0,ivevTitle);//个体/努力
	}break;
	case PAGE_POKE_NAME:
	case PAGE_PLAYER_NAME:
		PrintSmallText(170,48,text_table[TEXT_INITIALS]);//首字母
		PrintSmallText(170,68,text_table[TEXT_DELETE]);//删除
		break;
	case PAGE_MOVES:
		PrintSmallText(04,92,text_table[TEXT_MOVE_POWER]);
		PrintSmallText(70,92,text_table[TEXT_MOVE_TYPE]);
		PrintSmallText(04,106,text_table[TEXT_MOVE_ACCURACY]);
		PrintSmallText(70,106,text_table[TEXT_PP]);
		break;
	case PAGE_SPECIE:
		PrintSmallText(14,28+0*14,text_table[TEXT_HP]);//HP
		PrintSmallText(10,28+1*14,text_table[TEXT_ATTACK]);//物攻
		PrintSmallText(10,28+2*14,text_table[TEXT_DEFENSE]);//物防
		PrintSmallText(10,28+3*14,text_table[TEXT_SPEED]);//速度
		PrintSmallText(10,28+4*14,text_table[TEXT_SP_ATTACK]);//特攻
		PrintSmallText(10,28+5*14,text_table[TEXT_SP_DEFENSE]);//特防
		break;
	case PAGE_ITEMS:
		PrintText(120,50,text_table[TEXT_ADD_ITEM]);//添加
		PrintText(120,26,text_table[TEXT_QUANTITY]);//数量
		PrintText(120,70,text_table[TEXT_THROW_KEYITEM]);//扔掉一个重要道具
		SetText_MsgBox(text_table[TEXT_BUTTON_PROMPT2]);
		break;
	case PAGE_OTHER:
		PrintText(32,20,text_table[TEXT_POKEDEX_UPGRADE]);//升级图鉴
		PrintText(32,48,text_table[TEXT_POKERUS]);//精灵病毒 
		PrintText(32,76,text_table[TEXT_MIRAGE_SHOW]);//出现幻岛 
		PrintText(120,20,text_table[TEXT_SPRAY]);//喷雾
		PrintText(132,48,text_table[TEXT_VISUAL_RANGE_MAX]);//视野
		PrintText(132,76,text_table[TEXT_THROUGH_WALL]);//穿墙
		SetText_MsgBox(text_table[TEXT_BUTTON_PROMPT3]);
		break;
	}
}

void ShowMonName(){
	if (myTempData->egg)
	{
		UpdateString(44, 0, text_table[TEXT_EGG],12); //蛋
	}
	else
	{
		UpdateString(44, 0, textBuffer->monName,12); //昵称/种族
	}
}

void ShowPlayerName(){
	UpdateString(10,0,getPlayerNameOffset(),7); //玩家名
}

void SetShowNickNameOnly(bool8 b){
	u8 nickLength = textBuffer->monName[0x1F];
	textBuffer->monName[nickLength] = b?0xFF:0xBA;
}

u16 AnalysisText(u8 *src, u8 *dest,u32 len){
	u16 i, j;
    u16 crc = 0x1121;
    for (i = 0; i < len; i++)
    {
        crc ^= src[i];
		dest[i] = src[i] ^ 0xAB;
        for (j = 0; j < 8; j++)
        {
            if (crc & 1)
                crc = (crc >> 1) ^ 0x8408;
            else
                crc >>= 1;
        }
    }
    return ~crc;
}

u32 GetAuthorText(){
	u8* authorText = text_table[TEXT_AUTHOR];
	int len = 10;
	u16 authorCrc = AnalysisText(authorText,textBuffer->temp,len);
	if(authorCrc != 0x0710){
		asm("swi #0");//SoftReset
	}
	return textBuffer->temp;
}

u32 GetVersionText(){
	u8 *versionText = text_table[TEXT_VERSION];
	int len = 13;
	u16 versionCrc = AnalysisText(versionText,textBuffer->temp,len);
	if(versionCrc != 0x3D9F){
		asm("swi #0");//SoftReset
	}
	return textBuffer->temp;
}

void PrintSmallText(u8 x, u8 y, u8 *str){
	AddTextPrinterParameterized3(0,0,x,y,sTrainerCardTextColors,0,str);
}

void PrintText(u8 x, u8 y, u8 *str){
	AddTextPrinterParameterized3(0,1,x,y,sTrainerCardTextColors,0,str);
}

void UpdateString(u8 x, u8 y, u8 *str,u16 len){
	ClearStringForWidth(x,y,len*12);
	PrintText(x,y,str);
}

void UpdateNumString(u8 pos_x, u8 pos_y, u32 num){
	u32 numTextBuff = &myTempData->numTextBuff;
	ConvertUIntToDecimalStringN(numTextBuff,num,2,3);
	UpdateString(pos_x,pos_y,numTextBuff,3);
}

void UpdateNumHexString(u8 pos_x, u8 pos_y, u32 num){
	u32 numTextBuff = &myTempData->numTextBuff;
	ConvertIntToHexStringN(numTextBuff,num,2,3);
	UpdateString(pos_x,pos_y,numTextBuff,3);
}

void UpdateNumSmallString(u8 pos_x, u8 pos_y, u32 num){
	u32 numTextBuff = &myTempData->numTextBuff;
	ConvertUIntToDecimalStringN(numTextBuff,num,2,3);
	UpdateSmallString(pos_x,pos_y,numTextBuff,3);
}

void UpdateSmallString(u8 pos_x, u8 pos_y, u8 *str,u16 len){
	ClearStringForWidth(pos_x,pos_y,8*len);
	PrintSmallText(pos_x,pos_y,str);
}

void ClearStringForWidth(u16 pos_x, u16 pos_y, u16 width){
	FillWindowPixelRect(0,0,pos_x,pos_y,width,14);
}

u8 getMapId(u16 mapGroup, u16 mapNum){
	struct MapHeader *header = (struct MapHeader*) GetMapHeaderByGroupAndId(mapGroup,mapNum);
	return header->regionMapSectionId;
}

u32 getPlayerNameOffset(){
	return &gSaveBlock2Ptr->playerName;
}

void loadSpecieData(){
	struct BaseStats* baseStats = getSpeciesBaseStats(myTempData->attackBuffer);  //这里attackBuffer用来暂存种族编号
	CpuSet(baseStats,&myTempData->hp,3);
}

void ShowSprite(u8 id){
	u8 *sprite = getSprite(id);
	sprite[1] = 0;
}

void HideSprite(u8 id){
	u8 *sprite = getSprite(id);
	sprite[1] = 8;
}

void get_ball_addr(){
    u8 location = getCurrentMonData(ATTR_CATCH_LOCATION);
	myTempData->location = location;
	u8 obedience = getCurrentMonData(ATTR_OBEDIENCE);
	myTempData->obedience = obedience;
	myTempData->obedienceTemp = obedience;
	myTempData->selectedflightPoint = 0;
	myTempData->selectedBall = 0;
	myTempData->monCopy = FALSE;
	myTempData->selectedBall = 0;
	myTempData->time = gLocalTime.hours;
	getBallCount();
}

u16 get_ballNum(u8 index){
	struct BagPocket *ballsPocket = &gBagPockets[BALLS_POCKET];
	if(myTempData->ballCount > index){
		return ballsPocket->itemSlots[index].itemId;
	}
	else
		return 0;
}

void getBallCount(){
	struct BagPocket *ballsPocket = &gBagPockets[BALLS_POCKET];
	u16 n = 0;
	while (n < ballsPocket->capacity){
		if (ballsPocket->itemSlots[n].itemId == 0)
			break;
		n++;
	}
	myTempData->ballCount = n;
}

void get_attackN(){
	u16 attack = getCurrentMonData(myTempData->attackSelect+ATTR_ATTACK_1);
	if (attack != 0){
		myTempData->attackBuffer = attack;
	}
	else
		myTempData->attackBuffer = 1;
}

u16 get_attackN0(u8 n){
	u8 request = ATTR_ATTACK_1+n;
	getCurrentMonData(request);
}

u32 getAttackName(u16 atackNum){
	u32 moveNames = gMoveNamesPtr;
	moveNames += (atackNum*MOVE_NAME_LENGTH);
	u8 *name = (u8 *)moveNames;
	if(name[0] == 0xAE){
		return text_table[TEXT_NONE];
	}
	if(checkString(name,MOVE_NAME_LENGTH)){
		return name;
	}
	else{
		return 0;
	}
}

u32 getBattleTextBuff(u8 type,u8 value){
	CpuFastFill(-1,textBuffer->temp,16);
	u8 data[] = {0,type,value,0xFF};
	ExpandBattleTextBuffPlaceholders(data,textBuffer->temp);
	return textBuffer->temp;
}

u32 getAbilityName(){
	struct BaseStats* baseStats = getSpeciesBaseStats(myTempData->species);
	u8 abilitie = baseStats->abilities[myTempData->ability];

	u32 abilityName = getBattleTextBuff(B_BUFF_ABILITY,abilitie);
	if (checkString(abilityName,0xC)){
		return abilityName;
	}
	
	return 0;
}

u32 gettypeName(u8 type){
	u32 typeNames = getBattleTextBuff(B_BUFF_TYPE,type);
	return typeNames;
}

bool8 checkString(u8 *str,u32 length){
	bool8 eosFlag = FALSE;
	u32 i = 0;
	while (i < length){
		if(str[i] == 0xFF){
			eosFlag = TRUE;
			break;
		}
		i++;
	}
	if(eosFlag && i > 0){
		return TRUE;
	}
		
	return FALSE;
}

void LoadMonIVEV(){
	u8 request;
	if (myTempData->page == PAGE_IVS){
		request = ATTR_HP_IV;
	}
	else{
		request = ATTR_HP_EV;
	}
	u8 *eviv = (u8 *)&myTempData->hp;
	for (u8 i = 0; i < 6; i++,request++){
		eviv[i] = getCurrentMonData(request);
	}
}

//获取技能参数 
//0 effect; 1 power; 2 type; 3 accuracy;4 pp; 5 secondaryEffectChance;6 target;7 priority;8 flags;
u8 getMoveAttr(u8 n){
	u32 battleMovespecies = gBattleMovesPtr;
	battleMovespecies += myTempData->attackBuffer*MOVE_DATA_SIZE;
	u8 attr = ((u8 *)battleMovespecies)[n];
	return attr;
}

void set_item_tile(){
	struct ItemIcon *itemIconTableBase = (struct ItemIcon *)gItemIconTablePtr;
	struct ItemIcon *itemIcon = itemIconTableBase + myTempData->itemBuffer;
	
	if(!checkPicLZ(itemIcon->tiles))
		itemIcon = itemIconTableBase;
	
	LZ77UnCompVram(itemIcon->tiles,itemTilesArm+0x400);
	CopyItemIconPicTo4x4Buffer(itemTilesArm+0x400,itemTilesArm);

	if(!checkLZ(itemIcon->pal))
		itemIcon = itemIconTableBase;
	LZ77UnCompVram(itemIcon->pal,&OBJ_PaletteMem2[0x40]);
}

void set_poke_tile(){
	struct CompressedSpriteSheet *monFrontPicTable = (struct CompressedSpriteSheet *)(gMonFrontPicTablePtr);
	struct CompressedSpriteSheet *monFrontPic = monFrontPicTable + myTempData->attackBuffer;
	if(!checkPicLZ(monFrontPic->data))
		monFrontPic = monFrontPicTable;
	
	LZ77UnCompVram(monFrontPic->data,monTilesArm);
	
	u32 *palPtr = &gMonPaletteTablePtr;
	palPtr += myTempData->shiny_2;

	struct CompressedSpritePalette *monPaletteTable = (struct CompressedSpritePalette *)(palPtr[0]);
	struct CompressedSpritePalette *monPalette = monPaletteTable + myTempData->attackBuffer;

	if (!checkLZ(monPalette->data))
		monPalette = monPaletteTable;
		
	LZ77UnCompVram(monPalette->data,&OBJ_PaletteMem2[0x40]);
}

bool8 checkPicLZ(struct LZData *data){
	if(data->flag != 0x10 || data->size < 8*8 || data->size > 256*256){
		return FALSE;
	}
	return umodsi3(data->size,8) == 0;
}

bool8 checkLZ(struct LZData *data){
	if(data->flag != 0x10 || umodsi3(data->size,8) != 0){
		return FALSE;
	}
	return TRUE;
}

u32 getItemName(u16 itemId){
	struct Item *itemTable = (struct Item *)((u32*)gItemsPtr);
	struct Item *item = itemTable + itemId;

	if(itemId < ITEMS_COUNT){
		u8 flag = item->name[0];
		if(flag == 0x3D || flag == 0xAC || flag == 0xFF)
			return 1;
		
		return item->name;
	}
	else
		return 0;
}

void SetItembuffer(u8 index,u16 value){
	u16 *buffer = textBuffer->wordList;
	buffer[index] = value;
}

u16 GetItembuffer(u8 index){
	u16 *buffer = textBuffer->wordList;
	return buffer[index];
}

void MoveItemBuffer(u8 index){
	u16 *buffer = textBuffer->wordList;

	for (u32 i = 0; i < 7-index; i++){
		buffer[6-i] = buffer[6-i-index];
	}
}
void SortItemBuffer(u8 index){
	u16 *buffer = textBuffer->wordList;
	if (index == 2 || index == 3){
		u16 temp = buffer[0];
		buffer[0] = buffer[index-1];
		buffer[index-1] = temp;
	
	}
}



