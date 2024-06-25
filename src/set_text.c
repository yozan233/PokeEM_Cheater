#include "header/data.h"

extern u32 GetPenWuMax();
extern struct Pokemon *getCurrentPlayerParty();
extern u32 getCurrentMonData(u8 request);
extern struct BaseStats* getSpeciesBaseStats(u16 species);
extern u8 *getMonSpeciesName(u16 species);
extern bool8 checkNameString(u8 *str,u32 length);
extern u8 *getItemName(u16 itemId);
extern void initMonTempData();
extern struct Sprite *getSprite(u8 id);
extern void loadRepelStepCount();
extern u8 *getItemNameValid(u16 itemId);
extern void InitKeyboard();
extern void SetText_MsgBox(u8 *str);
extern u8 *getBattleTextBuff(u8 type,u8 value);
extern void UpDateSelectedMousePos();
extern bool8 validAttackName(u16 attackNum);
extern bool8 validMonSpeciesNameValid(u16 species);
extern void UpdateKeyboardValue();
extern void restart(int i);
u8 getMapId(u16 mapGroup, u16 mapNum);
u8 *getPlayerNameOffset();
u16 get_ballNum(u8 index);
u16 getAttackNum(u8 n);
u8 getMoveAttr(u8 n);
u8 *getTypeName(u8 type);
u8 *getAttackName(u16 attackNum);
u32 getMonName(u16 monNum);
u8 *getAbilityName();
bool8 checkPicLZ(struct LZData *data);
bool8 checkLZ(struct LZData *data);
u16 GetItemListBuffer(u8 index);
void UpdatePageValue(u8 page);
u8 *GetAuthorText();
u8 *GetVersionText();
void UpdateString(u8 x, u8 y, u8 *str,u16 len);
void ClearStringRect(u16 x, u16 y, u16 width, u16 height);
void UpdateNumString(u8 pos_x, u8 pos_y, u32 num);
void UpdateNumHexString(u8 pos_x, u8 pos_y, u32 num);
void ClearStringForWidth(u16 pos_x, u16 pos_y, u16 width);
void LoadMonIVEV();
void PrintSmallText(u8 x, u8 y, u8 *str);
void UpdateSmallString(u8 pos_x, u8 pos_y, u8 *str,u16 len);
void PrintText(u8 x, u8 y, u8 *str);
void UpdateNumSmallString(u8 pos_x, u8 pos_y, u32 num);
void getBallCount();
void get_ball_addr();
void ShowMonName();
void ShowSprite(u8 id);
void HideSprite(u8 id);
void SetShowNickNameOnly(bool8 b);
void SetPageTxet(u8 page);
void getSelectAttackNum();
void set_poke_tile();
void SortItemBuffer(u8 index);
void MoveItemBuffer(u8 index,int length);
void SetItemListBuffer(u8 index,u16 value);
void loadSpecieData();
void UpdateNumber(u8 x, u8 y, u32 value,u16 len);
void setSureCancelText();

#ifndef RUBY_SAPPHIRE
void set_item_tile();
#endif

#ifdef RUBY_SAPPHIRE
#define CRC_AUTHOR_TEXT 0xF3D3
#define CRC_VERSION_TEXT 0x63C2

#define POS_04 0
#define POS_09 8
#define POS_10 8
#define POS_17 16
#define POS_18 16
#define POS_20_0 16
#define POS_20 24
#define POS_60 64
#define POS_26 24
#define POS_28 24
#define POS_30 32
#define POS_44 40
#define POS_70 64
#define POS_76 80
#define POS_84 88
#define POS_92 88
#define POS_102 96
#define POS_106 104
#define POS_108 104
#define POS_120_0 112
#define POS_124 128
#define POS_132 128
#define POS_148 152
#define POS_156 160
#define POS_172 176
#define POS_204 200
#define POS_164 168
#define POS_160 168
#define POS_168 176
#define POS_170 176
#define POS_180 176

#else
#define CRC_AUTHOR_TEXT 0x0710
#define CRC_VERSION_TEXT 0x3653

#define POS_04 4
#define POS_09 9
#define POS_10 10
#define POS_17 17
#define POS_18 18
#define POS_20_0 20
#define POS_20 20
#define POS_30 30
#define POS_60 60
#define POS_28 28
#define POS_26 26
#define POS_44 44
#define POS_70 70
#define POS_76 76
#define POS_84 84
#define POS_92 92
#define POS_102 102
#define POS_106 106
#define POS_108 108
#define POS_120_0 120
#define POS_124 124
#define POS_132 132
#define POS_148 148
#define POS_156 156
#define POS_172 172
#define POS_204 204
#define POS_160 160
#define POS_164 164
#define POS_168 168
#define POS_170 170
#define POS_180 180

