#include "header/funcs.h"
#include "header/text.h"

extern void PrintText(u8 x, u8 y, u8 *str);
extern void BufferPos();
extern void SetMousePos(u16 x,u16 y);
extern bool8 IsPosChange();
extern void UpdateString(u8 x, u8 y, u8 *str,u16 len);
extern void PlaySound(u16 soundID);
extern void ClearStringRect(u8 windowId, u8 fillValue, u16 x, u16 y, u16 width, u16 height);
extern void ShowPlayerName();
extern void ShowMonName();
extern void UpdateSmallString(u8 pos_x, u8 pos_y, u8 *str,u16 len);
extern void PrintSmallText(u8 x, u8 y, u8 *str);
extern void UpdateCurrentPageText();
extern void changeMouseColor();
extern void SetText_MsgBox(u8 *str);

#ifdef FIRE_RED_LEAF_GREEN
#define KEYBOARD_BASE_X 0x12
#define KEYBOARD_BASE_Y 0x40
#define CHINESE_FONT_SPACE_H 18
#define ENGLISH_FONT_SPACE_H 18
#define FONT_SPACE_V 14
#else
#define KEYBOARD_BASE_X 0x1C
#define KEYBOARD_BASE_Y 0x40
#define CHINESE_FONT_SPACE_H 15
#define ENGLISH_FONT_SPACE_H 12
#define FONT_SPACE_V 16
#endif

/**
 * 输入文字模式时，更新键盘光标位置
*/
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
            x = KEYBOARD_BASE_X;
            y = KEYBOARD_BASE_Y + udivsi3(select,10)*FONT_SPACE_V;
            select = umodsi3(select,10);
            #ifdef FIRE_RED_LEAF_GREEN
            x += (CHINESE_FONT_SPACE_H*select);
            #else
            if(myTempData->fontType == FONT_CHINESE)
                x += (CHINESE_FONT_SPACE_H*select);
            else
                x += (ENGLISH_FONT_SPACE_H*select);
            #endif
        }
        break;
    }
    SetMousePos(x,y);
    if(IsPosChange())
        PlaySound(SOUND_SELECT);
}


void UpdateEnglishWordList(){
    struct font *ft = (struct font *)textBuffer->wordList;
	u8 b = myTempData->fontBit2;
	u8 i = 0;
	while (i<26) //26字母
	{
		ft->zi1 = 0;
		ft->zi2 = b;
		if(umodsi3(i+1,10) == 0)
			ft->fill = CHAR_NEWLINE;
		else
			ft->fill = CHAR_SPACE;
		ft ++;
		b ++;
		i ++;
	}
	
	i = 4;
	while (i)//26字母后4空格
	{
		ft->zi1 = 0;
		ft->zi2 = 0;
		if(i > 1)
			ft->fill = CHAR_SPACE;
		else
			ft->fill = CHAR_NEWLINE;
		ft ++;
		i --;
	}

	if(myTempData->fontType == FONT_UPPERCASE)
	{	
		
		i = 0;
		b = CHAR_0;
		while(i < 10){ //数字0-9
			ft->zi1 = 0;
			ft->zi2 = b;
			ft->fill = CHAR_SPACE;
			ft ++;
			b ++;
			i ++;
		}
		i = 10;
	}
    else
        i = 20;
		
	while (i)
	{
		ft->zi1 = 0;
		ft->zi2 = 0;
		ft->fill = CHAR_SPACE;
		ft ++;
		i --;
	}
	ft --;
	ft->fill = CHAR_EOS;
	
}

void UpdateChineseWordList(){
    struct font *ft = (struct font *)textBuffer->wordList;
	u8 a = myTempData->fontBit1;
	u8 b = myTempData->fontBit2;
	u8 i = 5;
	while (i)
	{
		u8 j = 1;
		while (j<=10)
		{
			ft->zi1 = a;
			ft->zi2 = b;
			if(umodsi3(j,10) == 0)
				ft->fill = CHAR_NEWLINE;
			else
				ft->fill = CHAR_SPACE;
			
			b ++;
			if(b==0xF7)
			{
				a++;
				if(a == 6)
					a = 7;
				if(a == 0x1B)
					a = 0x1C;
				b = 0;
			}
				
			j ++;
			ft ++;
		}
		
		i --;
	}
	ft--;
	ft->fill = 0xFF;

}

