#include "header/funcs.h"
//flags for buttons3_new_remapped:1=A,2=B,4=SELECT,8=START,0x10=RIGHT,0x20=LEFT,0x40=UP,0x80=DOWN,0x100=L,0x200=R
extern struct rbox_short rbox_table[];
//const char pokemonstring[] = {0x04,0xC6,0x04,0xC6,0xFF};
extern void set_text(u8 page);
extern void select_page();
extern void initMonTempData();
extern void get_attackN();
extern void get_ball_addr();
extern u32 getAttackName(u16 atackNum);
extern u16 get_ballNum();
extern u32 getPlayerNameOffset();
extern u32 lvl2exp();
extern u16 getbuffer(u8 index);
extern void box_draw(u8,u8);
extern void print_text0(u8 pos_x, u8 pos_y, u8 *str);
extern struct Pokemon *getCurrentPartyplayer();
extern void setCurrentMonData(u8 request, void* value);
extern struct BaseStats* getSpeciesBaseStats(u16 species);
extern struct Sprite *getSprite(u8 id);
extern u32 getMonSpeciesName(u16 species);
void reLoadPid();
void aborter(u8 task_id);
void buttonbox_print(u32 str);
void button_left();
void button_right();
void button_up();
void button_down();
void changeMouseColor();
void set_poke_dex(u16 species);
bool8 check_pos();
bool8 check_802();
bool8 check_Ultra_Emerald();
u16 check_pw();
bool32 check_font();
void setvar(u16 id,u16 value);