#endif

#define POS_24 24
#define POS_48 48
#define POS_56 56
#define POS_176 176
#define POS_120 120
#define POS_104 104
#define POS_128 128
#define POS_136 136


/**
 * 更新页面数值
*/
void UpdatePageValue(u8 page)
{
	switch(page){
		case PAGE_POKE_INFO:{
            //等级
            UpdateNumber(POS_60, POS_28, myTempData->lvl, 3);

            //亲密度
            UpdateNumber(POS_168, POS_28, myTempData->happiness, 3);

            //性格
			u8 *naturesTable = text_table[TEXT_NATURES_TABLE];
            u8 *naturesStr = naturesTable+5*myTempData->nature;
			UpdateString(POS_60, POS_56, naturesStr, 5);

            //特性
            u8 *abilityName = getAbilityName();
			if(!abilityName){
                abilityName = text_table[TEXT_UNKNOWN_ABILITY]+6*myTempData->ability;
			}
			UpdateString(POS_60, POS_84, abilityName, 5);

            //闪光
			UpdateString(POS_160,POS_56,text_table[TEXT_NOTSHINY]+2*myTempData->shiny,3);

            //性别
			UpdateString(POS_160,POS_84,text_table[TEXT_GENDER_TABLE]+4*myTempData->sex,1);
		}return;
		case PAGE_POKE_INFO2:{
			#ifndef FIRE_RED_LEAF_GREEN
			ClearStringForWidth(POS_156,POS_56,12);
			ConvertIntToDecimalStringN(&myTempData->numTextBuff,myTempData->time,2,2);
			PrintText(POS_156,POS_56,&myTempData->numTextBuff);//时间
			#endif
			UpdateString(POS_76,POS_84,text_table[TEXT_CIRCLE_DOT]+(myTempData->monCopy)*4,1);
            #ifndef RUBY_SAPPHIRE
			UpdateString(POS_172,POS_84,text_table[TEXT_CIRCLE_DOT]+(myTempData->obedience)*4,1);
            #endif

			u8 *mapName = myTempData->textBuffer.wordList;
            if(myTempData->location == 0xFF){
                mapName = text_table[TEXT_FATEFUL_ENCOUNTER];
            } else{
                GetMapName(mapName,myTempData->location,0);
                u8 firstChar = mapName[0];
                if(firstChar == 0x0 || firstChar == 0xFF){
                    mapName = text_table[TEXT_SOMEWHERE];
                }
            }

			UpdateString(POS_164,POS_28,mapName,5);//捕获地

			if(myTempData->selectedBall == 0){
				UpdateString(POS_60,POS_28,text_table[TEXT_NONE],5);
				myTempData->itemBuffer = 0;
			}
			else{
				u16 ball = get_ballNum(myTempData->selectedBall-1);
				UpdateString(POS_60,POS_28,getItemName(ball),5);//球种
				myTempData->itemBuffer = ball;
			}
				
			//飞行点
			if(myTempData->selectedflightPoint == 0)
				UpdateString(POS_60,POS_56,text_table[TEXT_NONE],5);
			else{
				struct HealLocation *location = GetHealLocation(myTempData->selectedflightPoint);
				u16 m = getMapId(location->group, location->map);
                u8 *mapName2 = myTempData->textBuffer.wordList;
				GetMapName(mapName2,m,0);

				UpdateString(POS_60,POS_56,mapName2,5);

			}
			
		}return;
		case PAGE_IVS:
		case PAGE_EVS:
			if(myTempData->cursorState == FALSE || myTempData->select == 0)
				LoadMonIVEV();
			if(myTempData->page == PAGE_EVS){
                UpdateSmallString(32,104,text_table[TEXT_CIRCLE_DOT]+myTempData->limit510*4,1);//添加[点]
				PrintSmallText(40,104,text_table[TEXT_LIMIT510]);
			}
			
			UpdateNumString(POS_60,POS_28,myTempData->hp);//HP
			UpdateNumString(POS_60,POS_56,myTempData->attack);//物攻
			UpdateNumString(POS_60,POS_84,myTempData->defence);//物防
			UpdateNumString(POS_160,POS_28,myTempData->speed);//速度
			UpdateNumString(POS_160,POS_56,myTempData->SP_attack);//特攻
			UpdateNumString(POS_160,POS_84,myTempData->SP_defence);//特防
			return;
		case PAGE_MOVES:{
            u8 *textNone = text_table[TEXT_NONE];
			ClearStringRect(18,20,12*6,4*16);
			ClearStringRect(128,16,12*8,5*16+8);

			for(u8 i = 0;i <= 3;i++){
                u8 *nameStr;
				if(getAttackNum(i)) {
                    nameStr = getAttackName(getAttackNum(i));
                }else {
                    nameStr = textNone;
                }

                UpdateString(POS_18,POS_20+i*POS_18,nameStr,6);
			}
			
			u8 power = getMoveAttr(1);//威力
			if(power){
				UpdateNumSmallString(POS_44,POS_92,power);
			}
			else
				UpdateSmallString(POS_44,POS_92,textNone,3);

            u8 accuracy = getMoveAttr(3);//命中率
            if(accuracy){
                UpdateNumSmallString(POS_44,POS_106,accuracy);
            }
            else{
                UpdateSmallString(POS_44,POS_106,textNone,3);
            }

            #ifdef RUBY_SAPPHIRE
            PrintSmallText(POS_70,POS_92,text_table[TEXT_MOVE_TYPE]);//属性
		    PrintSmallText(POS_70,POS_106,text_table[TEXT_PP]);//PP
            setSureCancelText();
            #endif

            UpdateSmallString(POS_102,POS_92,getTypeName(getMoveAttr(2)),3);//属性
			UpdateNumSmallString(POS_102,POS_106,getMoveAttr(4));//PP

			u16 attNum = myTempData->attackBuffer;
			u32 a = 0;
			while(a < 2){
                attNum--;
				if(attNum == 0)
					break;
				a++;
			}
            attNum = myTempData->attackBuffer;
			u32 b = 0;
			while(b < 2){
                attNum++;
				if(!validAttackName(attNum))
					break;
				b++;
			}
			if(a+b<4){
				if(a<2)
					b=4-a;
				else
					a=4-b;
			}
            attNum = myTempData->attackBuffer;
			u32 n = 0;
			while (a){
				UpdateNumHexString(POS_136,n*POS_18+16,attNum-a);//技能编号
				PrintText(POS_156,n*POS_18+16,getAttackName(attNum-a));//前
				n++;
				a--;
			}
			PrintText(POS_128,n*POS_18+16,text_table[TEXT_CURSOR]);
			UpdateNumHexString(POS_136,n*POS_18+16,attNum);//技能编号
			PrintText(POS_156,n*POS_18+16,getAttackName(attNum));//中
			n++;
			u32 m = 1;
			while (m<=b){
				UpdateNumHexString(POS_136,n*POS_18+16,attNum+m);
				PrintText(POS_156,n*POS_18+16,getAttackName(attNum+m));//后
				m++;
				n++;
			}
		}return;
		case PAGE_SPECIE:{
			set_poke_tile();
			loadSpecieData();
			
			//显示6项种族值
			u8 *specieData = (u8 *)&myTempData->hp;
			for(int k = 0; k < 6; k++){
                #ifdef RUBY_SAPPHIRE
                UpdateNumSmallString(40,POS_28+k*16-8,specieData[k]);
                #else
				UpdateNumSmallString(42,28+k*14,specieData[k]);
                #endif
			}

			u32 a5 = 0;
			u16 pokeNum = myTempData->attackBuffer;


			ClearStringRect(128,16,12*8,5*16+8);
			
			while(a5 < 2){
                pokeNum--;
				if(pokeNum == 0)
					break;
				a5++;
			}
            pokeNum = myTempData->attackBuffer;
			u32 b5 = 0;
			while(b5 < 2){
                pokeNum++;
				if(!validMonSpeciesNameValid(pokeNum)) {
                    break;
                }
				b5++;
			}
			if(a5+b5<4){
				if(a5<2)
					b5=4-a5;
				else
					a5=4-b5;
			}

            pokeNum = myTempData->attackBuffer;
			u32 n5 = 0;
			while (a5){
				PrintText(POS_156,n5*POS_18+16,getMonSpeciesName(pokeNum-a5));//前
				n5++;
				a5--;
			}
			PrintText(POS_148,n5*POS_18+16,text_table[TEXT_CURSOR]);
			PrintText(POS_156,n5*POS_18+16,getMonSpeciesName(pokeNum));//中
			n5++;
			u32 m5 = 1;
			while (m5<=b5){
				PrintText(POS_156,n5*POS_18+16,getMonSpeciesName(pokeNum+m5));//后
				m5++;
				n5++;
			}

            #ifdef RUBY_SAPPHIRE
            UpdateNumHexString(88,104,pokeNum);//精灵编号
            setSureCancelText();
            #else
            UpdateNumHexString(94,98,pokeNum);//精灵编号
            #endif

		}return;
		case PAGE_POKE_NAME:
		case PAGE_PLAYER_NAME:
			UpdateKeyboardValue();
			return;
		case PAGE_ITEMS:{
			#ifndef RUBY_SAPPHIRE
			set_item_tile();
			#endif
			
			ClearStringRect(0,0,12*7+6*4,16*7+4);
			u16 curItem = myTempData->itemBuffer;

			//查找上半部分道具
			u32 topIndex=0,listIndex=0;
			while(topIndex < 3){ //0-2
				if(curItem==1)
					break;
				curItem--;
                u8 *itemName = getItemNameValid(curItem);
				if (itemName == ITEM_NAME_NONE)
					break;
				else if(itemName != ITEM_NAME_TEMP){
					SetItemListBuffer(listIndex,curItem);
					topIndex++;
					listIndex++;
				}
			}
			SortItemBuffer(topIndex);
			
			//当前道具
			SetItemListBuffer(listIndex,myTempData->itemBuffer);
			listIndex++;

			//查找下半部分道具
			u32 bottomIndex = 3;
			if(topIndex < 3)
				bottomIndex = 6-topIndex;
			curItem=myTempData->itemBuffer;
			while(bottomIndex){
				curItem++;
                u8 *itemName = getItemNameValid(curItem);
				if (itemName == ITEM_NAME_NONE)
					break;
				else if(itemName != ITEM_NAME_TEMP){
					SetItemListBuffer(listIndex,curItem);
					bottomIndex--;
					listIndex++;
				}
			}
			
			if(bottomIndex){
				MoveItemBuffer(bottomIndex,7);
				curItem = GetItemListBuffer(0);
				topIndex=0,listIndex=0;
				while(topIndex < bottomIndex){
					curItem--;
                    u8 *itemName = getItemNameValid(curItem);
					if (itemName == 0)
						break;
					else if(itemName != 1){
						SetItemListBuffer(listIndex,curItem);
						topIndex++;
						listIndex++;
					}
				}
				SortItemBuffer(topIndex);
			}
            u8 *text6t = &myTempData->numTextBuff;
			for(u8 k=0;k<7;k++){
				u16 Na = GetItemListBuffer(k);
				if(Na == myTempData->itemBuffer)
				{
					//文本光标
					PrintText(0,k*POS_17,text_table[TEXT_CURSOR]);
					SetItemListBuffer(ITEM_TEXT_CURSOR_INDEX,k);
				}
				PrintText(POS_30,k*POS_17,getItemName(Na));//道具名称
				ConvertIntToHexStringN(text6t,Na,2,3);
				PrintText(POS_09,k*POS_17,text6t);//道具编号
			}

            ConvertIntToDecimalStringN(&myTempData->numTextBuff,myTempData->Num,2,2);
            UpdateString(POS_156,POS_26,&myTempData->numTextBuff,2);//数值
            #ifdef RUBY_SAPPHIRE
            UpdateString(112,48,text_table[TEXT_CIRCLE_DOT]+ 4*myTempData->addItemEnable,1);//添加[点]
            UpdateString(112,72,text_table[TEXT_CIRCLE_DOT]+ 4*myTempData->throwKeyItemEnable,1);//扔掉一个重要道具[空心点]
            PrintText(120,48,text_table[TEXT_ADD_ITEM]);//添加
            PrintText(120,72,text_table[TEXT_THROW_KEYITEM]);//扔掉一个重要道具
            #else
            UpdateString(108,50,text_table[TEXT_CIRCLE_DOT]+ 4*myTempData->addItemEnable,1);//添加[点]
            UpdateString(108,70,text_table[TEXT_CIRCLE_DOT]+ 4*myTempData->throwKeyItemEnable,1);//扔掉一个重要道具[空心点]
            #endif
		}return;
		case PAGE_OTHER:{
			u8 numLength = 5;
			if(GetPenWuMax() == 255)
				numLength -= 2;
			ConvertIntToDecimalStringN(&myTempData->numTextBuff,myTempData->species,2,numLength);
			UpdateString(POS_156,POS_20_0,&myTempData->numTextBuff,4);
			UpdateString(POS_20_0,POS_20_0,text_table[TEXT_CIRCLE_DOT] + 4 * myTempData->pokedexUpgrade,1);
			UpdateString(POS_20_0,POS_48,text_table[TEXT_CIRCLE_DOT] + 4 * myTempData->pokerus,1);
			UpdateString(POS_20_0,POS_76,text_table[TEXT_CIRCLE_DOT] + 4 * myTempData->mirageShow,1);
			UpdateString(POS_120_0,POS_48,text_table[TEXT_CIRCLE_DOT] + 4 * myTempData->visualRangeMax,1);
			UpdateString(POS_120_0,POS_76,text_table[TEXT_CIRCLE_DOT] + 4 * myTempData->throughWall,1);
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
		#ifndef RUBY_SAPPHIRE
		HideSprite(mySav->itemPicId);
		#endif
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
            getSelectAttackNum();
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
		#ifndef RUBY_SAPPHIRE
		ShowSprite(mySav->itemPicId);
		CpuFastFill(0, (void *) itemTilesArm, 0x800);
		#endif
		break;
	case PAGE_OTHER:
		throughWallFlag[0] = FALSE;
		((u8 *)myTempData)[0x46] = 0;
		loadRepelStepCount();
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

void setSureCancelText(){
    PrintSmallText(POS_176,POS_104,text_table[TEXT_SURE]);//确认
    PrintSmallText(POS_204,POS_104,text_table[TEXT_CANCEL]);//取消
}

void SetPageTxet(u8 page){
	#ifdef RUBY_SAPPHIRE
    Menu_EraseWindowRect(0,0,0x1D,0xF);
	#else
	FillWindowPixelBuffer(0,0); //清空全部文本
	#endif
	if(page != PAGE_MAIN){
        setSureCancelText();
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
//	case PAGE_MAIN:
    default:
		PrintText(24,56,text_table[TEXT_MON]); //精灵
		PrintText(96,56,text_table[TEXT_BAG]); //背包
		PrintText(168,56,text_table[TEXT_OTHER]); //其它
		SetText_MsgBox(text_table[TEXT_BUTTON_PROMPT1]);//按键提示
		PrintSmallText(0,0,GetAuthorText());//作者
		PrintSmallText(176,0,GetVersionText());//版本号
		break;
	case PAGE_POKE_INFO:
		PrintText(POS_24, POS_28, text_table[TEXT_LEVEL]);	 //等级
		PrintText(POS_24, POS_56, text_table[TEXT_NATURES]);	 //性格
		PrintText(POS_24, POS_84, text_table[TEXT_ABILITY]);	 //特性
		PrintText(POS_124, POS_28, text_table[TEXT_HAPPINESS]); //亲密度
		PrintText(POS_124, POS_56, text_table[TEXT_SHINY]);	 //闪光
		PrintText(POS_124, POS_84, text_table[TEXT_GENDER]);	 //性别
		SetText_MsgBox(text_table[TEXT_BUTTON_PROMPT3]);
		break;
	case PAGE_POKE_INFO2:{
		PrintText(POS_24, POS_28, text_table[TEXT_BALL_TYPE]);//球种
		PrintText(POS_120,POS_28,text_table[TEXT_CATCH_LOCATION]);//捕获地
		PrintText(POS_24, POS_56, text_table[TEXT_TELEPORT]);//瞬移
		#ifdef FIRE_RED_LEAF_GREEN
		PrintText(120,POS_56,text_table[TEXT_COMING_SOON]);//敬请期待
		#else
		PrintText(POS_120, POS_56, text_table[TEXT_TIME]);//时间
		PrintText(POS_170, POS_56, text_table[TEXT_HOUR]);//时
		#endif
		PrintText(POS_24, POS_84, text_table[TEXT_MON_COPY]);//复制精灵

        #ifdef RUBY_SAPPHIRE
        PrintText(POS_120,POS_84,text_table[TEXT_COMING_SOON]);//敬请期待
        #else
		PrintText(POS_120,POS_84,text_table[TEXT_MON_OBEDIENCE]);//精灵听话
        #endif
	}break;
	case PAGE_IVS:
	case PAGE_EVS:{
		PrintText(POS_24,POS_28,text_table[TEXT_HP]);//HP
		PrintText(POS_24, POS_56, text_table[TEXT_ATTACK]);//物攻
		PrintText(POS_24, POS_84, text_table[TEXT_DEFENSE]);//物防
		PrintText(POS_124,POS_28,text_table[TEXT_SPEED]);//速度
		PrintText(POS_124, POS_56, text_table[TEXT_SP_ATTACK]);//特攻
		PrintText(POS_124,POS_84,text_table[TEXT_SP_DEFENSE]);//特防
        u8 *ivevTitle = text_table[TEXT_IV+(myTempData->page-PAGE_IVS)];
		PrintText(POS_180,0,ivevTitle);//个体/努力
	}break;
	case PAGE_POKE_NAME:
	case PAGE_PLAYER_NAME:{
		#ifdef FIRE_RED_LEAF_GREEN
		PrintSmallText(180,48,text_table[TEXT_INITIALS]);//首字母
		PrintSmallText(180,68,text_table[TEXT_DELETE]);//删除
        #elif RUBY_SAPPHIRE
        PrintSmallText(168,48,text_table[TEXT_INITIALS]);//首字母
		PrintSmallText(168,72,text_table[TEXT_DELETE]);//删除
		#else
		PrintSmallText(170,48,text_table[TEXT_INITIALS]);//首字母
		PrintSmallText(170,68,text_table[TEXT_DELETE]);//删除
		#endif
		}break;
	case PAGE_MOVES:
		PrintSmallText(POS_04,POS_92,text_table[TEXT_MOVE_POWER]);//威力
        PrintSmallText(POS_04,POS_106,text_table[TEXT_MOVE_ACCURACY]);//命中率
        #ifndef RUBY_SAPPHIRE
        PrintSmallText(POS_70,POS_92,text_table[TEXT_MOVE_TYPE]);//属性
		PrintSmallText(POS_70,POS_106,text_table[TEXT_PP]);//PP
        #endif
		break;
	case PAGE_SPECIE:
        #ifdef RUBY_SAPPHIRE
        PrintSmallText(8,POS_28+0*16-8,text_table[TEXT_HP]);//HP
		PrintSmallText(8,POS_28+1*16-8,text_table[TEXT_ATTACK]);//物攻
		PrintSmallText(8,POS_28+2*16-8,text_table[TEXT_DEFENSE]);//物防
		PrintSmallText(8,POS_28+3*16-8,text_table[TEXT_SPEED]);//速度
		PrintSmallText(8,POS_28+4*16-8,text_table[TEXT_SP_ATTACK]);//特攻
		PrintSmallText(8,POS_28+5*16-8,text_table[TEXT_SP_DEFENSE]);//特防
        #else
		PrintSmallText(10,POS_28+0*14,text_table[TEXT_HP]);//HP
		PrintSmallText(10,POS_28+1*14,text_table[TEXT_ATTACK]);//物攻
		PrintSmallText(10,POS_28+2*14,text_table[TEXT_DEFENSE]);//物防
		PrintSmallText(10,POS_28+3*14,text_table[TEXT_SPEED]);//速度
		PrintSmallText(10,POS_28+4*14,text_table[TEXT_SP_ATTACK]);//特攻
		PrintSmallText(10,POS_28+5*14,text_table[TEXT_SP_DEFENSE]);//特防
        #endif
		break;
	case PAGE_ITEMS:
        PrintText(120,POS_26,text_table[TEXT_QUANTITY]);//数量
        #ifndef RUBY_SAPPHIRE
		PrintText(120,50,text_table[TEXT_ADD_ITEM]);//添加
		PrintText(120,70,text_table[TEXT_THROW_KEYITEM]);//扔掉一个重要道具
        #endif
		SetText_MsgBox(text_table[TEXT_BUTTON_PROMPT2]);
		break;
	case PAGE_OTHER:
		PrintText(32,POS_20_0,text_table[TEXT_POKEDEX_UPGRADE]);//升级图鉴
		PrintText(32,POS_48,text_table[TEXT_POKERUS]);//精灵病毒
		#ifdef FIRE_RED_LEAF_GREEN
		PrintText(32,76,text_table[TEXT_COMING_SOON]);//敬请期待
		#else
		PrintText(32,POS_76,text_table[TEXT_MIRAGE_SHOW]);//出现幻岛
		#endif
		PrintText(120,POS_20_0,text_table[TEXT_SPRAY]);//喷雾
		PrintText(POS_132,POS_48,text_table[TEXT_VISUAL_RANGE_MAX]);//视野
		PrintText(POS_132,POS_76,text_table[TEXT_THROUGH_WALL]);//穿墙
		SetText_MsgBox(text_table[TEXT_BUTTON_PROMPT3]);
		break;
	}
}

void ShowMonName(){
	if (myTempData->egg)
	{
		UpdateString(POS_44, 0, text_table[TEXT_EGG], 12); //蛋
	}
	else
	{
		UpdateString(POS_44, 0, myTempData->textBuffer.monName, 12); //昵称/种族
	}
}

void ShowPlayerName(){
	UpdateString(POS_10,0,getPlayerNameOffset(),7); //玩家名
}

void SetShowNickNameOnly(bool8 b){
	u8 nickLength = myTempData->textBuffer.monName[0x1F];
    myTempData->textBuffer.monName[nickLength] = b?0xFF:0xBA;
}

u16 AnalysisText(const u8 *src, u8 *dest,u32 len){
	u32 i, j;
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

/**
 * 获取作者文本
 */
u8 *GetAuthorText(){
	u8* authorText = text_table[TEXT_AUTHOR];
	int len = 10;
	u16 authorCrc = AnalysisText(authorText,myTempData->textBuffer.temp,len);
	if(authorCrc != CRC_AUTHOR_TEXT){
        restart(1);
	}
	return myTempData->textBuffer.temp;
}

/**
 * 获取版本文本
 */
u8 *GetVersionText(){
	u8 *versionText = text_table[TEXT_VERSION];
	int len = 13;
	u16 versionCrc = AnalysisText(versionText,myTempData->textBuffer.temp,len);
	if(versionCrc != CRC_VERSION_TEXT){
        restart(1);
	}
	return myTempData->textBuffer.temp;
}

/**
 * 显示小字体文本
 */
void PrintSmallText(u8 x, u8 y, u8 *str){
	#ifndef RUBY_SAPPHIRE
    UpdateMainWindowsText(0,str,x,y);
	#else
    u8 *format = myTempData->textBuffer.format;
    format[0] = 0xFC;
    format[1] = 0x02;
    format[2] = 0x00;
    format[3] = 0xFC;
    format[4] = 0x06;
    format[5] = 0x04;
    StringCopy(&format[6],str);
    Menu_PrintTextPixelCoords(myTempData->textBuffer.format,x+8,y+8,0);
	#endif
}

/**
 * 显示文本
 */
void PrintText(u8 x, u8 y, u8 *str){
	#ifndef RUBY_SAPPHIRE
    UpdateMainWindowsText(1,str,x,y);
	#else
    u8 *format = myTempData->textBuffer.format;
    format[0] = 0xFC;
    format[1] = 0x02;
    format[2] = 0x00;
    StringCopy(&format[3],str);
    Menu_PrintTextPixelCoords(myTempData->textBuffer.format,x+8,y+8,0);
    #endif
}

/**
 * 更新文本
 */
void UpdateString(u8 x, u8 y, u8 *str,u16 len){
    int textWidth;
    #ifdef RUBY_SAPPHIRE
    textWidth = 10;
    #else
    textWidth = 12;
    #endif
	ClearStringForWidth(x,y,len*textWidth);
	PrintText(x,y,str);
}

/**
 * 更新数字
 */
void UpdateNumber(u8 x, u8 y, u32 value,u16 len){
    u8 *temp = &myTempData->numTextBuff;
    ConvertIntToDecimalStringN(temp,value,2,len);
    UpdateString(x, y, temp, len);//等级
}

void UpdateNumString(u8 pos_x, u8 pos_y, u32 num){
    u8 *numTextBuff = &myTempData->numTextBuff;
	ConvertIntToDecimalStringN(numTextBuff,num,2,3);
	UpdateString(pos_x,pos_y,numTextBuff,3);
}

void UpdateNumHexString(u8 pos_x, u8 pos_y, u32 num){
    u8 *numTextBuff = &myTempData->numTextBuff;
	ConvertIntToHexStringN(numTextBuff,num,2,3);
	UpdateString(pos_x,pos_y,numTextBuff,3);
}

/**
 * 更新小字体数字
*/
void UpdateNumSmallString(u8 pos_x, u8 pos_y, u32 num){
    u8 *numTextBuff = &myTempData->numTextBuff;
	ConvertIntToDecimalStringN(numTextBuff,num,2,3);
	UpdateSmallString(pos_x,pos_y,numTextBuff,3);
}

void UpdateSmallString(u8 pos_x, u8 pos_y, u8 *str,u16 len){
	ClearStringForWidth(pos_x,pos_y,8*len);
	PrintSmallText(pos_x,pos_y,str);
}

void ClearStringForWidth(u16 pos_x, u16 pos_y, u16 width){
	ClearStringRect(pos_x,pos_y,width,14);
}

void ClearStringRect(u16 x, u16 y, u16 width, u16 height){
	#ifdef RUBY_SAPPHIRE
    x = (x+8)/8;
    y = (y+8)/8;
    Menu_EraseWindowRect(x,y,width/8+x,height/8+y);
	#else
    FillMainWindowPixelRect(x,y,width,height);
	#endif
}

u8 getMapId(u16 mapGroup, u16 mapNum){
	struct MapHeader *header = (struct MapHeader*) GetMapHeaderByGroupAndId(mapGroup,mapNum);
	return header->regionMapSectionId;
}

u8 *getPlayerNameOffset(){
	#ifdef RUBY_SAPPHIRE
    return gSaveBlock2.playerName;
	#else
	return &gSaveBlock2Ptr->playerName;
	#endif
}

/**
 * 加载种族数据
*/
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
    #ifndef RUBY_SAPPHIRE
	u8 obedience = getCurrentMonData(ATTR_OBEDIENCE);
	myTempData->obedience = obedience;
	myTempData->obedienceTemp = obedience;
    #endif
	myTempData->selectedflightPoint = 0;
	myTempData->selectedBall = 0;
	myTempData->monCopy = FALSE;
	myTempData->selectedBall = 0;
	#ifndef FIRE_RED_LEAF_GREEN
	myTempData->time = gLocalTime.hours;
	#endif
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

void getSelectAttackNum(){
	u16 attack = getCurrentMonData(myTempData->attackSelect+ATTR_ATTACK_1);
	if (attack != 0){
		myTempData->attackBuffer = attack;
	}
	else
		myTempData->attackBuffer = 1;
}

u16 getAttackNum(u8 n){
	u8 request = ATTR_ATTACK_1+n;
	getCurrentMonData(request);
}


u8 *getAbilityName(){
	struct BaseStats* baseStats = getSpeciesBaseStats(myTempData->species);
	u8 abilitie = baseStats->abilities[myTempData->ability];

    u8 *abilityName = getBattleTextBuff(B_BUFF_ABILITY,abilitie);
	if (checkNameString(abilityName,gNameLengthConfig.abilityNameLength)){
		return abilityName;
	}
	
	return 0;
}

u8 *getTypeName(u8 type){
    u8 *typeNames = getBattleTextBuff(B_BUFF_TYPE,type);
	return typeNames;
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
	u32 battleMovespecies = gBattleMovesPtr[0];
	battleMovespecies += myTempData->attackBuffer*MOVE_DATA_SIZE;
	u8 attr = ((u8 *)battleMovespecies)[n];
	return attr;
}

#ifndef RUBY_SAPPHIRE
void set_item_tile(){
	struct ItemIcon *itemIconTableBase = (struct ItemIcon *)gItemIconTablePtr;
	struct ItemIcon *itemIcon = itemIconTableBase + myTempData->itemBuffer;
	
	if(!checkPicLZ(itemIcon->tiles))
		itemIcon = itemIconTableBase;
	
	LZ77UnCompVram(itemIcon->tiles, (void *) (itemTilesArm + 0x400));
	CopyItemIconPicTo4x4Buffer((void *) (itemTilesArm + 0x400), (void *) itemTilesArm);

	if(!checkLZ(itemIcon->pal))
		itemIcon = itemIconTableBase;
	LZ77UnCompVram(itemIcon->pal,GetOBJPaletteMem2(0x40));
}
#endif

void set_poke_tile(){
	struct CompressedSpriteSheet *monFrontPicTable = (struct CompressedSpriteSheet *)(gMonFrontPicTablePtr);
	struct CompressedSpriteSheet *monFrontPic = monFrontPicTable + myTempData->attackBuffer;
	if(!checkPicLZ(monFrontPic->data))
		monFrontPic = monFrontPicTable;
	
	LZ77UnCompVram(monFrontPic->data, (void *) monTilesArm);
	
	u32 *palPtr = &gMonPaletteTablePtr;
	palPtr += myTempData->shiny_2;

	struct CompressedSpritePalette *monPaletteTable = (struct CompressedSpritePalette *)(palPtr[0]);
	struct CompressedSpritePalette *monPalette = monPaletteTable + myTempData->attackBuffer;

	if (!checkLZ(monPalette->data))
		monPalette = monPaletteTable;
		
	LZ77UnCompVram(monPalette->data,GetOBJPaletteMem2(0x40));
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

/**
 * 设置道具列表缓存
 * @param index 索引
 * @param value 道具编号
*/
void SetItemListBuffer(u8 index,u16 value){
    myTempData->textBuffer.wordList[index] = value;
}

/*
* 获取道具列表缓存
* @param index 索引
*/
u16 GetItemListBuffer(u8 index){
	return myTempData->textBuffer.wordList[index];
}

/**
 * 将从index开始的元素移动到length-1文字
*/
void MoveItemBuffer(u8 index,int length){
	u16 *buffer = myTempData->textBuffer.wordList;
	for (u32 i = 0; i < length-index; i++){
		buffer[length-1-i] = buffer[length-1-i-index];
	}
}

/**
 * 将0~index-1的元素逆序
*/
void SortItemBuffer(u8 index){
	if(index < 2)
		return;
	u16 *buffer = myTempData->textBuffer.wordList;
	for(u8 i = 0;i < index/2;i++){
		u16 temp = buffer[i];
		buffer[i] = buffer[index-1-i];
		buffer[index-1-i] = temp;
	}
}