void UpdateFontPageFlag(){
	u8 *fontPage = myTempData->fontPage;
	fontPage[1] = 0xFF;
	u16 a = (myTempData->fontBit1<<8)+myTempData->fontBit2;
	u8 b = 0;
	u16 c = 0x100;
	while(1)
	{
		if(a<c){
			b = CHAR_0;
			break;
		}
		c+=0x24;
		if(a<c){
			b = CHAR_A;
			break;
		}
		c+=0xB8;
		if(a<c){
			b = CHAR_B;
			break;
		}
		c+=0xF2;
		if(a<c){
			b = 0xBD;//C
			break;
		}
		c+=0xC1;
		if(a<c){
			b = 0xBE;//D
			break;
		}
		c+=0x16;
		if(a<c){
			b = 0xBF;//E
			break;
		}
		c+=0x86;
		if(a<c){
			b = 0xC0;//F
			break;
		}
		c+=0x9B;
		if(a<c){
			b = 0xC1;//G
			break;
		}
		c+=0xBE;
		if(a<c){
			b = 0xC2;//H
			break;
		}
		c+=0x230;
		if(a<c){
			b = 0xC4;//J
			break;
		}
		c+=0x6D;
		if(a<c){
			b = 0xC5;//K
			break;
		}
		c+=0x101;
		if(a<c){
			b = 0xC6;//L
			break;
		}
		c+=0x97;
		if(a<c){
			b = 0xC7;//M
			break;
		}
		c+=0x5A;
		if(a<c){
			b = 0xC8;//N
			break;
		}
		c+=0x8;
		if(a<c){
			b = 0xC9;//O
			break;
		}
		c+=0x7A;
		if(a<c){
			b = 0xCA;//P
			break;
		}
		c+=0xA6;
		if(a<c){
			b = 0xCB;//Q
			break;
		}
		c+=0x3B;
		if(a<c){
			b = 0xCC;//R
			break;
		}
		c+=0x127;
		if(a<c){
			b = 0xCD;//S
			break;
		}
		c+=0xA5;
		if(a<c){
			b = 0xCE;//T
			break;
		}
		c+=0x78;
		if(a<c){
			b = 0xD1;//W
			break;
		}
		c+=0xE8;
		if(a<c){
			b = 0xD2;//X
			break;
		}
		c+=0x13B;
		if(a<c){
			b = 0xD3;//Y
			break;
		}
		c+=0x155;
		if(a<c){
			b = 0xD4;//Z
			break;
		}
		b = 0xB0;
		break;

	}
	fontPage[0] = b;
	#ifdef FIRE_RED_LEAF_GREEN
	UpdateString(216,48,&myTempData->fontPage,1);
    #elif RUBY_SAPPHIRE
    UpdateString(208,48,&myTempData->fontPage,1);
	#else
	UpdateString(210,48,&myTempData->fontPage,1);
	#endif
}

void ClearNewNameBuffer(){
	CpuFastFill(-1,textBuffer->newName,16);
}

void PrintUnderline(u32 cur, u32 length){
	length = length-cur;
	u8 *text_g = textBuffer->temp;
	while (cur)
	{
		text_g[0] = 0xB0;
		text_g++;
		cur--;
	}
	while (length)
	{
		text_g[0] = 0xAE;
		text_g++;
		length--;
	}
	text_g[0] = 0xFF;
    #ifdef RUBY_SAPPHIRE
    PrintText(40,24,textBuffer->temp);
    #else
	PrintText(46,24,textBuffer->temp);
    #endif
}

bool32 CheckCurrentFont(){
    u16 flag = myTempData->fontBit1*0x100+myTempData->fontBit2;
    return flag < 0x1E28;
}

void UpdateWordList(){
	if(myTempData->fontType > FONT_LOWERCASE)
        UpdateChineseWordList();
	else
		UpdateEnglishWordList();
	#ifdef FIRE_RED_LEAF_GREEN
	ClearStringRect(0,0,0,40,12*10+6*9,16*5);
	PrintText(0,40,textBuffer->wordList);
    #elif RUBY_SAPPHIRE
    ClearStringRect(0,0,0,40,16*10,16*5-8);
	PrintText(8,40,textBuffer->wordList);
	#else
	ClearStringRect(0,0,0,40,12*10+5*9,16*5);
	PrintText(10,40,textBuffer->wordList);
	#endif
	UpdateFontPageFlag();
}

void InitKeyboard(){
	myTempData->fontBit1 = 0;
	myTempData->fontBit2 = 0xBB;
	myTempData->pageLock = TRUE;
	myTempData->fontType = FONT_UPPERCASE;
	myTempData->inputCursorIndex = 0;

	ClearNewNameBuffer();

}