void task_02(u8 task_id)
{
	// int i;
	switch(*(*malloc_pointer_loc))
	{
		case 0:
			(tasks[task_id].priv[2])++;
			if(tasks[task_id].priv[2] == 0x20)
				break;
			else return;
			break;
		case 1:
			switch(super->buttons4_new_and_keyrepeat)
			{
				case BUTTONS_A:
					if (super->buttons3_new_remapped != BUTTONS_A)
						return;
					PlaySE(5);
					if(myTempData->over == 0){
						if(myTempData->page == PAGE_MAIN){
							switch (myTempData->select)
							{
							case 0:
								myTempData->page = PAGE_POKE_INFO;
								myTempData->party = 0;
								myTempData->modebuffer = 1;
								set_7();
								initMonTempData();
								struct MySaveblock* saveblock = (struct MySaveblock*)VAR_8004;
								showSprite(saveblock->monIconId);
								// showicon(0);
								buttonbox_print(text_table+0x13E);
								select_page();
								updatetext();

								break;
							case 1:
								myTempData->page = PAGE_ITEMS;
								myTempData->Num = 1;
								myTempData->attackBuffer = 1;
								myTempData->modebuffer = 1;
								reset_IVs_buffer();
								myTempData->hp = 1;
								mouseXY->pos_x = 0x5A;
								mouseXY->pos_y = 0x2C;
								buttonbox_print(text_table+0x24);
								select_page();
								updatetext();
								break;
							case 2:
								open_p8();
							default:
								break;
							}
							
						}
						else if (myTempData->page == PAGE_POKE_NAME || myTempData->page == PAGE_PLAYER_NAME){
							shuru_A();
						}
						else if(myTempData->page >= PAGE_POKE_INFO && myTempData->page < PAGE_ITEMS){
							if(myTempData->select < 7){
								changeMouseColor();
								myTempData->over = 1;
								if((myTempData->page == PAGE_POKE_INFO && myTempData->select > 2) || myTempData->select == 0||myTempData->page == PAGE_POKE_INFO2)
									buttonbox_print(text_table+0x163);
								else
									buttonbox_print(text_table+0x161);
							}
							else if(myTempData->select == 7){
									if(myTempData->page == PAGE_POKE_INFO2){
										get_ball_addr();
										struct Time *getTime = (struct Time *)0x03005cf8;
										myTempData->SP_attack = getTime->hours;
									}
									if(myTempData->page == PAGE_MOVES)
										get_attackN();
									if (myTempData->page == PAGE_SPECIE)
										myTempData->attackBuffer = myTempData->species;
									updatetext();
							}
							else if(myTempData->select == 8){
								mouse_wait();
								if(myTempData->egg){
									u16 spe = myTempData->species;
									if(spe == 0x19C)
										spe = umodsi3(Random(),0xFB)+1;
									u8 *egg_lvl = (u8 *)0x08070A38;
									CreateMon(getCurrentPartyplayer(),spe,egg_lvl[0],32,1,Random() | (Random() << 0x10),0,myTempData->TID);
									myTempData->Num = 0;
									SetMonData(getCurrentPartyplayer(),0x24,&myTempData->Num);
									initMonTempData();
									myTempData->modebuffer = 1;
									updatetext();
								}
								else
								{
									if(myTempData->lvl != myTempData->lvl_2)
										SetMonData(getCurrentPartyplayer(),0x19,lvl2exp(myTempData->lvl));
									set_att();
									if(myTempData->page == PAGE_POKE_INFO){
										if(chck_PID()){
											change_pid();
											reLoadPid();
										}
									}
									if(myTempData->page == PAGE_POKE_INFO2){
										u32 mTid = GetPlayerIDAsU32();
										if(myTempData->hp == 0xFF){
											if(myTempData->TID == mTid){
												myTempData->TID -= 10;
												chck_PID();
												change_pid();
												reLoadPid();
											}
										}
										else{
											if(myTempData->TID != mTid){
												myTempData->TID = mTid;
												chck_PID();
												change_pid();
												reLoadPid();
											}
											SetMonData(getCurrentPartyplayer(),0x7,getPlayerNameOffset());
										}
										struct Time *getTime = (struct Time *)0x03005cf8;
										u8 t = getTime->hours;
										if (t != myTempData->SP_attack){
											RtcInitLocalTimeOffset(myTempData->SP_attack,0);//设置时间
										}
										if(myTempData->SP_defence){
											u32 r = GiveMonToPlayer(getCurrentPartyplayer());
											if(r!=2){
												print_text0(26,100,text_table+0x292);
												if(r==1)
													print_text0(66,100,text_table+0x29B);
											}
											else
											{
												print_text0(26,100,text_table+0x2A9);
											}
											
											
										}
										SetMonData(getCurrentPartyplayer(),0x50,&myTempData->ability);
										// myTempData->Num = myTempData->hp;
										SetMonData(getCurrentPartyplayer(),0x23,&myTempData->hp);
										if(myTempData->attackBuffer)
											SetMonData(getCurrentPartyplayer(),0x26,&myTempData->attackBuffer);
										if(myTempData->speed){
											BeginNormalPaletteFade(0xFFFFFFFF,0,0,0x10,0);
											HealPlayerParty();
											DestroyTask(task_id);
											FreeAllWindowBuffers();
											Free(*malloc_pointer_loc);
											struct fly **fly_p = (struct fly **)0x08122C80;
											(*fly_p) += (myTempData->speed-1);
											SetWarpDestination((*fly_p)->bank, (*fly_p)->map, 255, (*fly_p)->pos_x, (*fly_p)->pos_y);
											DoWarp();
											ResetInitialPlayerAvatarState();

										}
										
									}
									if(myTempData->page == PAGE_MOVES){
										SetMonData(getCurrentPartyplayer(),myTempData->attackSelect+0xD,&myTempData->attackBuffer);
										updatetext();
									}
									if(myTempData->page == PAGE_SPECIE){
										checkNmae();
										set_poke_dex(myTempData->attackBuffer);
										SetMonData(getCurrentPartyplayer(),ATTR_SPECIES,&myTempData->attackBuffer);
										myTempData->Num = 2;
										SetMonData(getCurrentPartyplayer(),ATTR_FONT_LANG,&myTempData->Num);
										initMonTempData();
										updatetext();
									}
									CalculateMonStats(getCurrentPartyplayer());
								}

								
							}
							
						}
						else if(myTempData->page == PAGE_ITEMS){
							if(myTempData->select <= 2){
								changeMouseColor();
								myTempData->over = 1;
								buttonbox_print(text_table+0x161);
							}
							if(myTempData->select == 8){
								updatetext();
								mouse_wait();
								if(myTempData->Num&&myTempData->hp){
									u32 additemtext = text_table+0x1BC;
									if(AddBagItem(myTempData->attackBuffer,myTempData->Num))
										additemtext -= 0x9;
									print_text0(120,88,additemtext);//添加成功
								}
								if(myTempData->attack){
									del_last_keyitem();
								}
								
							}
							if(myTempData->select == 3){
								myTempData->hp = !myTempData->hp;
								updatetext();
							}
							if(myTempData->select == 4){
								myTempData->attack = !myTempData->attack;
								updatetext();
							}
							if(myTempData->select == 7){
								myTempData->Num = 0;
								myTempData->attackBuffer = 1;
								myTempData->hp = 1;
								myTempData->attack = 0;
								updatetext();
							}

						}
						if(myTempData->page == PAGE_OTHER){
							if(myTempData->select <= 6){
								if(myTempData->select == 2){
									changeMouseColor();
									myTempData->over = 1;
									buttonbox_print(text_table+0x161);
								}
								else
								{
									select_set_p();
									updatetext();
								}
								
								
							}
							else if(myTempData->select == 7){
								ldr_var4021();
								reset_IVs_buffer();
								updatetext();
							}
							else{
								mouse_wait();
								if(myTempData->hp){
									FlagSet(0x896);
									EnableNationalPokedex();
								}
								if(myTempData->SP_attack){
									setvar(0x4024,myTempData->PID&0xFFFF);
								}
								if(myTempData->defence){
									set_bingdu();
								}
								// if(myTempData->attack){
									setvar(0x4021,myTempData->species);
								// }
								if(myTempData->speed){
									// FlagSet(0x888);
									shiye();
								}
								u8 *cq = (u8 *)0x020322d6;
								cq[0] = myTempData->SP_defence;

							}
							

						}
						
					}
					return;
				case BUTTONS_B:
					if (super->buttons3_new_remapped != BUTTONS_B)
						return;
					if(myTempData->over == 0){
						if((myTempData->page == PAGE_POKE_NAME||myTempData->page == PAGE_PLAYER_NAME)&&myTempData->sex == 1)
						{
							delete_zi();
						}
						else{
							PlaySE(5);
							if(myTempData->page == 0){
								BeginNormalPaletteFade(0xFFFFFFFF,0,0,0x10,0);
								HealPlayerParty();
								break;
							}
							else{
								if(myTempData->page < 0x20){
									hideSprite(myTempData->poke_pic_id);
									struct MySaveblock* saveblock = (struct MySaveblock*)VAR_8004;
									hideSprite(saveblock->monIconId);
									// showpokepic(8);
									// showicon(8);
									mouseXY->pos_x = 0x2E;
									myTempData->select = 0;
								}
								else if(myTempData->page == 0x20){
									hideSprite(myTempData->item_pic_id);
									// showitempic(8);
									mouseXY->pos_x = 0x7A;
									myTempData->select = 1;
								}
								else{
									mouseXY->pos_x = 0xC6;
									myTempData->select = 2;
								}
								
								mouseXY->pos_y = 0x4C;
								buttonbox_print(text_table);
								myTempData->page = 0;
								select_page();
								updatetext();
							}
							
						}
					}
					else{
						PlaySE(5);
						changeMouseColor();
						myTempData->over = 0;
						if(myTempData->page != 0x20)
							buttonbox_print(text_table+0x13E);
						else
							buttonbox_print(text_table+0x24);
					}
					return;
				case BUTTONS_SELECT:
					if (super->buttons3_new_remapped != BUTTONS_SELECT)
						return;
					if(myTempData->page == 0x13||myTempData->page == 0x16||myTempData->page == 0x31){
						myTempData->sex = !myTempData->sex;
						updatetext();
					}
					return;
				case BUTTONS_START:
					if (super->buttons3_new_remapped != BUTTONS_START)
						return;
					if(myTempData->page && myTempData->select != 8 && myTempData->over == 0){
						PlaySE(5);
						set_8();
					}
					return;
				case BUTTONS_RIGHT:
					get_pos();
					button_right();
					if(check_pos())
						PlaySE(5);
					return;
				case BUTTONS_LEFT:
					get_pos();
					button_left();
					if(check_pos())
						PlaySE(5);
					return;
				case BUTTONS_UP:
					get_pos();
					button_up();
					if(check_pos())
						PlaySE(5);
					return;
				case BUTTONS_DOWN:
					get_pos();
					button_down();
					if(check_pos())
						PlaySE(5);
					return;
				case BUTTONS_R:
					if (super->buttons3_new_remapped != BUTTONS_R)
						return;
					if(myTempData->page > 0&&myTempData->page < 0x20&&myTempData->over==0 && !myTempData->egg){
						if(myTempData->page == 0x16){
							shuru_R_1();
							
						}
						else
						{
							PlaySE(6);
							myTempData->page ++;
							select_page();
							if(myTempData->page == 0x11){
								get_ball_addr();
								struct Time *getTime = (struct Time *)0x03005cf8;
								myTempData->SP_attack = getTime->hours;
							}
							if(myTempData->page == 0x13){
								myTempData->sex = 0;
							}
							if(myTempData->page == 0x14){
								myTempData->attackSelect = 0;
								mouseXY->pos_x = 0x66;
								mouseXY->pos_y = 0x28;
								myTempData->select = 1;
								get_attackN();
							}
							if(myTempData->page == 0x15){
								myTempData->attackBuffer = myTempData->species;
								myTempData->select = 4;
								myTempData->attackSelect = 3;
								mouseXY->pos_x = 0x86;
								mouseXY->pos_y = 0x5E;
							}
							if(myTempData->page == 0x16){
								hideSprite(myTempData->poke_pic_id);
								// showpokepic(8);
								open_shuru();
							}
							
							myTempData->modebuffer = 1;
							updatetext();
						}
					}
					else if(myTempData->page == 0x30&&myTempData->over==0)
					{
						PlaySE(6);
						open_shuru();
						myTempData->modebuffer = 1;
						myTempData->page ++;
						select_page();
						updatetext();
					}
					else if (myTempData->page == 0x31)
					{
						if(myTempData->sex&&myTempData->over==0){
							shuru_R_1();
						}
					}
					
					
					return;
				case BUTTONS_L:
					if (super->buttons3_new_remapped != BUTTONS_L)
						return;
					if(myTempData->page > 0x10&&myTempData->page <= 0x16&&myTempData->over==0 && !myTempData->egg){
						if(myTempData->page == 0x16 && myTempData->sex == 1){
							shuru_L_1();
							
						}
						else
						{
							PlaySE(6);
							myTempData->page --;
							select_page();
							if(myTempData->page == 0x11){
								get_ball_addr();
								struct Time *getTime = (struct Time *)0x03005cf8;
								myTempData->SP_attack = getTime->hours;
							}
							if(myTempData->page == 0x13){
								set_7();
								myTempData->sex = 0;
							}
							if(myTempData->page == 0x14){
								mouseXY->pos_x = 0x66;
								get_attackN();
								hideSprite(myTempData->poke_pic_id);
								// showpokepic(8);
							}
							if(myTempData->page == 0x15){
								myTempData->attackBuffer = myTempData->species;
								set_7();
								initMonTempData();
							}
							myTempData->modebuffer = 1;
							updatetext();
							
						}
					}
					else if (myTempData->page == 0x31&&myTempData->over==0)
					{
						if(myTempData->sex)
						{
							shuru_L_1();
						}
						else
						{
							myTempData->modebuffer = 1;
							PlaySE(6);
							open_p8();
						}
					}
					
					return;
					
				default:
					return;
			}
			break;
		case 2:
			aborter(task_id);
			return;
		default:
			return;
	}	
	(*(*malloc_pointer_loc))++;
	return;
}
void button_left()
{
	if(myTempData->over == 0){
		if(myTempData->page == 0){//mode=0
			if(myTempData->select>0){
			mouseXY->pos_x -= 0x4C;
			myTempData->select--;
			}
			else{
				mouseXY->pos_x = 0xC6;
				myTempData->select = 2;
			}
		}
		else if(myTempData->page < 0x14){//mode=1,2,3
			if(umodsi3(myTempData->select+0x10,2) == 0 && myTempData->select != 0){
				if(myTempData->select <= 6){
					mouseXY->pos_x -= 0x5A;
					myTempData->select -= 1;
				}
				else if(!myTempData->egg){
					myTempData->select = 5;
					mouseXY->pos_x = 0x6C;
					mouseXY->pos_y = 0x64;
				}
				
			}
			else if(myTempData->select == 7){
					set_8();
				}
		}
		else if(myTempData->page == 0x14){//mode=4
			if(myTempData->select == 8){
					myTempData->select = myTempData->attackSelect+1;
					mouseXY->pos_x = 0x66;
					mouseXY->pos_y = 0x28+myTempData->attackSelect*18;
				}
			if(myTempData->select == 7){
				set_8();
			}
		}
		else if (myTempData->page == 0x15){//mode=5
			if(myTempData->select == 8){
					myTempData->select = 4;
					mouseXY->pos_x = 0x86;
					mouseXY->pos_y = 0x5E;
				}
			if(myTempData->select == 7){
				set_8();
			}
		}
		else if (myTempData->page == 0x16){
			shuru_left_0();
		}
		else if(myTempData->page == 0x20&&myTempData->select > 1){
			if(myTempData->select < 7 || myTempData->select == 8){
				myTempData->select = 1;
				mouseXY->pos_x = 0x5A;
				mouseXY->pos_y = 0x2C;
			}
			else{
				set_8();
			}
			
		}
		else if(myTempData->page == 0x30){
			if (umodsi3(myTempData->select + 0x10, 2) == 0){
				if (myTempData->select <= 6){
					mouseXY->pos_x -= 0x60;
					myTempData->select -= 1;
				}
				else{
					myTempData->select = 5;
					mouseXY->pos_x = 0x66;
					mouseXY->pos_y = 0x60;
				}
			}
			else if (myTempData->select == 7){
				set_8();
			}
		}
		else if (myTempData->page == 0x31)
		{
			shuru_left_0();
		}
		
		
		
	}
	else if(myTempData->page == 0x12 || myTempData->page == 0x13){
			u8 *ivev = (u8 *)(&myTempData->hp);
			switch(myTempData->select){
				// case 1:
				// 	ivev+0;
				// 	break;
				case 2:
					ivev+=3;
					break;
				case 3:
					ivev+=1;
					break;
				case 4:
					ivev+=4;
					break;
				case 5:
					ivev+=2;
					break;
				case 6:	
					ivev+=5;
					break;
			}
			u8 temp = ivev[0];
			if(temp>10)
				ivev[0]-=10;
			else
				ivev[0] = 0;

			if(temp)
				updatetext();
	}
	else if(myTempData->page == 0x10){
		switch(myTempData->select){
			case 1:
				if(myTempData->lvl > 10){
					myTempData->lvl-=10;
					updatetext();
				}
				else if(myTempData->lvl){
					myTempData->lvl = 0;
					updatetext();
				}
				break;
			case 2:
				if(myTempData->happiness > 10){
						myTempData->happiness-=10;
						updatetext();
				}
				else if(myTempData->happiness){
					myTempData->happiness = 0;
					updatetext();
				}
				
			default :break;
		}
	}
	else if(myTempData->page == 0x14 || myTempData->page == 0x15){
		mode_4_left();
	}
	else if(myTempData->page == 0x20){
		if(myTempData->select == 2){
			u16 numt = myTempData->Num;
			if(numt<10)
				myTempData->Num = 0;
			else
				myTempData->Num -= 10;
			if(numt)
				updatetext();
		}
		else{
			u16 t = getbuffer(7);
			if(t){
				myTempData->attackBuffer = getbuffer(0);
				updatetext();
			}
		}
	}
	else if(myTempData->page == 0x30)
		{
			u16 bus = myTempData->species;
			if(bus>100)
				myTempData->species-=100;
			else
				myTempData->species = 0;
			if(bus)
				updatetext();
		}
	
	
	
}
void button_right()
{
	if(myTempData->over == 0){
		if(myTempData->page == 0){
			if(myTempData->select<2){
			mouseXY->pos_x += 0x4C;
			myTempData->select++;
			}
			else{
				mouseXY->pos_x = 0x2E;
				myTempData->select = 0;
			}
		}
		else if(myTempData->page < 0x14){
			if(umodsi3(myTempData->select+0x10,2) != 0&&myTempData->select <= 6){
				mouseXY->pos_x += 0x5A;
				myTempData->select += 1;
			}
			else if(myTempData->select == 8){
				set_7();
			}
		}
		else if(myTempData->page == 0x14 || myTempData->page == 0x15){
			if(myTempData->select < 7){
				set_8();
			}
			else if(myTempData->select = 8){
				set_7();
			}
		}
		else if (myTempData->page == 0x16){
			shuru_right_0();
			
			
		}
		else if(myTempData->page == 0x20){
			if(myTempData->select == 1){
				myTempData->select = 2;
				mouseXY->pos_x = 0xBE;
			}
			if(myTempData->select == 8){
				set_7();
			}
		}
		else if(myTempData->page == 0x30){
			if(umodsi3(myTempData->select+0x10,2) != 0&&myTempData->select <= 6){
				mouseXY->pos_x += 0x60;
				myTempData->select += 1;
			}
			else if(myTempData->select == 8){
				set_7();
			}
		}
		else if (myTempData->page == 0x31)
		{
			shuru_right_0();
		}
		
		
	}
	else if(myTempData->page == 0x12 || myTempData->page == 0x13){
			u8 *ivev = (u8 *)(&myTempData->hp);
			switch(myTempData->select){
				// case 1:
				// 	ivev+0;
				// 	break;
				case 2:
					ivev+=3;
					break;
				case 3:
					ivev+=1;
					break;
				case 4:
					ivev+=4;
					break;
				case 5:
					ivev+=2;
					break;
				case 6:	
					ivev+=5;
					break;
			}
			u8 temp = ivev[0];
			u8 max=31;
			if(myTempData->page == 0x12)
				max = 31;
			else{
				if (myTempData->sex){
					u32 sum = sum = myTempData->hp+myTempData->speed+myTempData->attack+myTempData->SP_attack+myTempData->defence+myTempData->SP_defence;
					if (sum >= 510)
						max = 0;
					else
					{
						u32 ut = 510 - sum ;
						if (ut >= 255)
						{
							max = 255;
						}
						else
						{
							ut+=temp;
							if (ut < 255)
								max = ut;
							else
								max = 255;
						}
						
					}
				}
				else{
					max = 255;
				}
				
			}
			// MyTest();

			u8 addnum = 10;
			if(temp<max-addnum)
				ivev[0]+=addnum;
			else if (max)
				ivev[0] = max;
			
			if(temp<max)
				updatetext();
	}
	else if(myTempData->page == 0x10){
		u8 max;
		if(myTempData->select==1)
		{
			// max = 100;
			max = myTempData->maxLvl;
		}
		else
			max = 255;
		switch(myTempData->select){
			case 1:
				if(myTempData->lvl < max-10){
					myTempData->lvl+=10;
					updatetext();
				}
				else if(myTempData->lvl != max){
					myTempData->lvl = max;
					updatetext();
				}
				break;
			case 2:
				if(myTempData->happiness < max-10){
					myTempData->happiness+=10;
					updatetext();
				}
				else if(myTempData->happiness != max){
					myTempData->happiness = max;
					updatetext();
				}
				
			default :break;
		}
	}
	else if (myTempData->page == 0x14)
	{
		mode_4_right();
	}
	else if (myTempData->page == 0x15){
		u8 ft = 1;
		while (ft<=4){
			u16 pmax = gPokeMax;
			if(check_802())
				pmax-=2;
			if(myTempData->attackBuffer+ft > pmax)
				break;
			else
				ft++;
		}
		if(ft != 1){
			myTempData->attackBuffer+=(ft-1);
			updatetext();
		}
	}
	else if(myTempData->page == 0x20){
		if(myTempData->select == 2){
			u16 numt = myTempData->Num;
			if(numt>89)
				myTempData->Num = 99;
			else
				myTempData->Num += 10;
			if(numt<99)
				updatetext();
		}
		else{
			u16 t = getbuffer(7);
			if(t < 6){
				myTempData->attackBuffer = getbuffer(6);
				updatetext();
			}
		}
	}
	else if(myTempData->page == 0x30)
		{
			u16 bus = myTempData->species;
			u16 var4021 = check_pw();
			if(bus<var4021-100)
				myTempData->species+=100;
			else
				myTempData->species = var4021;
			if(bus!=var4021)
				updatetext();
		}

	
	
	
}
void button_up()
{
	if(myTempData->over == 0){
		if(myTempData->page > 0 && myTempData->page < 0x14){
			if(myTempData->select > 2){
				if(myTempData->egg){
						myTempData->select = 0;
						mouseXY->pos_x = 0x8C;
						mouseXY->pos_y = 0x14;
					}
				else
				{
					if(myTempData->select != 7){
					mouseXY->pos_y -= 0x18;
					myTempData->select -= 2;
					}
					else{
						myTempData->select = 6;
						mouseXY->pos_x = 0xC6;
						mouseXY->pos_y = 0x64;
					}
				}
			}
			else if(myTempData->select != 0){
				myTempData->select = 0;
				mouseXY->pos_x = 0x8C;
				mouseXY->pos_y = 0x14;
			}
			
		}
		else if(myTempData->page == 0x14){
			if (myTempData->select != 1){
				if (myTempData->select <= 4){
					mouseXY->pos_y -= 18;
					myTempData->select -= 1;
					myTempData->attackSelect--;
					myTempData->modebuffer = 1;
					get_attackN();
					updatetext();
				}
				else{
					myTempData->select = myTempData->attackSelect+1;
					mouseXY->pos_x = 0x66;
					mouseXY->pos_y = 0x28+myTempData->attackSelect*18;
				}
			}
		}
		else if (myTempData->page == 0x15 && myTempData->select > 4){
			myTempData->select = 4;
			mouseXY->pos_x = 0x86;
			mouseXY->pos_y = 0x5E;
					
		}
		else if(myTempData->page == 0x16){
			shuru_up_0();
		}
		else if(myTempData->page == 0x20&&myTempData->select > 2){
			if(myTempData->select <= 4){
				mouseXY->pos_y -= 0x18;
				myTempData->select--;
			}
			else{
				myTempData->select = 4;
				mouseXY->pos_x = 0xBE;
				mouseXY->pos_y = 0x5C;
			}
		}
		else if(myTempData->page == 0x30){
			if(myTempData->select>2){
				if (myTempData->select != 7){
					mouseXY->pos_y -= 0x1C;
					myTempData->select -= 2;
				}
				else{
					myTempData->select = 6;
					mouseXY->pos_x = 0xC6;
					mouseXY->pos_y = 0x60;
				}
			}
		}
		else if (myTempData->page == 0x31)
		{
			shuru_up_0();
		}
		
		
		
		
	}
	else if(myTempData->page == 0x12 || myTempData->page == 0x13){
			u8 *ivev = (u8 *)(&myTempData->hp);
			switch(myTempData->select){
				case 0:
					set_pat_u();
					return;
				// case 1:
				// 	ivev+0;
				// 	break;
				case 2:
					ivev+=3;
					break;
				case 3:
					ivev+=1;
					break;
				case 4:
					ivev+=4;
					break;
				case 5:
					ivev+=2;
					break;
				case 6:	
					ivev+=5;
					break;
			}
			u8 temp = ivev[0];
			u8 max;
			if(myTempData->page == 0x12)
				max = 31;
			else{
				if (myTempData->sex){
					u32 sum = sum = myTempData->hp+myTempData->speed+myTempData->attack+myTempData->SP_attack+myTempData->defence+myTempData->SP_defence;
					if (sum >= 510)
						max = 0;
					else
					{
						u32 ut = 510 - sum ;
						if (ut >= 255)
						{
							max = 255;
						}
						else
						{
							ut+=temp;
							if (ut < 255)
								max = ut;
							else
								max = 255;
						}
						
					}
				}
				else{
					max = 255;
				}
			}

			if(temp<max-1)
				ivev[0]++;
			else if(max)
				ivev[0] = max;

			if(temp<max)
				updatetext();
	}
	else if(myTempData->page == 0x10){
		u8 max;
		if(myTempData->select==1)
		{
			// max = 100;
			max = myTempData->maxLvl;
		}
		else
			max = 255;
		switch(myTempData->select){
			case 0:
				set_pat_u();
				return;
			case 1:
				if(myTempData->lvl < max){
					myTempData->lvl++;
					updatetext();
				}
				break;
			case 2:
				if(myTempData->happiness < max){
						myTempData->happiness++;
						updatetext();
				}
				break;
			case 3:
				if(myTempData->nature<0x18){
					myTempData->nature++;
					updatetext();
				}
				break;
			case 4:
				myTempData->shiny = !myTempData->shiny;
				updatetext();
				break;
			case 5:
				set_ability();
				updatetext();
				break;
			case 6:
				if(myTempData->sex == 1 || myTempData->sex == 2)
					myTempData->sex = !(myTempData->sex-1)+1;
				updatetext();
			default : break;
		}
	}
	else if (myTempData->page == 0x11)
	{
		switch (myTempData->select)
		{
		case 0:
			set_pat_u();
			return;
		case 1: 
			if(myTempData->attackN && (myTempData->defence > 0)){
					myTempData->defence --;
					if(myTempData->defence)
						myTempData->attackBuffer = get_ballNum(myTempData->defence-1);
					else
						myTempData->attackBuffer = 0;
					
					updatetext();
				}
			break;
		case 2:
			if(myTempData->hp == 0xFF)
				myTempData->hp = 0xD4;
			else
				myTempData->hp --;
			updatetext();
			break;
		case 3:
			if(myTempData->speed){
				myTempData->speed --;
				updatetext();
			}
			break;
		case 4:
			//if(myTempData->SP_attack){
				myTempData->SP_attack --;
				if(myTempData->SP_attack==255)
					myTempData->SP_attack = 23;
				updatetext();
			//}
			break;
		case 5:
			myTempData->SP_defence = !(myTempData->SP_defence);
			updatetext();
			break;
		case 6:
			myTempData->ability = !(myTempData->ability);
			updatetext();
		default:
			break;
		}
	}
	else if(myTempData->page == 0x14 || myTempData->page == 0x15){
			if(myTempData->attackBuffer > 1){
				myTempData->attackBuffer--;
				// if(myTempData->page == 5)
				// 	set_poke_tile();
				updatetext();
			}
		}
		else if(myTempData->page == 0x16)
		{
			shuru_up_1();
		}
		else if(myTempData->page == 0x20){
			if(myTempData->select == 1){
				u16 t = getbuffer(7);
				if(t){
					myTempData->attackBuffer = getbuffer(t-1);
					updatetext();
				}
			}
			else if(myTempData->Num<99){
				myTempData->Num++;
				updatetext();
			}	
		}
		else if(myTempData->page == 0x30)
		{
			u16 var4021 = check_pw();
			if(myTempData->species<var4021){
				myTempData->species++;
				updatetext();
			}
			
		}
		else if (myTempData->page == 0x31)
		{
			shuru_up_1();
		}
		
		
		
		
}
void button_down()
{
	if(myTempData->over == 0){
		if(myTempData->page > 0&&myTempData->page < 0x14){
			if(myTempData->select < 7){
				if(myTempData->select == 0){
					if(myTempData->egg){
						set_8();
					}
					else
					{
						myTempData->select = 1;
						mouseXY->pos_x = 0x6C;
						mouseXY->pos_y = 0x34;
					}
					
					
				}
				else if(myTempData->select != 5){
					mouseXY->pos_y += 0x18;
					myTempData->select += 2;
				}
				else{
					set_8();
				}
			}
		}
		else if(myTempData->page == 0x14){
			if(myTempData->select < 4){
					mouseXY->pos_y += 18;
					myTempData->select += 1;
					myTempData->attackSelect++;
					myTempData->modebuffer = 1;
					get_attackN();
					updatetext();
				}
				else if(myTempData->select == 4){
					set_8();
				}
		}
		else if(myTempData->page == 0x15){
			if(myTempData->select < 7){
				set_8();
			}
		}
		else if (myTempData->page == 0x16){
			shuru_down_0();
			
			
		}
		else if(myTempData->page == 0x20){
			if(myTempData->select > 1&&myTempData->select < 4){
				mouseXY->pos_y += 0x18;
				myTempData->select++;
			}
			else if(myTempData->select == 1||myTempData->select == 4){
				set_8();
			}
		}
		else if(myTempData->page == 0x30){
			if(myTempData->select < 7){
				if(myTempData->select != 5){
					mouseXY->pos_y += 0x1C;
					myTempData->select += 2;
				}
				else{
					set_8();
				}
			}
			
		}
		else if (myTempData->page == 0x31)
		{
			shuru_down_0();
		}
		
		
	}
	else if(myTempData->page == 0x12 || myTempData->page == 0x13){
			u8 *ivev = (u8 *)(&myTempData->hp);
			switch(myTempData->select){
				case 0:
					set_pat_d();
					return;
				// case 1:
				// 	ivev+0;
				// 	break;
				case 2:
					ivev+=3;
					break;
				case 3:
					ivev+=1;
					break;
				case 4:
					ivev+=4;
					break;
				case 5:
					ivev+=2;
					break;
				case 6:	
					ivev+=5;
					break;
			}
			u8 temp = ivev[0];
			if (temp)
			{
				ivev[0]--;
				updatetext();
			}
	}
	else if(myTempData->page == 0x10){
		switch(myTempData->select){
			case 0:
				set_pat_d();
				return;
			case 1:
				if(myTempData->lvl){
					myTempData->lvl--;
					updatetext();
				}
				break;
			case 2:
				if(myTempData->happiness){
						myTempData->happiness--;
						updatetext();
				}
				break;
			case 3:
				if(myTempData->nature){
					myTempData->nature--;
					updatetext();
				}
				break;
			case 4:
				myTempData->shiny = !myTempData->shiny;
				updatetext();
				break;
			case 5:
				set_ability();
				updatetext();
				break;
			case 6:
				if(myTempData->sex == 1 || myTempData->sex == 2)
					myTempData->sex = !(myTempData->sex-1)+1;
				updatetext();
			default :break;
		}
	}
	else if (myTempData->page == 0x11)
	{
		switch (myTempData->select)
		{
		case 0:
			set_pat_d();
			return;
		case 1:
			if(myTempData->attackN && (myTempData->defence < myTempData->attackN)){
				myTempData->defence ++;
				myTempData->attackBuffer = get_ballNum(myTempData->defence-1);
				updatetext();
			}
			break;
		case 2:
			if(myTempData->hp == 0xD4)
				myTempData->hp = 0xFF;
			else
				myTempData->hp ++;
			updatetext();
			break;
		case 3:
			if(myTempData->speed <= myTempData->sex){
				myTempData->speed ++;
				updatetext();
			}
		break;
		case 4:
			//if(myTempData->SP_attack){
				myTempData->SP_attack ++;
				if(myTempData->SP_attack==24)
					myTempData->SP_attack = 0;
				updatetext();
			//}
		break;
		case 5:
			myTempData->SP_defence = !(myTempData->SP_defence);
			updatetext();
			break;
		case 6:
			myTempData->ability = !(myTempData->ability);
			updatetext();
		default:
			break;
		}
	}
	else if(myTempData->page == 0x14){
			if(getAttackName(myTempData->attackBuffer+1)){
				myTempData->attackBuffer++;
				updatetext();
			}
		}
		else if (myTempData->page == 0x15)
		{
			u16 pmax = gPokeMax;
			if(check_802())
				pmax-=2;
			if(myTempData->attackBuffer < pmax){
				myTempData->attackBuffer++;
				updatetext();
			}
			
		}
		else if (myTempData->page == 0x16)
		{
			shuru_down_1();


		}
		else if(myTempData->page == 0x20){
			if(myTempData->select == 1){
				u16 t = getbuffer(7);
				if(t < 6){
					myTempData->attackBuffer = getbuffer(t+1);
					updatetext();
				}
			}
			else if(myTempData->Num){
				myTempData->Num--;
				updatetext();
			}
			
		}
		else if(myTempData->page == 0x30 && myTempData->species)
		{
			myTempData->species--;
			updatetext();
		}
		else if (myTempData->page == 0x31)
		{
			shuru_down_1();
		}
		
		
		
	
}
void aborter(u8 task_id)
{
	if(((pal_fade_control->mix_color) >> 8 & 0x80))
		return;
	DestroyTask(task_id);
	FreeAllWindowBuffers();
	Free(*malloc_pointer_loc);
	SetMainCallback2(CB2_ReturnToFieldContinueScript);
	return;
}
void open_shuru(){
	set_7();
	reset_IVs_buffer();
	reset_ff_buffer2_add10();
	myTempData->sex = 1;
	myTempData->attack = 0xBB;
}
void shuru_down_0(){
	if(myTempData->select == 1){
		myTempData->select = 2;
		mouseXY->pos_x = 0xE2;
		mouseXY->pos_y = 0x58;
	}
	else if (myTempData->select == 2){
		set_7();
	}
	else
	{
		if(myTempData->select > 0xD7){
			myTempData->select -= 10;
			mouseXY->pos_y += 0x10;
		}
	}
}
void shuru_down_1(){
	u8 *Aa = (u8 *)&myTempData->attackN;
	switch (Aa[0])
	{
	case 0xBB:
		myTempData->hp = 0;
		myTempData->attack = 0xBB;
		break;
	case 0xBC:
		myTempData->hp = 1;
		myTempData->attack = 0;
		break;
	case 0xBD:
		myTempData->hp = 1;
		myTempData->attack = 0x24;
		break;
	case 0xBE:
		myTempData->hp = 1;
		myTempData->attack = 0xDC;
		break;
	case 0xBF:
		myTempData->hp = 2;
		myTempData->attack = 0xCE;
		break;
	case 0xC0:
		myTempData->hp = 3;
		myTempData->attack = 0x8F;
		break;
	case 0xC1:
		myTempData->hp = 3;
		myTempData->attack = 0xA5;
		break;
	case 0xC2:
		myTempData->hp = 4;
		myTempData->attack = 0x2B;
		break;
	case 0xC4:
		myTempData->hp = 4;
		myTempData->attack = 0xC6;
		break;
	case 0xC5:
		myTempData->hp = 5;
		myTempData->attack = 0x84;
		break;
	case 0xC6:
		myTempData->hp = 7;
		myTempData->attack = 0xB4;
		break;
	case 0xC7:
		myTempData->hp = 8;
		myTempData->attack = 0x21;
		break;
	case 0xC8:
		myTempData->hp = 9;
		myTempData->attack = 0x22;
		break;
	case 0xC9:
		myTempData->hp = 9;
		myTempData->attack = 0xB9;
		break;
	case 0xCA:
		myTempData->hp = 0xA;
		myTempData->attack = 0x13;
		break;
	case 0xCB:
		myTempData->hp = 0xA;
		myTempData->attack = 0x1B;
		break;
	case 0xCC:
		myTempData->hp = 0xA;
		myTempData->attack = 0x95;
		break;
	case 0xCD:
		myTempData->hp = 0xB;
		myTempData->attack = 0x3B;
		break;
	case 0xCE:
		myTempData->hp = 0xB;
		myTempData->attack = 0x76;
		break;
	case 0xD1:
		myTempData->hp = 0xC;
		myTempData->attack = 0x9D;
		break;
	case 0xD2:
		myTempData->hp = 0xD;
		myTempData->attack = 0x42;
		break;
	case 0xD3:
		myTempData->hp = 0xD;
		myTempData->attack = 0xBA;
		break;
	case 0xD4:
		myTempData->hp = 0xE;
		myTempData->attack = 0xA2;
		break;
	case 0xB0:
		myTempData->hp = 0xF;
		myTempData->attack = 0xDD;
		break;
	
	
	default:
		break;
	}
	if(Aa[0] == 0xBB)
		myTempData->defence = 0;
	if(Aa[0] != 0xA1)
		updatetext();
}
void shuru_up_0(){
	if(myTempData->select == 7||myTempData->select == 8)
	{
		myTempData->select = 2;
		mouseXY->pos_x = 0xE2;
		mouseXY->pos_y = 0x58;
	}
	else if(myTempData->select == 2){
		myTempData->select = 1;
		mouseXY->pos_x = 0xE2;
		mouseXY->pos_y = 0x48;
	}
	else
	{
		if(myTempData->select > 8&&myTempData->select < 0xF6){
			myTempData->select += 10;
			mouseXY->pos_y -= 0x10;
		}
	}
}
void shuru_up_1(){
	u8 *Aa = (u8 *)&myTempData->attackN;
	switch (Aa[0])
	{
	case 0xA1:
		myTempData->hp = 1;
		myTempData->attack = 0;
		break;
	case 0xBB:
		myTempData->hp = 1;
		myTempData->attack = 0x24;
		break;
	case 0xBC:
		myTempData->hp = 1;
		myTempData->attack = 0xDC;
		break;
	case 0xBD:
		myTempData->hp = 2;
		myTempData->attack = 0xCE;
		break;
	case 0xBE:
		myTempData->hp = 3;
		myTempData->attack = 0x8F;
		break;
	case 0xBF:
		myTempData->hp = 3;
		myTempData->attack = 0xA5;
		break;
	case 0xC0:
		myTempData->hp = 4;
		myTempData->attack = 0x2B;
		break;
	case 0xC1:
		myTempData->hp = 4;
		myTempData->attack = 0xC6;
		break;
	case 0xC2:
		myTempData->hp = 5;
		myTempData->attack = 0x84;
		break;
	case 0xC4:
		myTempData->hp = 7;
		myTempData->attack = 0xB4;
		break;
	case 0xC5:
		myTempData->hp = 8;
		myTempData->attack = 0x21;
		break;
	case 0xC6:
		myTempData->hp = 9;
		myTempData->attack = 0x22;
		break;
	case 0xC7:
		myTempData->hp = 9;
		myTempData->attack = 0xB9;
		break;
	case 0xC8:
		myTempData->hp = 0xA;
		myTempData->attack = 0x13;
		break;
	case 0xC9:
		myTempData->hp = 0xA;
		myTempData->attack = 0x1B;
		break;
	case 0xCA:
		myTempData->hp = 0xA;
		myTempData->attack = 0x95;
		break;
	case 0xCB:
		myTempData->hp = 0xB;
		myTempData->attack = 0x3B;
		break;
	case 0xCC:
		myTempData->hp = 0xB;
		myTempData->attack = 0x76;
		break;
	case 0xCD:
		myTempData->hp = 0xC;
		myTempData->attack = 0x9D;
		break;
	case 0xCE:
		myTempData->hp = 0xD;
		myTempData->attack = 0x42;
		break;
	case 0xD1:
		myTempData->hp = 0xD;
		myTempData->attack = 0xBA;
		break;
	case 0xD2:
		myTempData->hp = 0xE;
		myTempData->attack = 0xA2;
		break;
	case 0xD3:
		myTempData->hp = 0xF;
		myTempData->attack = 0xDD;
		break;
	case 0xD4:
		myTempData->hp = 0x11;
		myTempData->attack = 0x32;
		
	
	default:
		break;
	}
	myTempData->defence = 2;
	if(Aa[0] != 0xB0)
		updatetext();
}
void shuru_right_0(){
	if(myTempData->select <= 8){
		if(myTempData->select == 8)
			set_7();
	}
	else{
		if(umodsi3((myTempData->select),10)!=6){
			if(myTempData->defence > 1)
				mouseXY->pos_x+=15;
			else
				mouseXY->pos_x+=12;
			myTempData->select -= 1;
		}
		else{
			if(myTempData->select>=0xEC)
			{
				myTempData->select = 1;
				mouseXY->pos_x = 0xE2;
				mouseXY->pos_y = 0x48;
			}
			else if (myTempData->select == 0xE2)
			{
				myTempData->select = 2;
				mouseXY->pos_x = 0xE2;
				mouseXY->pos_y = 0x58;
			}
			else
			{
				set_8();
			}
			
			
		}
		
	}
}
void shuru_left_0(){
	if(myTempData->select<=8){
		if(myTempData->select == 7){
			set_8();
		}
		else{
			myTempData->select = 0xFF;
			mouseXY->pos_x = 0x1C;
			mouseXY->pos_y = 0x3C;
		}
		
	}
	else{
		if(umodsi3((myTempData->select),10)!=5){
			if(myTempData->defence > 1)
				mouseXY->pos_x-=15;
			else
				mouseXY->pos_x-=12;
			myTempData->select += 1;
		}
	}
}
void shuru_L_1(){
	if(myTempData->defence > 1)
	{
		if(myTempData->hp+myTempData->attack>1)
		{
			if(myTempData->attack<50)
			{
				if(myTempData->hp>1){
					myTempData->hp--;
					myTempData->attack = 0xC8;
					if(myTempData->hp == 6)
							myTempData->hp = 5;
					if(myTempData->hp == 0x1B)
						myTempData->hp = 0x1A;
				}
				else{
					myTempData->attack = 0;
				}
			}
			else
				myTempData->attack -= 50;
			updatetext();
		}
		else
		{
			myTempData->defence = 1;
			myTempData->hp = 0;
			myTempData->attack = 0xD5;
			set_7();
			updatetext();
		}
		
	}
	else if(myTempData->defence == 1)
	{
		myTempData->defence = 0;
		
		myTempData->attack = 0xBB;
		set_7();
		updatetext();
	}
}
void shuru_R_1(){
	if(myTempData->sex == 1){//
		if(myTempData->defence > 1)
		{
			if(check_font()){
				myTempData->attack += 50;
				if(myTempData->attack >= 0xF7){
					myTempData->attack = 0;
					myTempData->hp++;
					if(myTempData->hp == 6)
						myTempData->hp = 7;
					if(myTempData->hp == 0x1B)
						myTempData->hp = 0x1C;
				}

				updatetext();
			}
		}
		else{
			myTempData->defence++;
			set_7();
			if(myTempData->defence == 1)
				myTempData->attack = 0xD5;
			else{
				myTempData->hp = 1;
				myTempData->attack = 0;
			}
			updatetext();
		}
		
	}
}
void shuru_A(){
	if(myTempData->select == 1){
		changeMouseColor();
		myTempData->over = 1;
		buttonbox_print(text_table+0x163);
	}
	if(myTempData->select == 2)
		{delete_zi();}
	if(myTempData->select == 7)
	{
		myTempData->speed = 0;
		reset_ff_buffer2_add10();
		updatetext();
	}
	if(myTempData->select == 8){
		// mouse_wait();
		u8 *name_text = (u8 *)0x02021DD4;
		if(myTempData->page == 0x16)
		{
			if(name_text[0] != 0xFF)
				set_poke_name();
			myTempData->Num = 2;
			SetMonData(getCurrentPartyplayer(),0x3,&myTempData->Num);

			PlaySE(6);
			set_7();
			initMonTempData();
			myTempData->attackBuffer = myTempData->species;
			myTempData->page --;
			myTempData->modebuffer = 1;
			select_page();
			updatetext();
		}
		else
		{
			if(name_text[0] != 0xFF)
				StringCopy(getPlayerNameOffset(),0x02021DD4);
			// updatetext();
			PlaySE(6);
			myTempData->modebuffer = 1;
			open_p8();
		}
		
	}
	if(myTempData->select > 8){
		u8 *text_n = (u8 *)0x02021DD4;
		struct font *text_f = (struct font *)0x02021DF4;
		u32 m = 2;
		if(myTempData->defence < 2)
			m --;
		int name_len = 10;
		if(myTempData->page == 0x31)
			name_len = 7;
		if(myTempData->speed <= name_len-m)
		{
			text_n += myTempData->speed;
			myTempData->speed += m;
			text_f += (0xFF-myTempData->select);

			if(m == 2){
				text_n[0] = text_f->zi1;
				text_n++;
				text_n[0] = text_f->zi2;
			}
			else{
				text_n[0] = text_f->zi2;
			}

			updatetext();
		}
				
	}
}


