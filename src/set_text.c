#include "header/funcs.h"
extern u32 check_802();
// extern void set_zi();
extern u32 check_pw();
extern struct Pokemon *getCurrentPartyplayer();
extern u32 getCurrentMonData(u8 request);
extern struct BaseStats* getSpeciesBaseStats(u16 species);
extern u32 getMonSpeciesName(u16 species);
u8 getMapId(u16 mapGroup, u16 mapNum);
u32 getPlayerNameOffset();
u16 get_ballNum(u8 index);
u16 get_attackN0(u8 n);
u8 getMoveAttr(u8 n);
u32 get_type_name(u8 type);
bool8 checkString(u8 *str,u32 length);
u32 getAttackName(u16 atackNum);
u32 getAbilityName();
bool8 checkPicLZ(struct LZData *data);
bool8 checkLZ(struct LZData *data);
u32 getItemName(u16 itemId);
u8 checkString2(u8 *str,u32 length);
u16 getbuffer(u8 index);

void set_text(u8 page)
{
	switch(page){
		case PAGE_MAIN:
			FillWindowPixelBuffer(0,0);
			print_text(24,56,text_table+0x15);
			print_text(96,56,text_table+0x1A);
			print_text(168,56,text_table+0x1F);
			print_text0(0,0,text_table+0x1C9);//作者
			print_text0(176,0,text_table+0x1D3);//版本号
			return;
		case PAGE_POKE_INFO:
			// print_public_text();
			if (myTempData->egg)
			{
				print_text(80,56,text_table+0x1E3);
			}
			else
			{
				
				if(myTempData->over == 0)
					refreshMonTempData();
				u32 temp = 0x02021EC8;
				ConvertUIntToDecimalStringN(temp,myTempData->lvl,2,3);
				update_string(60,28,temp,3);//等级s
				ConvertUIntToDecimalStringN(temp,myTempData->happiness,2,3);
				update_string(168,28,temp,3);//亲密度s
				temp = text_table+0x77+5*myTempData->nature;
				update_string(60,56,temp,5);//性格s
				temp = getAbilityName();
				if(!temp){
					temp = text_table+0x6B+6*myTempData->ability;
				}
				update_string(60,84,temp,5);//特性s
				temp = text_table+0xF4+2*myTempData->shiny;
				update_string(160,56,temp,3);//闪光s
				temp = text_table+0xFB+4*myTempData->sex;
				update_string(160,84,temp,1);//性别s
			}
			return;
		case PAGE_POKE_INFO2:{
			// print_public_text();
			
			ConvertUIntToDecimalStringN(&myTempData->numTextBuff,myTempData->SP_attack,2,2);
			clear_string_w(156,56,12);
			print_text(156,56,&myTempData->numTextBuff);//时间s

			update_string(76,84,text_table+0x1B0-(myTempData->SP_defence)*3,1);

			update_string(172,84,text_table+0x1B0-(myTempData->ability)*3,1);
			u32 mapName = 0x02021DE4;
			if(myTempData->hp <= 0xD4)
				GetMapName(mapName,myTempData->hp,0);
			else if (myTempData->hp == 0xFF)
				mapName = text_table+0x26E;
			else
				mapName = text_table+0x269;
			
			update_string(164,28,mapName,5);//捕获地s
			if(myTempData->attackBuffer == 0)
				update_string(60,28,text_table+0x189,5);
			else
				update_string(60,28,getItemName(myTempData->attackBuffer),5);//球种s
			//飞行点
			if(myTempData->speed == 0)
				update_string(60,56,text_table+0x189,5);
			else{
				/* print_text(60,56,text_table+0x279);
				u32 fly_txt = 0x02021EC8;
				ConvertUIntToDecimalStringN(fly_txt,myTempData->speed,2,2);
				print_text(98,56,fly_txt); */
				struct fly **fly_p = (struct fly **)0x08122C80;
				(*fly_p) += (myTempData->speed-1);
				u16 m = getMapId((*fly_p)->bank, (*fly_p)->map);
				GetMapName(mapName+0x20,m,0);
				update_string(60,56,mapName+0x20,5);
			}
			
		}return;
		case PAGE_IVS:
			//return;
		case PAGE_EVS:
			//FillWindowPixelBuffer(0,0);
			// print_public_text();
			if (myTempData->egg)
			{
				print_text(80,56,text_table+0x1E3);
			}
			else
			{
				
				if(myTempData->over == 0 || myTempData->select == 0)
					setattr();
				if(myTempData->page == 0x13){
					print_text0(40,104,text_table+0x221);
					update_string0(32,104,text_table+0x1B0-myTempData->sex*3,1);//添加[点]
				}
					
				u32 text2 = 0x02021EC8;
				ConvertUIntToDecimalStringN(text2,myTempData->hp,2,3);
				update_string(60,28,text2,3);//HPs
				ConvertUIntToDecimalStringN(text2,myTempData->attack,2,3);
				update_string(60,56,text2,3);//物攻s
				ConvertUIntToDecimalStringN(text2,myTempData->defence,2,3);
				update_string(60,84,text2,3);//物防s
				ConvertUIntToDecimalStringN(text2,myTempData->speed,2,3);
				update_string(160,28,text2,3);//速度s
				ConvertUIntToDecimalStringN(text2,myTempData->SP_attack,2,3);
				update_string(160,56,text2,3);//特攻s
				ConvertUIntToDecimalStringN(text2,myTempData->SP_defence,2,3);
				update_string(160,84,text2,3);//特防s
			}
			return;
		case PAGE_MOVES:{
			//FillWindowPixelBuffer(0,0);
			// print_public_text();
			u32 text4 = text_table+0x170+0x19;
			// text4 += 0x19;//text4='---'

			FillWindowPixelRect(0,0,18,20,12*6,4*16);
			FillWindowPixelRect(0,0,128,16,12*8,5*16+8);

			for(u8 i = 0;i <= 3;i++){
				if(get_attackN0(i))
					update_string(18,20+i*18,getAttackName(get_attackN0(i)),6);
				else
					update_string(18,20+i*18,text4,6);
			}
			
			u32 text4t = 0x02021EC8;
			if(getMoveAttr(1)>1){
				ConvertUIntToDecimalStringN(text4t,getMoveAttr(1),2,3);
				update_string0(44,92,text4t,3);//威力s
			}
			else
				update_string0(44,92,text4,3);//威力s
			update_string0(102,92,get_type_name(getMoveAttr(2)),3);//属性s
			if(getMoveAttr(3)>1){
				ConvertUIntToDecimalStringN(text4t,getMoveAttr(3),2,3);
				update_string0(44,106,text4t,3);//命中率s
			}
			else{
				update_string0(44,106,text4,3);//命中率s
			}
			ConvertUIntToDecimalStringN(text4t,getMoveAttr(4),2,3);
			update_string0(102,106,text4t,3);//PP
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
				print_text(156,n*18+16,getAttackName(attN-a));//前
				ConvertIntToHexStringN(text4t,attN-a,2,3);
				print_text(136,n*18+16,text4t);//技能编号
				n++;
				a--;
			}
			myTempData->attackN = 0xFFEF;
			print_text(128,n*18+16,&myTempData->attackN);
			print_text(156,n*18+16,getAttackName(attN));//中
			ConvertIntToHexStringN(text4t,attN,2,3);
			print_text(136,n*18+16,text4t);//技能编号
			n++;
			u32 m = 1;
			while (m<=b){
				print_text(156,n*18+16,getAttackName(attN+m));//后
				ConvertIntToHexStringN(text4t,attN+m,2,3);
				print_text(136,n*18+16,text4t);//技能编号
				m++;
				n++;
			}
		}return;
		case PAGE_SPECIE:{
			set_poke_tile();
			showSprite(myTempData->poke_pic_id);
			// showpokepic(0);
			// print_public_text();
			loadSpecieData();
				
			u32 text5 = &myTempData->numTextBuff;
			u8 *Gh = (u8 *)&myTempData->hp;
			for(int k = 0; k < 6; k++){
				ConvertUIntToDecimalStringN(text5,Gh[0],2,3);
				update_string0(42,28+k*14,text5,3);//HPs
				Gh++;
			}

			u32 a5 = 0;
			u16 pokeN;
			pokeN = myTempData->attackBuffer;

			ConvertIntToHexStringN(text5,pokeN,2,3);
			update_string(94,98,text5,3);//精灵编号

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
				u16 pmax = gPokeMax;
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
			//getMonSpeciesName(species)
			pokeN = myTempData->attackBuffer;
			u32 n5 = 0;
			while (a5){
				print_text(156,n5*18+16,getMonSpeciesName(pokeN-a5));//前
				n5++;
				a5--;
			}
			myTempData->attackN = 0xFFEF;
			print_text(148,n5*18+16,&myTempData->attackN);
			print_text(156,n5*18+16,getMonSpeciesName(pokeN));//中
			n5++;
			u32 m5 = 1;
			while (m5<=b5){
				print_text(156,n5*18+16,getMonSpeciesName(pokeN+m5));//后
				m5++;
				n5++;
			}
		}return;
		case PAGE_POKE_NAME:
			shuru();
			return;
		case PAGE_ITEMS:{
			set_item_tile();
			showSprite(myTempData->item_pic_id);
			// showitempic(0);
			// print_public_text();
			u32 text6 = text_table+0x180;
			ConvertUIntToDecimalStringN(0x02021EC8,myTempData->Num,2,2);
			update_string(156,26,0x02021EC8,2);//数值
			update_string(108,50,text6+0x30-3 * myTempData->hp,1);//添加[点]
			update_string(108,70,text6+0x30-3 * myTempData->attack,1);//扔掉一个重要道具[空心点]
			
			FillWindowPixelRect(0,0,0,0,12*7+6*4,16*7+4);
			// myTempData->attackBuffer = 5;
			u16 S=myTempData->attackBuffer;
			u32 a6=0,i6=0;
			while(a6 < 3){
				if(S==1)
					break;
				S--;
				u32 itemN = getItemName(S);
				if (itemN == 0)
					break;
				else if(itemN != 1){
						setbuffer(i6,S);
						a6++;
						i6++;
					}
			}
			sortA(a6);
			
			setbuffer(i6,myTempData->attackBuffer);
			i6++;

			u32 b6 = 3;
			if(a6 < 3)
				b6 = 6-a6;
			S=myTempData->attackBuffer;
			while(b6){
				S++;
				u32 itemN = getItemName(S);
				if (itemN == 0)
					break;
				else if(itemN != 1){
						setbuffer(i6,S);
						b6--;
						i6++;
					}
			}
			
			if(b6){
				bufferMove(b6);
				S = getbuffer(0);
				a6=0,i6=0;
				while(a6 < b6){
					S--;
					u32 itemN = getItemName(S);
					if (itemN == 0)
						break;
					else if(itemN != 1){
							setbuffer(i6,S);
							a6++;
							i6++;
						}
				}
				sortA(a6);
			}
			u32 text6t = &myTempData->numTextBuff;
			for(u8 k=0;k<7;k++){
				u16 Na = getbuffer(k);
				if(Na == myTempData->attackBuffer)
				{
					myTempData->attackN = 0xFFEF;
					print_text(0,k*17,&myTempData->attackN);
					setbuffer(7,k);
				}
				print_text(30,k*17,getItemName(Na));//道具名称
				ConvertIntToHexStringN(text6t,Na,2,3);
				print_text(9,k*17,text6t);//道具编号
			}
		}return;
		case PAGE_OTHER:{
			// print_public_text();
			u32 p_text = text_table+0x1B0;

			update_string(20,20,p_text-3 * myTempData->hp,1);
			update_string(20,48,p_text-3 * myTempData->defence,1);
			update_string(20,76,p_text-3 * myTempData->SP_attack,1);
			// print_text(120,20,p_text-3 * myTempData->attack);[点]
			u32 text7 = 0x02021EC8;
			u8 mx = 5;
			if(check_pw()==0xFF)
				mx-=2;
			ConvertUIntToDecimalStringN(text7,myTempData->species,2,mx);
			update_string(156,20,text7,4);
			update_string(120,48,p_text-3 * myTempData->speed,1);
			update_string(120,76,p_text-3 * myTempData->SP_defence,1);
		}return;
		case PAGE_PLAYER_NAME:
			shuru();
		default:
			return;
	}
	
}