void UpdateKeyboardValue(){
	UpdateWordList();
	ClearStringRect(0,0,46,18,5*12,20);

	int name_len = 10;
	if(myTempData->page == PAGE_PLAYER_NAME)
	{
		name_len = 7;
		ShowPlayerName();
	}
	else{
		ShowMonName();
	}

	#ifdef FIRE_RED_LEAF_GREEN
	UpdateSmallString(144,0,text_table[TEXT_CIRCLE_DOT]+myTempData->pageLock*4,1);//[点]
	PrintSmallText(154,0,text_table[TEXT_PAGELOCK]);//锁定页面
    #elif RUBY_SAPPHIRE
    UpdateSmallString(128,0,text_table[TEXT_CIRCLE_DOT]+myTempData->pageLock*4,1);//[点]
	PrintSmallText(136,0,text_table[TEXT_PAGELOCK]);//锁定页面
	#else
	UpdateSmallString(148,0,text_table[TEXT_CIRCLE_DOT]+myTempData->pageLock*4,1);//[点]
	PrintSmallText(158,0,text_table[TEXT_PAGELOCK]);//锁定页面
	#endif
	PrintUnderline(myTempData->inputCursorIndex,name_len);//横线

    #ifdef RUBY_SAPPHIRE
    PrintText(40,16,textBuffer->newName);//新名字
    #else
    PrintText(46,18,textBuffer->newName);//新名字
    #endif
}

void KeyboardPreviousPage(){
	if(myTempData->fontType > FONT_LOWERCASE)
	{
		if(myTempData->fontBit1+myTempData->fontBit2 > 1)
		{
			if(myTempData->fontBit2<50)
			{
				if(myTempData->fontBit1>1){
					myTempData->fontBit1--;
					myTempData->fontBit2 = 0xC8;
					if(myTempData->fontBit1 == 6)
							myTempData->fontBit1 = 5;
					if(myTempData->fontBit1 == 0x1B)
						myTempData->fontBit1 = 0x1A;
				}
				else{
					myTempData->fontBit2 = 0;
				}
			}
			else
				myTempData->fontBit2 -= 50;
		}
		else
		{
			myTempData->fontType = FONT_LOWERCASE;
			myTempData->fontBit1 = 0;
			myTempData->fontBit2 = 0xD5;
		}
		
	}
	else if(myTempData->fontType == FONT_LOWERCASE)
	{
		myTempData->fontType = FONT_UPPERCASE;
		myTempData->fontBit2 = 0xBB;
	}
	UpdateWordList();
}

void KeyboardNextPage(){
	if(myTempData->fontType > FONT_LOWERCASE)
	{
		if(CheckCurrentFont()){
			myTempData->fontBit2 += 50;
			if(myTempData->fontBit2 >= 0xF7){
				myTempData->fontBit2 = 0;
				myTempData->fontBit1++;
				if(myTempData->fontBit1 == 6)
					myTempData->fontBit1 = 7;
				if(myTempData->fontBit1 == 0x1B)
					myTempData->fontBit1 = 0x1C;
			}
		}
	}
	else{
		myTempData->fontType++;
		if(myTempData->fontType == FONT_LOWERCASE)
			myTempData->fontBit2 = 0xD5;
		else{
			myTempData->fontBit1 = 1;
			myTempData->fontBit2 = 0;
		}
		
	}

	UpdateWordList();
}

void DeleteWord(){
	if(myTempData->inputCursorIndex)
	{
		u8 *text_nd = textBuffer->newName;
		u32 dm = 0;
		if(myTempData->inputCursorIndex > 1)
			dm = myTempData->inputCursorIndex-2;
		text_nd += dm;
		
		dm = 1;
		if(text_nd[0] > 0 && text_nd[0] < 0x20)
			dm = 2;
		
		if(myTempData->inputCursorIndex != 1)
			text_nd++;

		myTempData->inputCursorIndex -= dm;

		while (dm)
		{
			text_nd[0] = 0xFF;
			text_nd--;
			dm--;
		}
		
		PlaySound(SOUND_DELETE);
		UpdateCurrentPageText();
	}
}