void delete_zi(){
	if(myTempData->speed)
	{
		u8 *text_nd = (u8 *)0x02021DD4;
		u32 dm = 0;
		if(myTempData->speed > 1)
			dm = myTempData->speed-2;
		text_nd += dm;
		
		dm = 1;
		if(text_nd[0] > 0&&text_nd[0] < 0x20)
			dm = 2;
		
		if(myTempData->speed != 1)
			text_nd++;

		myTempData->speed -= dm;

		
		
		while (dm)
		{
			text_nd[0] = 0xFF;
			text_nd--;
			dm--;
		}
		
		PlaySE(3);
		myTempData->modebuffer = 1;
		updatetext();
	}
}

void open_p8(){
	u8 *cq = (u8 *)0x020322d6;
	cq[0] = 0;
	myTempData->page = 0x30;
	myTempData->modebuffer = 2;
	initMonTempData();
	reset_IVs_buffer();
	buttonbox_print(text_table+0x13E);
	ldr_var4021();
	select_page();
	updatetext();
	set_7();
}

void set_8(){
	myTempData->select = 8;
	mouseXY->pos_x = 0xC6;
	mouseXY->pos_y = 0x7C;
}
void set_7(){
	myTempData->select = 7;
	mouseXY->pos_x = 0xE2;
	mouseXY->pos_y = 0x7C;
}