void shuru(){
	if(myTempData->defence > 1)
		set_zi();
	else
		set_zi0();
	
	FillWindowPixelRect(0,0,46,14,5*12,20);
	FillWindowPixelRect(0,0,0,40,12*10+5*9,16*5);

	print_text(46,14,0x02021DD4);//名字
	int name_len = 10;
	if(myTempData->page == 0x31)
	{
		name_len = 7;
		print_text(10,0,getPlayerNameOffset());//玩家
	}
		
	print_text_000(myTempData->speed,name_len);//横线 print_text(46,20,0x02021DE4);
	
	print_text(10,40,0x02021DF4);

	update_string0(148,0,text_table+0x1B0-myTempData->sex*3,1);//[点]

	getset_start_A();
	update_string(210,48,&myTempData->attackN,1);
	
}

void select_page(){
	u8 mode = myTempData->page;
	if (mode > 0)
	{
		FillWindowPixelBuffer(0,0);
		u32 t = text_table+0x20;
		print_text0(176,104,t+0x41);//确认
		print_text0(204,104,t+0x46);//取消
		if(myTempData->page > 0 && myTempData->page < 0x16){
			if(myTempData->egg){
				print_text(44,0,text_table+0x1E0);//蛋
			}
			else{
				print_text(44,0,0x02021DC4);//昵称/种族
			}
		}

		if (mode == PAGE_POKE_NAME || mode == PAGE_PLAYER_NAME)
		{
			print_text0(158,0,text_table+0x230);//锁定页面
			print_text0(170,48,text_table+0x23C);//首字母
			print_text0(170,68,text_table+0x244);//删除
		}

		switch (mode)
		{
			case PAGE_POKE_INFO:{
				u32 text = text_table+0x20;
				print_text(24,28,text+0x1B);//等级
				print_text(24,56,text+0x21);//性格
				print_text(24,84,text+0x27);//特性
				print_text(124,28,text+0x2D);//亲密度
				print_text(124,56,text+0x35);//闪光
				print_text(124,84,text+0x3B);//性别
			}break;
			case PAGE_POKE_INFO2:{
				u32 text = text_table+0x200;
				print_text(24,28,text+0x4C);//球种
				print_text(120,28,text+0x52);//捕获地
				print_text(24,56,text+0x5A);//瞬移
				print_text(120,56,text+0x80);//时间
				print_text(170,56,text+0x86);//时
				print_text(24,84,text+0x89);//复制精灵
				print_text(120,84,text+0xB2);//精灵听话
			}break;
			case PAGE_IVS:
			case PAGE_EVS:{
				u32 text2 = text_table+0x100;
				print_text(30,28,text2+0xE);//HP
				print_text(24,56,text2+0x12);//物攻
				print_text(24,84,text2+0x18);//物防
				print_text(124,28,text2+0x1E);//速度
				print_text(124,56,text2+0x24);//特攻
				print_text(124,84,text2+0x2A);//特防
				text2 = text2+0x30+7*(myTempData->page-0x12);//2-2||3-2
				print_text(180,0,text2);//个体/努力
			}break;
			case PAGE_MOVES:{
				u32 text4 = text_table+0x170;
				print_text0(04,92,text4+1);
				print_text0(70,92,text4+7);
				print_text0(04,106,text4+0xD);
				print_text0(70,106,text4+0x15);
			}break;
			case PAGE_SPECIE:{
				u32 text5 = text_table+0x100;
				print_text0(14,28+0*14,text5+0xE);//HP
				print_text0(10,28+1*14,text5+0x12);//物攻
				print_text0(10,28+2*14,text5+0x18);//物防
				print_text0(10,28+3*14,text5+0x1E);//速度
				print_text0(10,28+4*14,text5+0x24);//特攻
				print_text0(10,28+5*14,text5+0x2A);//特防
			}break;
			case PAGE_ITEMS:{
				u32 text6 = text_table+0x180;
				print_text(120,50,text6+0x13);//添加
				print_text(120,26,text6+0xD);//数量
				print_text(120,70,text6+0x1C);//扔掉一个重要道具
			}break;
			case PAGE_OTHER:{
				u32 p_text = text_table+0x1E0;
				print_text(32,20,p_text+0xE);//升级图鉴
				print_text(32,48,p_text+0x17);//精灵病毒 
				print_text(32,76,p_text+0x20);//出现幻岛 
				print_text(120,20,p_text+0x3B);//喷雾
				print_text(132,48,p_text+0x32);//视野
				print_text(132,76,p_text+0x29);//穿墙
			}break;
			default:
				break;
		}
	}
	
	
}
void set_zi(){
	struct font *ft = (struct font *)0x02021DF4;
	u8 a = myTempData->hp,b = myTempData->attack;
	u8 i = 5;
	while (i)
	{
		u8 j = 1;
		while (j<=10)
		{
			ft->zi1 = a;
			ft->zi2 = b;
			if(umodsi3(j,10))
				ft->fill = 0x0;
			else
				ft->fill = 0xFE;
			
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
void set_zi0(){
	struct font *ft = (struct font *)0x02021DF4;
	u8 b = myTempData->attack;
	u8 i = 0;
	while (i<26)
	{
		ft->zi1 = 0;
		ft->zi2 = b;
		if(umodsi3(i+1,10))
			ft->fill = 0x0;
		else
			ft->fill = 0xFE;
		ft ++;
		b ++;
		i ++;
	}
	// ft--;
	// ft->fill = 0xFF;
	i = 4;
	while (i)
	{
		ft->zi1 = 0;
		ft->zi2 = 0;
		if(i > 1)
			ft->fill = 0x0;
		else
			ft->fill = 0xFE;
		ft ++;
		i --;
	}

	if(myTempData->defence == 0)
	{	
		
		i = 0;
		b = 0xA1;
		while(i<10){
			ft->zi1 = 0;
			ft->zi2 = b;
			ft->fill = 0x0;
			ft ++;
			b ++;
			i ++;
		}
		
	}

	if(myTempData->defence == 0)
		i = 10;
	else
		i = 20;
	while (i)
	{
		ft->zi1 = 0;
		ft->zi2 = 0;
		ft->fill = 0x0;
		ft ++;
		i --;
	}
	ft --;
	ft->fill = 0xFF;
	

}
void getset_start_A(){
	u8 *Aa = (u8 *)&myTempData->attackN;
	Aa ++;
	Aa[0] = 0xFF;
	Aa --;
	u16 a = myTempData->hp*0x100+myTempData->attack;
	u8 b = 0;
	u16 c = 0x100;
	while(1)
	{
		if(a<c){
			b = 0xA1;//0
			break;
		}
		c+=0x24;
		if(a<c){
			b = 0xBB;//A
			break;
		}
		c+=0xB8;
		if(a<c){
			b = 0xBC;//B
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
	
	
	Aa[0] = b;

}

void print_text_000(u32 a, u32 b){
	
	b = b-a;
	u8 *text_g = (u8 *)0x02021DE4;
	while (a)
	{
		text_g[0] = 0xB0;
		text_g++;
		a--;
	}
	while (b)
	{
		text_g[0] = 0xAE;
		text_g++;
		b--;
	}
	text_g[0] = 0xFF;
	print_text(46,20,0x02021DE4);

}

void print_text0(u8 pos_x, u8 pos_y, u8 *str){
	AddTextPrinterParameterized3(0,0,pos_x,pos_y,0x80CCCD4,0,str);
}

void print_text(u8 pos_x, u8 pos_y, u8 *str){
	AddTextPrinterParameterized3(0,1,pos_x,pos_y,0x80CCCD4,0,str);
}

void update_string(u8 pos_x, u8 pos_y, u8 *str,u16 len){
	clear_string_w(pos_x,pos_y,len*12);
	print_text(pos_x,pos_y,str);
}
void update_string0(u8 pos_x, u8 pos_y, u8 *str,u16 len){
	clear_string_w(pos_x,pos_y,8*len);
	print_text0(pos_x,pos_y,str);
}

void clear_string_w(u16 pos_x, u16 pos_y, u16 width){
	FillWindowPixelRect(0,0,pos_x,pos_y,width,14);
}

u8 getMapId(u16 mapGroup, u16 mapNum){
	struct MapHeader *header = (struct MapHeader*) GetMapHeaderByGroupAndId(mapGroup,mapNum);
	return header->regionMapSectionId;
}

u32 getPlayerNameOffset(){
	struct SaveBlock2 *sav2 = (struct SaveBlock2*)((u32*)gSaveBlock2Ptr)[0];
	return &sav2->playerName;
}

void loadSpecieData(){
	struct BaseStats* baseStats = getSpeciesBaseStats(myTempData->attackBuffer);  //这里attackBuffer用来暂存种族编号
	CpuSet(baseStats,&myTempData->hp,3);
}

void get_ball_addr(){
    u8 location = getCurrentMonData(ATTR_CATCH_LOCATION);
	myTempData->hp = location;
	u8 obedience = getCurrentMonData(ATTR_OBEDIENCE);
	myTempData->ability = obedience;
	u8 flightPointCount = ((u8*)gFlightPointCount)[0];
	myTempData->sex = flightPointCount;
	myTempData->defence = 0;
	myTempData->attackBuffer = 0;
	get_ballNum(0);
}

u16 get_ballNum(u8 index){
	struct BagPocket *ballsPocket = (struct BagPocket*)gBagPockets;
	ballsPocket += BALLS_POCKET;
	u16 n = 0;
	while (n < ballsPocket->capacity){
		if (ballsPocket->itemSlots[n].itemId == 0)
			break;
		n++;
	}
	myTempData->attackN = n;
	if(n != 0){
		return ballsPocket->itemSlots[index].itemId;
	}
	else
		return 0;
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

u32 getAttackName(u16 atackNum){
	u32 moveNames = ((u32*)gMoveNames_Pointer)[0];
	moveNames += (atackNum*13);
	u8 *name = (u8 *)moveNames;
	if(name[0] == 0xAE){
		return gText_ThreeDashes;
	}
	if(checkString(name,13)){
		return name;
	}
	else{
		return 0;
	}
}
u32 getAbilityName(){
	struct BaseStats* baseStats = getSpeciesBaseStats(myTempData->species);
	u8 abilitie = baseStats->abilities[myTempData->ability];
	u32 abilityName = ((u32*)gAbilityNames_Pointer)[0];
	abilityName += (0xD*abilitie);
	if (checkString(abilityName,0xC)){
		return abilityName;
	}
	else{
		u32 qhAbilityName = qhAbilityNames+0xD*(abilitie-0x4E);
		if (checkString(qhAbilityName,0xC)){
			return qhAbilityName;
		}

	}
	
	return 0;
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

void setattr(){
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
	u32 battleMovespecies = ((u32*)gBattleMoves_Pointer)[0];
	battleMovespecies += myTempData->attackBuffer*0xC;
	u8 attr = ((u8 *)battleMovespecies)[n];
	return attr;
}

u32 get_type_name(u8 type){
	u32 typeNames = ((u32*)gTypeNames_Pointer)[0];
	return typeNames + (type*7);
}

void set_item_tile(){
	struct ItemIcon *itemIconTableBase = (struct ItemIcon *)((u32*)gItemIconTable_Pointer)[0];
	struct ItemIcon *itemIcon = itemIconTableBase + myTempData->attackBuffer;
	
	if(!checkPicLZ(itemIcon->tiles))
		itemIcon = itemIconTableBase;
	
	LZ77UnCompVram(itemIcon->tiles,itemTilesArm+0x400);
	CopyItemIconPicTo4x4Buffer(itemTilesArm+0x400,itemTilesArm);

	if(!checkLZ(itemIcon->pal))
		itemIcon = itemIconTableBase;
	LZ77UnCompVram(itemIcon->pal,OBJ_PaletteMem2+0x80);
}

void set_poke_tile(){
	struct CompressedSpriteSheet *monFrontPicTable = (struct CompressedSpriteSheet *)((u32*)gMonFrontPicTable_Pointer)[0];
	struct CompressedSpriteSheet *monFrontPic = monFrontPicTable + myTempData->attackBuffer;
	if(!checkPicLZ(monFrontPic->data))
		monFrontPic = monFrontPicTable;
	
	LZ77UnCompVram(monFrontPic->data,monTilesArm);
	
	struct CompressedSpritePalette *monPaletteTable = (struct CompressedSpritePalette *)((u32*)gMonPaletteTable_Pointer)[myTempData->shiny_2];
	struct CompressedSpritePalette *monPalette = monPaletteTable + myTempData->attackBuffer;

	if (!checkLZ(monPalette->data))
		monPalette = monPaletteTable;
		
	LZ77UnCompVram(monPalette->data,OBJ_PaletteMem2+0x80);
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
	struct Item *itemTable = (struct Item *)((u32*)gItems_Pointer)[0];
	struct Item *item = itemTable + itemId;

	u8 check = checkString2(item->name,14);

	switch (check){
		case 1:
			return 1;
		case 2:
			return item->name;
		default:
			return 0;
	}
}

//检查文本 返回值 0错误文本 1?文本 2正确文本
u8 checkString2(u8 *str,u32 len){
	if(str[0] == 0x3D || str[0] == 0xAC)
		return 1;
	if(str[0] == 0xFF){
		if(((u32 *)str)[0] == -1)
			return 0;
		else
			return 1;
	}
		
	for (u32 i = 1; i < len; i++){
		if(str[i] == 0xFF)
			return 2;
	}
	return 0;	
}

void setbuffer(u8 index,u16 value){
	u16 *buffer = (u16 *)(BUFFER_3+0x40);
	buffer[index] = value;
}

u16 getbuffer(u8 index){
	u16 *buffer = (u16 *)(BUFFER_3+0x40);
	return buffer[index];
}

void bufferMove(u8 index){
	u16 *buffer = (u8 *)(BUFFER_3+0x40);

	for (u32 i = 0; i < 7-index; i++){
		buffer[6-i] = buffer[6-i-index];
	}
}
void sortA(u8 index){
	u16 *buffer = (u8 *)(BUFFER_3+0x40);
	
	if (index == 2 || index == 3){
		u16 temp = buffer[0];
		buffer[0] = buffer[index-1];
		buffer[index-1] = temp;
	
	}
}