void KeyboardButtonAEvent(){
	switch(myTempData->select){
		case 1:
			changeMouseColor();
			myTempData->cursorState = TRUE;
			SetText_MsgBox(text_table[TEXT_BUTTON_PROMPT4]+2);
			break;
		case 2:
			DeleteWord();
			break;
		default:{
			u32 m = 2;
			if(myTempData->fontType < FONT_CHINESE)
				m --;
			int name_len = 10;
			if(myTempData->page == PAGE_PLAYER_NAME)
				name_len = 7;
			if(myTempData->inputCursorIndex <= name_len-m)
			{
				struct font *wordList = (struct font *)textBuffer->wordList;
				wordList += (u8)(~myTempData->select);
				u8 *newName = (u8 *)textBuffer->newName;
				newName += myTempData->inputCursorIndex;
				
				myTempData->inputCursorIndex += m;

				if(m == 2){
					newName[0] = wordList->zi1;
					newName[1] = wordList->zi2;
				}
				else{
					newName[0] = wordList->zi2;
				}

				UpdateCurrentPageText();
			}
				
		}
		break;
	}

}

//通过首字母获取对应的字
void GetWordByFlag(u8 flag,u8* word){
	switch (flag)
	{
	case CHAR_0:
		word[0] = 0;
		word[1] = 0xBB;
		break;
	case CHAR_A:
		word[0] = 1;
		word[1] = 0;
		break;
	case CHAR_B:
		word[0] = 1;
		word[1] = 0x24;
		break;
	case CHAR_C:
		word[0] = 1;
		word[1] = 0xDC;
		break;
	case CHAR_D:
		word[0] = 2;
		word[1] = 0xCE;
		break;
	case CHAR_E:
		word[0] = 3;
		word[1] = 0x8F;
		break;
	case CHAR_F:
		word[0] = 3;
		word[1] = 0xA5;
		break;
	case CHAR_G:
		word[0] = 4;
		word[1] = 0x2B;
		break;
	case CHAR_H:
		word[0] = 4;
		word[1] = 0xC6;
		break;
	case CHAR_I:
	case CHAR_J:
		word[0] = 5;
		word[1] = 0x84;
		break;
	case CHAR_K:
		word[0] = 7;
		word[1] = 0xB4;
		break;
	case CHAR_L:
		word[0] = 8;
		word[1] = 0x21;
		break;
	case CHAR_M:
		word[0] = 9;
		word[1] = 0x22;
		break;
	case CHAR_N:
		word[0] = 9;
		word[1] = 0xB9;
		break;
	case CHAR_O:
		word[0] = 0xA;
		word[1] = 0x13;
		break;
	case CHAR_P:
		word[0] = 0xA;
		word[1] = 0x1B;
		break;
	case CHAR_Q:
		word[0] = 0xA;
		word[1] = 0x95;
		break;
	case CHAR_R:
		word[0] = 0xB;
		word[1] = 0x3B;
		break;
	case CHAR_S:
		word[0] = 0xB;
		word[1] = 0x76;
		break;
	case CHAR_T:
		word[0] = 0xC;
		word[1] = 0x9D;
		break;
	case CHAR_U:
	case CHAR_V:
	case CHAR_W:
		word[0] = 0xD;
		word[1] = 0x42;
		break;
	case CHAR_X:
		word[0] = 0xD;
		word[1] = 0xBA;
		break;
	case CHAR_Y:
		word[0] = 0xE;
		word[1] = 0xA2;
		break;
	case CHAR_Z:
		word[0] = 0xF;
		word[1] = 0xDD;
		break;
	case CHAR_ELLIPSIS:
		word[0] = 0x11;
		word[1] = 0x32;
		break;
	}
}

void KeyboardPreviousFlag(){
	u8 fontPageFlag = myTempData->fontPage[0];
	u8* word = (u8 *)&myTempData->fontBit1;
	switch (fontPageFlag)
	{
	case CHAR_A:
		myTempData->fontType = FONT_UPPERCASE;
		GetWordByFlag(CHAR_0,word);
		break;
	case CHAR_J:
		GetWordByFlag(CHAR_H,word);
		break;
	case CHAR_W:
		GetWordByFlag(CHAR_T,word);
		break;
	case CHAR_ELLIPSIS:
		GetWordByFlag(CHAR_Z,word);
		break;
	default:
		GetWordByFlag(fontPageFlag-1,word);
		break;
	}

	UpdateWordList();
}

void KeyboardNextFlag(){
	u8 fontPageFlag = myTempData->fontPage[0];
	myTempData->fontType = FONT_CHINESE;
	u8* word = (u8 *)&myTempData->fontBit1;
	switch (fontPageFlag)
	{
	case CHAR_0:
		GetWordByFlag(CHAR_A,word);
		break;
	case CHAR_Z:
		GetWordByFlag(CHAR_ELLIPSIS,word);
		break;
	default:
		GetWordByFlag(fontPageFlag+1,word);
		break;
	}

	UpdateWordList();
}