void set_pat_d(){
	u8 partyMax = ((u8 *)gPlayerPartyCount)[0];
	if(myTempData->party<partyMax-1){
		myTempData->party++;
		u8 t = myTempData->sex;
		initMonTempData();
		if(myTempData->page == 0x11)
			get_ball_addr();
		if (myTempData->page == PAGE_EVS)
			myTempData->sex = t;
		select_page();
		updatetext();
	}
}
void set_pat_u(){
	if(myTempData->party){
		myTempData->party--;
		u8 t = myTempData->sex;
		initMonTempData();
		if(myTempData->page == 0x11)
			get_ball_addr();
		if (myTempData->page == PAGE_EVS)
			myTempData->sex = t;
		select_page();
		updatetext();
	}
}

void buttonbox_print(u32 str)
{
	u8 boxid_t = myTempData->boxid;
	FillWindowPixelBuffer(boxid_t,0x11);
	AddTextPrinterParameterized(boxid_t,1,str,6,0,0,0); //按键提示
}
void set_ability(){
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
	else
	{
		myTempData->ability = !myTempData->ability;
	}
	
}
void mode_4_right(){
	u8 rt = 1;
		while (rt<=4){
			if(!getAttackName(myTempData->attackBuffer+rt))
				break;
			else
				rt++;
		}
		if(rt != 1){
			myTempData->attackBuffer+=(rt-1);
			updatetext();
		}
		
}
void mode_4_left(){
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
		updatetext();
	}
	
}
void updatetext(){
	if(myTempData->modebuffer)
		myTempData->modebuffer--;
	else
		PlaySE(5);
	set_text(myTempData->page);
}
void mouse_wait(){
	changeMouseColor();
	pause();
	changeMouseColor();
}
void ldr_var4021(){
	u16 var4021 = VarGet(0x4021);
	if(check_pw()==0xFF){
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
void reLoadPid(){
	u32 pid = getCurrentMonData(ATTR_PID);
	myTempData->PID = pid;
	backupMonTempData();
}

void set_att(){
	switch (myTempData->page)
	{
		case PAGE_POKE_INFO:{
			struct Pokemon* party = getCurrentPartyplayer();
			party->padding = 0;
			myTempData->Num = myTempData->ability;
			setCurrentMonData(ATTR_ABILITY_BIT,&myTempData->Num);
			myTempData->Num = myTempData->happiness;
			setCurrentMonData(ATTR_HAPPINESS,&myTempData->Num);

			

		}break;
		case PAGE_IVS:
		case PAGE_EVS:{
			u8 request;
			if (myTempData->page == PAGE_IVS){
				request = ATTR_HP_IV;
			}
			else{
				request = ATTR_HP_EV;
			}
			u8 *eviv = (u8 *)&myTempData->hp;
			for (u8 i = 0; i < 6; i++,request++){
				setCurrentMonData(request,&eviv[i]);
			}
		}break;
		default:
			break;
	}
}
void set_poke_name(){
	CpuSet(BUFFER_2+0x10,&getCurrentPartyplayer()->nickname,5);
}

void pause(){
	asm("push {lr}\nmov r0, #0\nmov r1, #0xFF\nlsl r1, #0xA\npause_t:\nadd r0, #0x1\ncmp r0, r1\nbne pause_t\npop {pc}\nBX_R3:\nbx r3");
}
void chck_PID(){
	// if(myTempData->page == PAGE_POKE_INFO2){
	// 	//changePID

	// }
	// if(myTempData->sex != myTempData->sex_2){
	// 	//changePID

	// }
	// if(myTempData->shiny != myTempData->shiny_2){
	// 	//changePID

	// }

	// u8 genderRatio = getSpeciesBaseStats(myTempData->species_2)->genderRatio;
	// switch(myTempData->sex_2){
	// 	case GENDER_FEMALE:

	// }


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
	cmp r0, r1\nbne G_PID\n\
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

void showSprite(u8 id){
	u8 *sprite = getSprite(id);
	sprite[1] = 0;
}

void hideSprite(u8 id){
	u8 *sprite = getSprite(id);
	sprite[1] = 8;
}

void checkNmae(){
	u8 *name = (u8 *)BUFFER_2;
	u32 i = 0;
	while(TRUE){
		if (name[i] == 0xBA){
			name[i] = 0xFF;
			break;
		}
		i++;
	}
	if(StringCompare(BUFFER_2+i+1,BUFFER_2) != 0)
		return;

	u8 *speciesName = (u8 *) getMonSpeciesName(myTempData->attackBuffer);
	struct Pokemon* party = getCurrentPartyplayer();
	u8 *nickName = party->nickname;
	for (u32 n = 0; n < 0xB; n++){
		nickName[n] = speciesName[n];
	}
}

void set_poke_dex(u16 species){
	u16 index = SpeciesToNationalPokedexNum(species);
	GetSetPokedexFlag(index,2); //图鉴设置已发现的标识
	GetSetPokedexFlag(index,3); //图鉴设置已捕获的标识
}

void get_pos(){
	u32 *pos = (u32 *)(gSprites+0x20);
	myTempData->pos_buffer = pos[0];
}

bool8 check_pos(){
	u32 *pos = (u32 *)(gSprites+0x20);
	return pos[0] != myTempData->pos_buffer;
}

void del_last_keyitem(){
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

bool8 check_802(){
	u32 gBaseStats = ((u32*)gBaseStats_Pointer)[0];
	return gBaseStats == 0x08F186E0;

	// asm("push {lr}\n\
	// mov r0, #0\n\
	// ldr r1, basestat_table_802\n\
	// ldr r1, [r1]\n\
	// ldr r2, Emerald_802_ver\n\
	// cmp r1, r2\n\
	// bne check_802_end\n\
	// mov r0, #0x1\n\
	// check_802_end:\n\
	// pop {pc}\n\
	// .align 2\n\
	// Emerald_802_ver:\n\
	// .word 0x08F186E0\n\
	// basestat_table_802:\n\
	// .word 0x080001BC");
}
bool8 check_Ultra_Emerald(){
	u32 ultraEmerald = ((u32*)0x080BB100)[0];
	return ultraEmerald == 0x09E0FF80;

	// asm("push {lr}\n\
	// mov r0, #0x1\n\
	// ldr r1, Ultra_Emerald\n\
	// ldr r1, [r1]\n\
	// ldr r2, Ultra_Emerald_ver\n\
	// cmp r1, r2\n\
	// beq is_Ultra_Emerald\n\
	// mov r0, #0\n\
	// is_Ultra_Emerald:\n\
	// pop {pc}\n\
	// .align 2\n\
	// Ultra_Emerald:\n\
	// .word 0x080BB100\n\
	// Ultra_Emerald_ver:\n\
	// .word 0x09E0FF80");
}

void reset_IVs_buffer(){
	u16 *eviv = (u16 *)&myTempData->hp;
	eviv[0] = 0;
	eviv[1] = 0;
	eviv[2] = 0;
}

void select_set_p(){
	u8 *option = &myTempData->hp;
	option[myTempData->select-1] = !option[myTempData->select-1];
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

void shiye(){
	 struct SaveBlock1 *sav1 = (struct SaveBlock1*)((u32*)gSaveBlock1Ptr)[0];
	 sav1->flashLevel = 0;
	 u8 *pyramidFlag = (u8 *)(((u32*)gSaveBlock2Ptr)[0]+0x0E68);
	 if(pyramidFlag[0] != 0){
         pyramidFlag[0] = 0xC0;
	 }
}

bool32 check_font(){
    u16 flag = myTempData->hp*0x100+myTempData->attack;
    return flag < 0x1E28;

//	asm("push {lr}\nldr r0, buffer3_check_font\nldrb r1, [r0,#0x1A]\nlsl r1, #0x8\nldrb r2, [r0,#0x1B]\nadd r1, r2\nmov r2, #0x1E\nlsl r2, #0x8\nadd r2, #0x2B\nmov r0, #1\ncmp r1, r2\nbcc check_font_end\nmov r0, #0\ncheck_font_end:\npop {pc}\n.align 2\nbuffer3_check_font:\n.word 0x02021EC4");
}

void reset_ff_buffer2_add10(){
    u32 *buffer2_0x10 = (u32 *)(BUFFER_2+0x10);
    for (u8 i=0;i<4;i++){
        buffer2_0x10[i] = -1;
    }
}

u16 check_pw(){
	u8 penWuFlag = ((u8 *)0x080FE0CB)[0];
	if(penWuFlag == 6){
		return 0xFF;
	}
	else{
		return 0xFFFF;
	}
}