#include "header/funcs.h"
void resetData();
extern u32 check_802();
// extern void set_zi();
extern u32 check_pw();

void set_text(u8 m)
{
	switch(m){
		case 0:
			rboxid_fill_pixels(0,0);
			print_text(24,56,text_table+0x15);
			print_text(96,56,text_table+0x1A);
			print_text(168,56,text_table+0x1F);
			print_text0(0,0,text_table+0x1C9);//作者
			print_text0(176,0,text_table+0x1D3);//版本号
			return;
		case 0x10:
			print_public_text();
			if (strbData->egg)
			{
				print_text(80,56,text_table+0x1E3);
			}
			else
			{
				u32 text = text_table+0x20;
				print_text(24,28,text+0x1B);//等级
				print_text(24,56,text+0x21);//性格
				print_text(24,84,text+0x27);//特性
				print_text(124,28,text+0x2D);//亲密度
				print_text(124,56,text+0x35);//闪光
				print_text(124,84,text+0x3B);//性别
				if(strbData->over == 0)
					resetData(0);
				u32 temp = 0x02021EC8;
				u_int_to_str(temp,strbData->lvl,2,3);
				print_text(60,28,temp);//等级s
				u_int_to_str(temp,strbData->happiness,2,3);
				print_text(168,28,temp);//亲密度s
				temp = text_table+0x77+5*strbData->nature;
				print_text(60,56,temp);//性格s
				temp = getAbilityName();
				if(!temp){
					temp = text_table+0x6B+6*strbData->ability;
				}
				print_text(60,84,temp);//特性s
				temp = text_table+0xF4+2*strbData->shiny;
				print_text(160,56,temp);//闪光s
				temp = text_table+0xFB+4*strbData->sex;
				print_text(160,84,temp);//性别s
			}
			return;
		case 0x11:
			print_public_text();
			print_text(24,28,text_table+0x24C);//球种
			print_text(120,28,text_table+0x252);//捕获地
			print_text(24,56,text_table+0x25A);//瞬移
			print_text(120,56,text_table+0x280);//时间
			print_text(170,56,text_table+0x286);//时
			u_int_to_str(&strbData->numTextBuff,strbData->SP_attack,2,2);
			print_text(156,56,&strbData->numTextBuff);//时间s
			print_text(24,84,text_table+0x289);//复制精灵
			print_text(76,84,text_table+0x1B0-(strbData->SP_defence)*3);

			print_text(120,84,text_table+0x2B2);//精灵听话
			print_text(172,84,text_table+0x1B0-(strbData->ability)*3);
			u32 mapName = 0x02021DE4;
			if(strbData->hp <= 0xD4)
				get_mapName(mapName,strbData->hp,0);
			else if (strbData->hp == 0xFF)
				mapName = text_table+0x26E;
			else
				mapName = text_table+0x269;
			
			print_text(164,28,mapName);//捕获地s
			if(strbData->attackBuffer == 0)
				print_text(60,28,text_table+0x189);
			else
				print_text(60,28,getItemName(strbData->attackBuffer));//球种s
			//飞行点
			if(strbData->speed == 0)
				print_text(60,56,text_table+0x189);
			else{
				/* print_text(60,56,text_table+0x279);
				u32 fly_txt = 0x02021EC8;
				u_int_to_str(fly_txt,strbData->speed,2,2);
				print_text(98,56,fly_txt); */
				struct fly **fly_p = (struct fly **)0x08122C80;
				(*fly_p) += (strbData->speed-1);
				u16 m = getMapId((*fly_p)->bank, (*fly_p)->map);
				get_MapName(mapName+0x20,m,0);
				print_text(60,56,mapName+0x20);
			}
			
			

			

			return;
		case 0x12:
			//return;
		case 0x13:
			//rboxid_fill_pixels(0,0);
			print_public_text();
			if (strbData->egg)
			{
				print_text(80,56,text_table+0x1E3);
			}
			else
			{
				u32 text2 = text_table+0x100;
				print_text(30,28,text2+0xE);//HP
				print_text(24,56,text2+0x12);//物攻
				print_text(24,84,text2+0x18);//物防
				print_text(124,28,text2+0x1E);//速度
				print_text(124,56,text2+0x24);//特攻
				print_text(124,84,text2+0x2A);//特防
				text2 = text2+0x30+7*(strbData->mode-0x12);//2-2||3-2
				print_text(180,0,text2);//个体/努力
				if(strbData->over == 0 || strbData->select == 0)
					setattr();
				if(strbData->mode == 0x13){
					print_text0(40,104,text_table+0x221);
					print_text0(32,104,text_table+0x1B0-strbData->sex*3);//添加[点]
				}
					
				text2 = 0x02021EC8;
				u_int_to_str(text2,strbData->hp,2,3);
				print_text(60,28,text2);//HPs
				u_int_to_str(text2,strbData->attack,2,3);
				print_text(60,56,text2);//物攻s
				u_int_to_str(text2,strbData->defence,2,3);
				print_text(60,84,text2);//物防s
				u_int_to_str(text2,strbData->speed,2,3);
				print_text(160,28,text2);//速度s
				u_int_to_str(text2,strbData->SP_attack,2,3);
				print_text(160,56,text2);//特攻s
				u_int_to_str(text2,strbData->SP_defence,2,3);
				print_text(160,84,text2);//特防s
			}
			return;
		case 0x14:
			//rboxid_fill_pixels(0,0);
			print_public_text();
			u32 text4 = text_table+0x170;
			print_text0(24,92,text4+1);
			print_text0(90,92,text4+7);
			print_text0(24,106,text4+0xD);
			print_text0(90,106,text4+0x15);
			text4 += 0x19;//text4='---'

			for(u8 i = 0;i <= 3;i++){
				if(get_attackN0(i))
					print_text(34,20+i*18,get_attackName(get_attackN0(i)));
				else
					print_text(34,20+i*18,text4);
			}
			/* print_text(34,20,get_attackName(get_attackN0(0)));
			print_text(34,38,get_attackName(get_attackN0(1)));
			print_text(34,56,get_attackName(get_attackN0(2)));
			print_text(34,74,get_attackName(get_attackN0(3))); */
			
			
			u32 text4t = 0x02021EC8;
			if(get_movex(1)>1){
				u_int_to_str(text4t,get_movex(1),2,3);
				print_text0(64,92,text4t);//威力s
			}
			else
				print_text0(64,92,text4);//威力s
			print_text0(122,92,get_type_name(get_movex(2)));//属性s
			if(get_movex(3)>1){
				u_int_to_str(text4t,get_movex(3),2,3);
				print_text0(64,106,text4t);//命中率s
			}
			else{
				print_text0(64,106,text4);//命中率s
			}
			u_int_to_str(text4t,get_movex(4),2,3);
			print_text0(122,106,text4t);//PP
			u16 attN = strbData->attackBuffer;
			u32 a = 0;
			while(a < 2){
				attN--;
				if(attN == 0)
					break;
				a++;
			}
			attN = strbData->attackBuffer;
			u32 b = 0;
			while(b < 2){
				attN++;
				if(!get_attackName(attN))
					break;
				b++;
			}
			if(a+b<4){
				if(a<2)
					b=4-a;
				else
					a=4-b;
			}
			attN = strbData->attackBuffer;
			u32 n = 0;
			while (a){
				print_text(156,n*18+16,get_attackName(attN-a));//前
				n++;
				a--;
			}
			strbData->attackN = 0xFFEF;
			print_text(148,n*18+16,&strbData->attackN);
			print_text(156,n*18+16,get_attackName(attN));//中
			n++;
			u32 m = 1;
			while (m<=b){
				print_text(156,n*18+16,get_attackName(attN+m));//后
				m++;
				n++;
			}
			return;
		case 0x15:
			set_poke_tile();
			showpokepic(0);
			print_public_text();
			get_zhong();

			u32 text5 = text_table+0x100;
			print_text0(14,28+0*14,text5+0xE);//HP
			print_text0(10,28+1*14,text5+0x12);//物攻
			print_text0(10,28+2*14,text5+0x18);//物防
			print_text0(10,28+3*14,text5+0x1E);//速度
			print_text0(10,28+4*14,text5+0x24);//特攻
			print_text0(10,28+5*14,text5+0x2A);//特防
				
			text5 = &strbData->numTextBuff;
			struct get_a_u8 *Gh = (struct get_a_u8 *)&strbData->hp;
			for(int k = 0; k < 6; k++){
				u_int_to_str(text5,Gh->bit,2,3);
				print_text0(42,28+k*14,text5);//HPs
				Gh++;
			}
			

			u32 a5 = 0;
			u16 pokeN;
			pokeN = strbData->attackBuffer;
			while(a5 < 2){
				pokeN--;
				if(pokeN == 0)
					break;
				a5++;
			}
			pokeN = strbData->attackBuffer;
			u32 b5 = 0;
			while(b5 < 2){
				pokeN++;
				u16 pmax = pokeMax->max;
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
			//get_poke_name(species)
			pokeN = strbData->attackBuffer;
			u32 n5 = 0;
			while (a5){
				print_text(156,n5*18+16,get_poke_name(pokeN-a5));//前
				n5++;
				a5--;
			}
			strbData->attackN = 0xFFEF;
			print_text(148,n5*18+16,&strbData->attackN);
			print_text(156,n5*18+16,get_poke_name(pokeN));//中
			n5++;
			u32 m5 = 1;
			while (m5<=b5){
				print_text(156,n5*18+16,get_poke_name(pokeN+m5));//后
				m5++;
				n5++;
			}
			return;
		case 0x16:
			shuru();


			return;
		case 0x20:
			set_item_tile();
			showitempic(0);
			print_public_text();
			u32 text6 = text_table+0x180;
			print_text(120,26,text6+0xD);//数量
			u_int_to_str(0x02021EC8,strbData->Num,2,2);
			print_text(156,26,0x02021EC8);//数值
			print_text(120,50,text6+0x13);//添加
			print_text(108,50,text6+0x30-3 * strbData->hp);//添加[点]
			print_text(120,70,text6+0x1C);//扔掉一个重要道具
			print_text(108,70,text6+0x30-3 * strbData->attack);//扔掉一个重要道具[空心点]
			
			// strbData->attackBuffer = 5;
			u16 S=strbData->attackBuffer;
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
			
			setbuffer(i6,strbData->attackBuffer);
			i6++;

			u32 b6 = 3;
			if(a6 < 3)
				b6 = 6-a6;
			S=strbData->attackBuffer;
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
			for(u8 k=0;k<7;k++){
				u16 Na = getbuffer(k);
				if(Na == strbData->attackBuffer)
				{
					strbData->attackN = 0xFFEF;
					print_text(22,k*17,&strbData->attackN);
					setbuffer(7,k);
				}
				print_text(30,k*17,getItemName(Na));//中
			}
			return;
		case 0x30 :
			print_public_text();
			u32 p_text = text_table+0x1B0;
			print_text(20,20,p_text-3 * strbData->hp);//升级图鉴
			print_text(32,20,text_table+0x1EE);
			print_text(20,48,p_text-3 * strbData->defence);//精灵病毒 
			print_text(32,48,text_table+0x1F7);
			print_text(20,76,p_text-3 * strbData->SP_attack);//出现幻岛 
			print_text(32,76,text_table+0x200);

			// print_text(120,20,p_text-3 * strbData->attack);//喷雾[点]
			print_text(120,20,text_table+0x21B);
			u32 text7 = 0x02021EC8;
			u8 mx = 5;
			if(check_pw()==0xFF)
				mx-=2;
			u_int_to_str(text7,strbData->species,2,mx);
			print_text(156,20,text7);
			print_text(120,48,p_text-3 * strbData->speed);//视野
			print_text(132,48,text_table+0x212);
			print_text(120,76,p_text-3 * strbData->SP_defence);//穿墙
			print_text(132,76,text_table+0x209);
			return;
		case 0x31:
			shuru();
		default:
			return;
	}
	
}

void shuru(){
	if(strbData->defence > 1)
		set_zi();
	else
		set_zi0();
	print_public_text();
	print_text(46,14,0x02021DD4);//名字
	int name_len = 10;
	if(strbData->mode == 0x31)
	{
		name_len = 7;
		print_text(10,0,get_player_name_offset());//玩家
	}
		
	print_text_000(strbData->speed,name_len);//横线 print_text(46,20,0x02021DE4);
	
	print_text(10,40,0x02021DF4);

	print_text0(158,0,text_table+0x230);
	print_text0(148,0,text_table+0x1B0-strbData->sex*3);//锁定页面[点]

	print_text0(170,48,text_table+0x23C);
	getset_start_A();
	print_text(210,48,&strbData->attackN);
	print_text0(170,68,text_table+0x244);
}

void print_public_text(){
	rboxid_fill_pixels(0,0);
	u32 text = text_table+0x20;
	print_text0(176,104,text+0x41);//确认
	print_text0(204,104,text+0x46);//取消
	if(strbData->mode > 0 && strbData->mode < 0x16){
		if(strbData->egg){
			print_text(44,0,text_table+0x1E0);//蛋
		}
		else{
			text = 0x02021DC4;
			print_text(44,0,text);//昵称/种族
		}
	}
	
}
void set_zi(){
	struct font *ft = (struct font *)0x02021DF4;
	u8 a = strbData->hp,b = strbData->attack;
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
	u8 b = strbData->attack;
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

	if(strbData->defence == 0)
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

	if(strbData->defence == 0)
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
	struct get_a_u8 *Aa = (struct get_a_u8 *)&strbData->attackN;
	Aa ++;
	Aa->bit = 0xFF;
	Aa --;
	u16 a = strbData->hp*0x100+strbData->attack;
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
	
	
	Aa->bit = b;

}

void print_text_000(u32 a, u32 b){
	
	b = b-a;
	struct get_a_u8 *text_g = (struct get_a_u8 *)0x02021DE4;
	while (a)
	{
		text_g->bit = 0xB0;
		text_g++;
		a--;
	}
	while (b)
	{
		text_g->bit = 0xAE;
		text_g++;
		b--;
	}
	text_g->bit = 0xFF;
	print_text(46,20,0x02021DE4);

}
void print_text0(u8 pos_x, u8 pos_y, u8 *str)
{
	box_print(0,0,pos_x,pos_y,0x80CCCD4,0,str);
}
void print_text(u8 pos_x, u8 pos_y, u8 *str)
{
	box_print(0,1,pos_x,pos_y,0x80CCCD4,0,str);
}
void resetData(){
	asm("push {lr}\ncmp r0, #0x0\nbeq reset\nmov r0, #0x0\nbl getattr\nldr r2, buffer3_resetData\nmov r1, r2\nadd r1, #0x20\nstr r0, [r1] \nmov r0, r2\nmov r1, r0\nadd r0,#0x10\nadd r1, #0x30\nb resetend\nreset:\nldr r1, buffer3_resetData\nmov r0, r1\nadd r1,#0x10\nadd r0, #0x30\nresetend:\nmov r2, #0x6\nswi #0xB\npop {pc}\n.align 2\nbuffer3_resetData:\n.word 0x02021EC4");
}
void get_ball_addr(){
	asm("push {r4,lr}\nldr r4, buffer3_get_attackN\nmov r0, #0\nstrh r0, [r4,#0x2C]\nmov r0, #0x23\nbl getattr\nstrh r0, [r4,#0x1A]\nmov r0, #0x50\nbl getattr\nstrh r0, [r4,#0x16]\nldr r0, fly_max\nldrb r0, [r0]\nstrb r0, [r4,#0x19]\nmov r0, #0\nstr r0, [r4,#0x1C]\nbl get_ballNumAsm\npop {r4,pc}");
}
void get_ballNum(){
	asm("get_ballNumAsm:\npush {r4,lr}\nmov r4, r0\nldr r3, ball_sav\nldr r0, [r3]\nldrh r1, [r3,#0x4]\nmov r3, #0x0\nball_check:\nlsl r2, r3,#0x2\nadd r2, r0\nldrh r2, [r2]\ncmp r2, #0x0\nbeq ball_check_end\nadd r3, #0x1\ncmp r3, r1\nbne ball_check\nball_check_end:\nldr r2, buffer3_get_attackN\nstrh r3, [r2,#0x2A]\ncmp r3, #0x0\nbeq get_ballNum_end\nldr r2, ball_sav\nldr r2, [r2]\nlsl r4, #0x2\nadd r2, r4\nldrh r0, [r2]\nget_ballNum_end:\npop {r4,pc}\n.align 2\nball_sav:\n.word 0x02039DD8+0x8\nfly_max:\n.word 0x08122C88");
}
void get_attackN(){
	asm("push {r4,lr}\nldr r4, buffer3_get_attackN\nldrb r0, [r4,#0x9]\nmov r1, #0xD\nadd r0, r1\nbl getattr\ncmp r0, #0x0\nbne attackNend\nmov r0, #0x1\nattackNend:\nadd r4, #0x2C\nstrh r0, [r4]\npop {r4,pc}\n.align 2\nbuffer3_get_attackN:\n.word 0x02021EC4");
}
void get_attackN0(){
	asm("push {lr}\nmov r1, #0xD\nadd r0, r1\nbl getattr\npop {pc}");
}
void lvl2exp(){
	asm("push {r4, lr}\nlsl r4, r0,#0x2\nmov r0, #0xB\nbl getattr\nldr r2, pokemon_basestat\nldr r2, [r2]\nmov r1, #0x1C\nmul r0, r1\nadd r0, r2\nadd r0, #0x13\nldrb r0, [r0]\nldr r1, pokemon_max_lvl\nldrb r1, [r1]\ncmp r1, #0x64\nbeq is_old_lvl\nmov r1, #0xFF\nis_old_lvl:\nadd r1, #1\nlsl r1, #0x2\nmul r0, r1\nldr r2, ExperienceTable\nldr r2, [r2]\nadd r0, r2\nadd r0, r4\npop {r4, pc}\n.align 2\nExperienceTable:\n.word 0x080592C4\npokemon_basestat:\n.word 0x080001BC\npokemon_max_lvl:\n.word 0x0804A5BE");
}
void get_attackName(){
	asm("push {r4,lr}\nldr r4, attackNameTable\nldr r4, [r4]\nmov r1, #0xD\nmul r0, r1\nadd r0, r4\nmov r4, r0\nldrb r2, [r0]\ncmp r2, #0xAE\nbeq isAE\nbl checkFF\ncmp r0, #0x0\nbne isName\nb ckNameEnd\nisAE:\nldr r4, AEAEAE\nisName:\nmov r0, r4\nckNameEnd:\npop {r4,pc}\n.align 2\nattackNameTable:\n.word 0x08000148\nAEAEAE:\n.word 0x0832DADB");
}
void getAbilityName(){
	asm("push {r4-r5,lr}\nldr r5, buffer3_getAbilityName\nldrh r0, [r5,#0x12]\nldr r3, basestat_table\nldr r3, [r3]\nmov r1, #0x1C\nmul r0, r1\nadd r0, r3\nadd r0, #0x16\nldrb r5, [r5,#0x16]\nadd r0, r5\nldrb r5, [r0]\nldr r3, ability_table\nldr r3, [r3]\nmov r4, #0xD\nmul r4, r5\nadd r4, r3\nmov r0, r4\nmov r1, #0xC\nbl checkFF\ncmp r0, #0x1\nbeq showAbility\nmov r4, #0xD\nsub r5, #0x4E\nmul r4, r5\nldr r0, ability_table2\nadd r4, r0\nmov r0, r4\nmov r1, #0xC\nbl checkFF\ncmp r0, #0x1\nbeq showAbility\nmov r0, #0x0\nb endd\nshowAbility:\nmov r0, r4\nendd:\npop {r4-r5,pc}\ncheckFF: @r0=offset,r1=length\npush {lr}\nmov r2, #0x1\nmov r3, r0\ncheckc:\nmov r0, r3\nadd r0, r2\nldrb r0, [r0]\ncmp r0, #0xFF\nbeq haveFF\nadd r2, #0x1\ncmp r2, r1\nbls checkc\nb notFF\nhaveFF:\ncmp r2, #0x1\nbeq notFF\nmov r0, #0x1\nb checkend\nnotFF:\nmov r0, #0x0\ncheckend:\npop {pc}\n.align 2\nbuffer3_getAbilityName:\n.word 0x02021EC4\nbasestat_table:\n.word 0x080001BC\nability_table:\n.word 0x080001C0\nability_table2:\n.word 0x082E99F8");
}
void setattr(){
	asm("push {r4-r5,lr}\nldr r5, buffer3_1\nldrb r1, [r5]\nsub r1, #0x12\nadd r5, #0x1A\nmov r2, #0xD\nmov r4, #0x27\nmul r2, r1\nsub r4, r2\nreturn1:\nmov r0, r4\nbl getattr\nstrb r0, [r5]\nadd r4, #0x1\nadd r5, #0x1\nldr r0, buffer3_1\nadd r0, #0x20\ncmp r5, r0\nbne return1\npop {r4-r5,pc}\ngetattr:\npush {lr}\nmov r3, r0\nldr r2, buffer3_1\nadd r2, #0x10\nldrb r2, [r2]\nmov r0, #0x64\nmul r2, r0\nldr r0, party_player\nadd r0, r2\nmov r1, r3\nldr r3, get_attributes\nbl BX_R3_s\npop {pc}\nBX_R3_s:\nbx r3\n.align 2\nbuffer3_1:\n.word 0x02021EC4\nparty_player:\n.word 0x020244EC\nget_attributes:\n.word 0x0806A519");
}
void get_movex(){
	asm("push {lr}\nldr r1, buffer3_move\nadd r1, #0x2C\nldrh r1, [r1]\nmov r2, #0xC\nmul r1, r2\nldr r2, move_table\nldr r2, [r2]\nadd r1, r2\nadd r0, r1\nldrb r0, [r0]\npop {pc}\n.align 2\nmove_table:\n.word 0x080001CC;\nbuffer3_move:\n.word 0x02021EC4");
}
void get_type_name(){
	asm("push {lr}\nldr r1, type_name_table\nldr r1, [r1]\nmov r2, #0x7\nmul r0, r2\nadd r0, r1\npop {pc}\n.align 2\ntype_name_table:\n.word 0x080166F4");
}
void get_poke_name(){
	asm("push {lr}\nldr r2, poke_name_table\nldr r2, [r2]\nmov r1, #0xB\nmul r0, r1\nadd r0, r2\npop {pc}\n.align 2\npoke_name_table:\n.word 0x08000144");
}
void set_item_tile(){
	asm("push {r4,lr}\nldr r0, buffer3_title\nldrh r0, [r0,#0x2C]\nlsl r0, #3\nldr r2, item_pic_table\nldr r2, [r2]\nadd r4, r0,r2\nldr r0, [r4]\nldrb r1, [r0]\ncmp r1, #0x10\nbeq isLz77i\nldr r0, [r2]\nisLz77i:\nldr r1, item_obj_base\nmov r2, #4\nlsl r2, #8\nadd r1, r2\nswi 0x12\nldr r1, item_obj_base\nmov r0, #4\nlsl r0, #8\nadd r0, r1\nldr r3, CopyItemIconPicTo4x4Buffer\nbl BX_R3_itemIcon\nadd r0, r4, #0x4\nldr r0, [r0]\nldrb r1, [r0]\ncmp r1, #0x10\nbeq islz77pi\nldr r0, [r3]\nislz77pi:\nldr r1, OBJ_PaletteMemt\nswi 0x12\npop {r4,pc}\nBX_R3_itemIcon:\nbx r3\n.align 2\nitem_pic_table:\n.word 0x081B0034\nitem_obj_base:\n.word 0x06012000\nCopyItemIconPicTo4x4Buffer:\n.word 0x081afe45");
}
void set_poke_tile(){
	asm("push {r4,lr}\nldr r4, buffer3_title\nldrh r0, [r4,#0x2C]\nmov r1, #0x8\nmul r0, r1\nldr r2, front_sprites\nldr r2, [r2]\nadd r0, r2\nldr r0, [r0]\nldrb r1, [r0]\ncmp r1, #0x10\nbeq isLz77\nldr r0, [r2]\nisLz77:\nldr r1, obj_base\nswi 0x12\nmov r1, r4\nadd r1, #0x38\nldrb r1, [r1]\nmov r2, #0x4\nmul r1, r2\nldr r0, sprites_pal\nadd r0, r1\nldr r0, [r0]\nldr r3, [r0]\nldrh r1, [r4,#0x2C]\nmov r2, #0x8\nmul r1, r2\nadd r0, r1\nldr r0, [r0]\nldrb r1, [r0]\ncmp r1, #0x10\nbeq islz77p\nmov r0, r3\nislz77p:\nldr r1, OBJ_PaletteMemt\nswi 0x12\npop {r4,pc}\n.align 2\nbuffer3_title:\n.word 0x02021EC4\nfront_sprites:\n.word 0x08000128\nobj_base:\n.word 0x06010C00\nsprites_pal:\n.word 0x08000130\nOBJ_PaletteMemt:\n.word 0x02037D14+0x80");
}
void getItemName(){
	asm("push {lr}\nldr r3, item_table\nldr r3, [r3]\nmov r1, #0x2C\nmul r0, r1\nadd r0, r3\nldrb r1, [r0]\ncmp r1, #0x3D\nbeq go_what\ncmp r1, #0xAC\nbeq go_what\ncmp r1, #0xFF\nbeq go_FF1\nmov r2, #0x1\nchck_item:\nmov r3, r0\nadd r3, r2\nldrb r1, [r3]\ncmp r1, #0xFF\nbeq haveFF2\nadd r2, #0x1\ncmp r2, #0xE\nbne chck_item\nnotFF2:\nmov r0, #0x0\nb end_getItemName\nhaveFF2:\ncmp r2, #0x1\nbeq notFF2\nb end_getItemName\ngo_FF1:\nldr r1, [r0]\nmov r2, #0x0\nsub r2, #0x1\ncmp r1, r2\nbeq notFF2\ngo_what:\nmov r0, #0x1\nend_getItemName:\npop {pc}\n.align 2\nitem_table:\n.word 0x80001C8");
}
void setbuffer(){
	asm("push {lr}\nlsl r0, #0x1\nldr r2, buffer3_buffer\nadd r2, r0\nstrh r1, [r2]\npop {pc}\n.align 2\nbuffer3_buffer:\n.word 0x02021EC4+0x40");
}
void bufferMove(){
	asm("push {lr}\nmov r3, #0x7\nsub r3,r0\nldr r1, buffer3_movem\nlsl r0, #0x1\nsub r0, r1, r0\nctnMove:\nldrh r2, [r0]\nstrh r2, [r1]\nsub r1, #0x2\nsub r0, #0x2\nsub r3, #0x1\ncmp r3, #0x0\nbne ctnMove\nmov r0, #0x0\npop {pc}\n.align 2\nbuffer3_movem:\n.word 0x02021F10");
}
void getbuffer(){
	asm("push {lr}\nlsl r0, #0x1\nldr r1, buffer3_getbuffer\nadd r1, r0\nldrh r0, [r1]\npop {pc}\n.align 2\nbuffer3_getbuffer:\n.word 0x02021EC4+0x40");
}
void sortA(){
	asm("push {lr}\nldr r1, buffer3_sort\ncmp r0, #0x2\nbeq sort2\ncmp r0, #0x3\nbeq sort2\nb end_sort\nsort2:\nsub r0, #0x1\nlsl r0, #0x1\nadd r2, r1,r0\nldrh r0, [r1]\nldrh r3, [r2]\nstrh r0, [r2]\nstrh r3, [r1]\nend_sort:\npop {pc}\n.align 2\nbuffer3_sort:\n.word 0x02021EC4+0x40");
}
void get_zhong(){
	asm("push {lr}\nldr r3, basestat_table_Gz\nldr r3, [r3]\nldr r1, buffer3_Gz\nldrh r2, [r1,#0x2C]\nmov r0, #0x1C\nmul r0, r2\nadd r0, r3\nadd r1, #0x1A\nmov r2, #0x3\nswi #0xB\nmov r0, #0\npop {pc}\n.align 2\nbasestat_table_Gz:\n.word  0x80001BC\nbuffer3_Gz:\n.word 0x02021EC4");
}
void get_player_name_offset(){
	asm("push {lr}\nldr r0, sav2_name\nldr r0, [r0]\npop {pc}\n.align 2\nsav2_name:\n.word 0x03005D90");
}
void getMapId(){
	asm("push {lr}\nldr r3, GetMapHeaderByGroupAndId\nbl BX_R3_getmapid\nadd r0, #0x14\nldrh r0, [r0]\npop {pc}\nBX_R3_getmapid:\nbx r3\n.align 2\nGetMapHeaderByGroupAndId:\n.word 0x08084a91");
}
