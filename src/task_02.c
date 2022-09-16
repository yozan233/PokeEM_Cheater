#include "header/funcs.h"
//flags for buttons3_new_remapped:1=A,2=B,4=SELECT,8=START,0x10=RIGHT,0x20=LEFT,0x40=UP,0x80=DOWN,0x100=L,0x200=R
extern struct rbox_short rbox_table[];
//const char pokemonstring[] = {0x04,0xC6,0x04,0xC6,0xFF};
extern void set_text(u8 m);
extern void resetData();
extern void get_attackN();
extern void get_ball_addr();
extern u32 get_attackName();
extern u16 get_ballNum();
extern u32 get_player_name_offset();
extern u32 lvl2exp();
extern u16 getbuffer();
extern void box_draw(u8,u8);
void aborter(u8 task_id);
void buttonbox_print(u32 str);
extern void print_text0(u8 pos_x, u8 pos_y, u8 *str);
void button_left();
void button_right();
void button_up();
void button_down();
void mouse_color();
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
					play_sound(5);
					if(strbData->over == 0){
						if(strbData->mode == 0){
							switch (strbData->select)
							{
							case 0:
								strbData->mode = 0x10;
								strbData->party = 0;
								strbData->modebuffer = 1;
								set_7();
								setData();
								showicon(0);
								buttonbox_print(text_table+0x13E);
								updatetext();

								break;
							case 1:
								strbData->mode = 0x20;
								strbData->Num = 1;
								strbData->attackBuffer = 1;
								strbData->modebuffer = 1;
								reset_IVs_buffer();
								strbData->hp = 1;
								mouseXY->pos_x = 0x5A;
								mouseXY->pos_y = 0x2C;
								buttonbox_print(text_table+0x24);
								updatetext();
								break;
							case 2:
								open_p8();
							default:
								break;
							}
							
						}
						else if (strbData->mode == 0x16 || strbData->mode == 0x31){
							shuru_A();
						}
						else if(strbData->mode >= 0x10&&strbData->mode < 0x20){
							if(strbData->select < 7){
								mouse_color();
								strbData->over = 1;
								if((strbData->mode == 0x10 && strbData->select > 2) || strbData->select == 0||strbData->mode == 0x11)
									buttonbox_print(text_table+0x163);
								else
									buttonbox_print(text_table+0x161);
							}
							else if(strbData->select == 7){
									if(strbData->mode == 0x11){
										get_ball_addr();
										struct Time *getTime = (struct Time *)0x03005cf8;
										strbData->SP_attack = getTime->hours;
									}
									if(strbData->mode == 0x14)
										get_attackN();
									if (strbData->mode == 0x15)
										strbData->attackBuffer = strbData->species;
									updatetext();
							}
							else if(strbData->select == 8){
								mouse_wait();
								if(strbData->egg){
									u16 spe = strbData->species;
									if(spe == 0x19C)
										spe = umodsi3(rng(),0xFB)+1;
									struct get_a_u8 *egg_lvl = (struct get_a_u8 *)0x08070A38;
									pokemon_make_wrapper(get_party_offset(),spe,egg_lvl->bit,32,1,rng() | (rng() << 0x10),0,strbData->TID);
									strbData->Num = 0;
									set_attributes(get_party_offset(),0x24,&strbData->Num);
									setData();
									strbData->modebuffer = 1;
									updatetext();
								}
								else
								{
									if(strbData->lvl != strbData->lvl_2)
										set_attributes(get_party_offset(),0x19,lvl2exp(strbData->lvl));
									set_att();
									if(strbData->mode == 0x10){
										if(chck_PID()){
											change_pid();
										}
										resetData(1);
									}
									if(strbData->mode == 0x11){
										u32 mTid = get_trainerID();
										if(strbData->hp == 0xFF){
											if(strbData->TID == mTid){
												strbData->TID -= 10;
												chck_PID();change_pid();
												resetData(1);
											}
										}
										else{
											if(strbData->TID != mTid){
												strbData->TID = mTid;
												chck_PID();change_pid();
												resetData(1);
											}
											set_attributes(get_party_offset(),0x7,get_player_name_offset());
										}
										struct Time *getTime = (struct Time *)0x03005cf8;
										u8 t = getTime->hours;
										if (t != strbData->SP_attack){
											RtcInitLocalTimeOffset(strbData->SP_attack,0);//设置时间
										}
										if(strbData->SP_defence){
											u32 r = GiveMonToPlayer(get_party_offset());
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
										set_attributes(get_party_offset(),0x50,&strbData->ability);
										// strbData->Num = strbData->hp;
										set_attributes(get_party_offset(),0x23,&strbData->hp);
										if(strbData->attackBuffer)
											set_attributes(get_party_offset(),0x26,&strbData->attackBuffer);
										if(strbData->speed){
											oak_fade(0xFFFFFFFF,0,0,0x10,0);
											heals_pokemom();
											task_del(task_id);
											rboxes_free();
											free(*malloc_pointer_loc);
											struct fly **fly_p = (struct fly **)0x08122C80;
											(*fly_p) += (strbData->speed-1);
											SetWarpDestination((*fly_p)->bank, (*fly_p)->map, 255, (*fly_p)->pos_x, (*fly_p)->pos_y);
											DoWarp();
											ResetInitialPlayerAvatarState();

										}
										
									}
									if(strbData->mode == 0x14){
										set_attributes(get_party_offset(),strbData->attackSelect+0xD,&strbData->attackBuffer);
										updatetext();
									}
									if(strbData->mode == 0x15){
										checkNmae();
										set_poke_dex(strbData->attackBuffer);
										set_attributes(get_party_offset(),0xB,&strbData->attackBuffer);
										strbData->Num = 2;
										set_attributes(get_party_offset(),0x3,&strbData->Num);
										setData();
										updatetext();
									}
									calculate_stats_pokekmon(get_party_offset());
								}

								
							}
							
						}
						else if(strbData->mode == 0x20){
							if(strbData->select <= 2){
								mouse_color();
								strbData->over = 1;
								buttonbox_print(text_table+0x161);
							}
							if(strbData->select == 8){
								updatetext();
								mouse_wait();
								if(strbData->Num&&strbData->hp){
									u32 additemtext = text_table+0x1BC;
									if(additem(strbData->attackBuffer,strbData->Num))
										additemtext -= 0x9;
									print_text0(120,88,additemtext);//添加成功
								}
								if(strbData->attack){
									del_last_keyitem();
								}
								
							}
							if(strbData->select == 3){
								strbData->hp = !strbData->hp;
								updatetext();
							}
							if(strbData->select == 4){
								strbData->attack = !strbData->attack;
								updatetext();
							}
							if(strbData->select == 7){
								strbData->Num = 0;
								strbData->attackBuffer = 1;
								strbData->hp = 1;
								strbData->attack = 0;
								updatetext();
							}

						}
						if(strbData->mode == 0x30){
							if(strbData->select <= 6){
								if(strbData->select == 2){
									mouse_color();
									strbData->over = 1;
									buttonbox_print(text_table+0x161);
								}
								else
								{
									select_set_p();
									updatetext();
								}
								
								
							}
							else if(strbData->select == 7){
								ldr_var4021();
								reset_IVs_buffer();
								updatetext();
							}
							else{
								mouse_wait();
								if(strbData->hp){
									setflag(0x896);
									special_0x1F3();
								}
								if(strbData->SP_attack){
									setvar(0x4024,strbData->PID&0xFFFF);
								}
								if(strbData->defence){
									set_bingdu();
								}
								// if(strbData->attack){
									setvar(0x4021,strbData->species);
								// }
								if(strbData->speed){
									// setflag(0x888);
									shiye();
								}
								struct get_a_u8 *cq = (struct get_a_u8 *)0x020322d6;
								cq->bit = strbData->SP_defence;

							}
							

						}
						
					}
					return;
				case BUTTONS_B:
					if (super->buttons3_new_remapped != BUTTONS_B)
						return;
					if(strbData->over == 0){
						if((strbData->mode == 0x16||strbData->mode == 0x31)&&strbData->sex == 1)
						{
							delete_zi();
						}
						else{
							play_sound(5);
							if(strbData->mode == 0){
								oak_fade(0xFFFFFFFF,0,0,0x10,0);
								heals_pokemom();
								break;
							}
							else{
								if(strbData->mode < 0x20){
									showpokepic(8);
									showicon(8);
									mouseXY->pos_x = 0x2E;
									strbData->select = 0;
								}
								else if(strbData->mode == 0x20){
									showitempic(8);
									mouseXY->pos_x = 0x7A;
									strbData->select = 1;
								}
								else{
									mouseXY->pos_x = 0xC6;
									strbData->select = 2;
								}
								
								mouseXY->pos_y = 0x4C;
								buttonbox_print(text_table);
								strbData->mode = 0;
								updatetext();
							}
							
						}
					}
					else{
						play_sound(5);
						mouse_color();
						strbData->over = 0;
						if(strbData->mode != 0x20)
							buttonbox_print(text_table+0x13E);
						else
							buttonbox_print(text_table+0x24);
					}
					return;
				case BUTTONS_SELECT:
					if (super->buttons3_new_remapped != BUTTONS_SELECT)
						return;
					if(strbData->mode == 0x13||strbData->mode == 0x16||strbData->mode == 0x31){
						strbData->sex = !strbData->sex;
						updatetext();
					}
					return;
				case BUTTONS_START:
					if (super->buttons3_new_remapped != BUTTONS_START)
						return;
					if(strbData->select != 8 && strbData->over == 0){
						play_sound(5);
						set_8();
					}
					return;
				case BUTTONS_RIGHT:
					get_pos();
					button_right();
					if(check_pos())
						play_sound(5);
					return;
				case BUTTONS_LEFT:
					get_pos();
					button_left();
					if(check_pos())
						play_sound(5);
					return;
				case BUTTONS_UP:
					get_pos();
					button_up();
					if(check_pos())
						play_sound(5);
					return;
				case BUTTONS_DOWN:
					get_pos();
					button_down();
					if(check_pos())
						play_sound(5);
					return;
				case BUTTONS_R:
					if (super->buttons3_new_remapped != BUTTONS_R)
						return;
					if(strbData->mode > 0&&strbData->mode < 0x20&&strbData->over==0 && !strbData->egg){
						if(strbData->mode == 0x16){
							shuru_R_1();
							
						}
						else
						{
							play_sound(6);
							strbData->mode ++;
							if(strbData->mode == 0x11){
								get_ball_addr();
								struct Time *getTime = (struct Time *)0x03005cf8;
								strbData->SP_attack = getTime->hours;
							}
							if(strbData->mode == 0x13){
								strbData->sex = 0;
							}
							if(strbData->mode == 0x14){
								strbData->attackSelect = 0;
								mouseXY->pos_x = 0x66;
								mouseXY->pos_y = 0x28;
								strbData->select = 1;
								get_attackN();
							}
							if(strbData->mode == 0x15){
								strbData->attackBuffer = strbData->species;
								strbData->select = 4;
								strbData->attackSelect = 3;
								mouseXY->pos_x = 0x86;
								mouseXY->pos_y = 0x5E;
							}
							if(strbData->mode == 0x16){
								showpokepic(8);
								open_shuru();
							}
							
							strbData->modebuffer = 1;
							updatetext();
						}
					}
					else if(strbData->mode == 0x30&&strbData->over==0)
					{
						play_sound(6);
						open_shuru();
						strbData->modebuffer = 1;
						strbData->mode ++;
						updatetext();
					}
					else if (strbData->mode == 0x31)
					{
						if(strbData->sex&&strbData->over==0){
							shuru_R_1();
						}
					}
					
					
					return;
				case BUTTONS_L:
					if (super->buttons3_new_remapped != BUTTONS_L)
						return;
					if(strbData->mode > 0x10&&strbData->mode <= 0x16&&strbData->over==0 && !strbData->egg){
						if(strbData->mode == 0x16 && strbData->sex == 1){
							shuru_L_1();
							
						}
						else
						{
							play_sound(6);
							strbData->mode --;
							if(strbData->mode == 0x11){
								get_ball_addr();
								struct Time *getTime = (struct Time *)0x03005cf8;
								strbData->SP_attack = getTime->hours;
							}
							if(strbData->mode == 0x13){
								set_7();
								strbData->sex = 0;
							}
							if(strbData->mode == 0x14){
								mouseXY->pos_x = 0x66;
								get_attackN();
								showpokepic(8);
							}
							if(strbData->mode == 0x15){
								strbData->attackBuffer = strbData->species;
								set_7();
								setData();
							}
							strbData->modebuffer = 1;
							updatetext();
							
						}
					}
					else if (strbData->mode == 0x31&&strbData->over==0)
					{
						if(strbData->sex)
						{
							shuru_L_1();
						}
						else
						{
							strbData->modebuffer = 1;
							play_sound(6);
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
	if(strbData->over == 0){
		if(strbData->mode == 0){//mode=0
			if(strbData->select>0){
			mouseXY->pos_x -= 0x4C;
			strbData->select--;
			}
			else{
				mouseXY->pos_x = 0xC6;
				strbData->select = 2;
			}
		}
		else if(strbData->mode < 0x14){//mode=1,2,3
			if(umodsi3(strbData->select+0x10,2) == 0 && strbData->select != 0){
				if(strbData->select <= 6){
					mouseXY->pos_x -= 0x5A;
					strbData->select -= 1;
				}
				else if(!strbData->egg){
					strbData->select = 5;
					mouseXY->pos_x = 0x6C;
					mouseXY->pos_y = 0x64;
				}
				
			}
			else if(strbData->select == 7){
					set_8();
				}
		}
		else if(strbData->mode == 0x14){//mode=4
			if(strbData->select == 8){
					strbData->select = strbData->attackSelect+1;
					mouseXY->pos_x = 0x66;
					mouseXY->pos_y = 0x28+strbData->attackSelect*18;
				}
			if(strbData->select == 7){
				set_8();
			}
		}
		else if (strbData->mode == 0x15){//mode=5
			if(strbData->select == 8){
					strbData->select = 4;
					mouseXY->pos_x = 0x86;
					mouseXY->pos_y = 0x5E;
				}
			if(strbData->select == 7){
				set_8();
			}
		}
		else if (strbData->mode == 0x16){
			shuru_left_0();
		}
		else if(strbData->mode == 0x20&&strbData->select > 1){
			if(strbData->select < 7 || strbData->select == 8){
				strbData->select = 1;
				mouseXY->pos_x = 0x5A;
				mouseXY->pos_y = 0x2C;
			}
			else{
				set_8();
			}
			
		}
		else if(strbData->mode == 0x30){
			if (umodsi3(strbData->select + 0x10, 2) == 0){
				if (strbData->select <= 6){
					mouseXY->pos_x -= 0x60;
					strbData->select -= 1;
				}
				else{
					strbData->select = 5;
					mouseXY->pos_x = 0x66;
					mouseXY->pos_y = 0x60;
				}
			}
			else if (strbData->select == 7){
				set_8();
			}
		}
		else if (strbData->mode == 0x31)
		{
			shuru_left_0();
		}
		
		
		
	}
	else if(strbData->mode == 0x12 || strbData->mode == 0x13){
			u8 temp;
			switch(strbData->select){
				case 1: temp = strbData->hp;
						if(temp>10)
							strbData->hp-=10;
						else
							strbData->hp = 0;
						break;
				case 2: temp = strbData->speed;
						if(temp>10)
							strbData->speed-=10;
						else
							strbData->speed = 0;
						break;
				case 3: temp = strbData->attack;
						if(temp>10)
							strbData->attack-=10;
						else
							strbData->attack = 0;
						break;
				case 4: temp = strbData->SP_attack;
						if(temp>10)
							strbData->SP_attack-=10;
						else
							strbData->SP_attack = 0;
						break;
				case 5: temp = strbData->defence;
						if(temp>10)
							strbData->defence-=10;
						else
							strbData->defence = 0;
						break;
				case 6: temp = strbData->SP_defence;
						if(temp>10)
							strbData->SP_defence-=10;
						else
							strbData->SP_defence = 0;
				default: break;
			}
			if(temp)
				updatetext();
	}
	else if(strbData->mode == 0x10){
		switch(strbData->select){
			case 1:
				if(strbData->lvl > 10){
					strbData->lvl-=10;
					updatetext();
				}
				else if(strbData->lvl){
					strbData->lvl = 0;
					updatetext();
				}
				break;
			case 2:
				if(strbData->happiness > 10){
						strbData->happiness-=10;
						updatetext();
				}
				else if(strbData->happiness){
					strbData->happiness = 0;
					updatetext();
				}
				
			default :break;
		}
	}
	else if(strbData->mode == 0x14 || strbData->mode == 0x15){
		mode_4_left();
	}
	else if(strbData->mode == 0x20){
		if(strbData->select == 2){
			u16 numt = strbData->Num;
			if(numt<10)
				strbData->Num = 0;
			else
				strbData->Num -= 10;
			if(numt)
				updatetext();
		}
		else{
			u16 t = getbuffer(7);
			if(t){
				strbData->attackBuffer = getbuffer(0);
				updatetext();
			}
		}
	}
	else if(strbData->mode == 0x30)
		{
			u16 bus = strbData->species;
			if(bus>100)
				strbData->species-=100;
			else
				strbData->species = 0;
			if(bus)
				updatetext();
		}
	
	
	
}
void button_right()
{
	if(strbData->over == 0){
		if(strbData->mode == 0){
			if(strbData->select<2){
			mouseXY->pos_x += 0x4C;
			strbData->select++;
			}
			else{
				mouseXY->pos_x = 0x2E;
				strbData->select = 0;
			}
		}
		else if(strbData->mode < 0x14){
			if(umodsi3(strbData->select+0x10,2) != 0&&strbData->select <= 6){
				mouseXY->pos_x += 0x5A;
				strbData->select += 1;
			}
			else if(strbData->select == 8){
				set_7();
			}
		}
		else if(strbData->mode == 0x14 || strbData->mode == 0x15){
			if(strbData->select < 7){
				set_8();
			}
			else if(strbData->select = 8){
				set_7();
			}
		}
		else if (strbData->mode == 0x16){
			shuru_right_0();
			
			
		}
		else if(strbData->mode == 0x20){
			if(strbData->select == 1){
				strbData->select = 2;
				mouseXY->pos_x = 0xBE;
			}
			if(strbData->select == 8){
				set_7();
			}
		}
		else if(strbData->mode == 0x30){
			if(umodsi3(strbData->select+0x10,2) != 0&&strbData->select <= 6){
				mouseXY->pos_x += 0x60;
				strbData->select += 1;
			}
			else if(strbData->select == 8){
				set_7();
			}
		}
		else if (strbData->mode == 0x31)
		{
			shuru_right_0();
		}
		
		
	}
	else if(strbData->mode == 0x12 || strbData->mode == 0x13){
			u8 temp,max=31;
			if(strbData->mode == 0x12)
				max = 31;
			else{
				if (strbData->sex){
					max = 85;
				}
				else{
					max = 255;
				}
				
				
			}
			u8 addnum;
			u32 ut = max*6;
			u32 sum = strbData->hp+strbData->speed+strbData->attack+strbData->SP_attack+strbData->defence+strbData->SP_defence;
			if(ut ==510&&ut-sum < 10){
				addnum = ut-sum;
			}
			else{
				addnum = 10;
			}
			
			switch(strbData->select){
				case 1: temp = strbData->hp;
						if(max == 85){
								max = temp+(ut-sum);
								if(max>255)
									max=255;
							}
						if(temp<=max-addnum)
							strbData->hp+=addnum;
						else
							strbData->hp = max;
						break;
				case 2: temp = strbData->speed;
						if(max == 85){
								max = temp+(ut-sum);
								if(max>255)
									max=255;
							}
						if(temp<=max-addnum)
							strbData->speed+=addnum;
						else
							strbData->speed = max;
						break;
				case 3: temp = strbData->attack;
						if(max == 85){
								max = temp+(ut-sum);
								if(max>255)
									max=255;
							}
						if(temp<=max-addnum)
							strbData->attack+=addnum;
						else
							strbData->attack = max;
						break;
				case 4: temp = strbData->SP_attack;
						if(max == 85){
								max = temp+(ut-sum);
								if(max>255)
									max=255;
							}
						if(temp<=max-addnum)
							strbData->SP_attack+=addnum;
						else
							strbData->SP_attack = max;
						break;
				case 5: temp = strbData->defence;
						if(max == 85){
								max = temp+(ut-sum);
								if(max>255)
									max=255;
							}
						if(temp<=max-addnum)
							strbData->defence+=addnum;
						else
							strbData->defence = max;
						break;
				case 6: temp = strbData->SP_defence;
						if(max == 85){
								max = temp+(ut-sum);
								if(max>255)
									max=255;
							}
						if(temp<=max-addnum)
							strbData->SP_defence+=addnum;
						else
							strbData->SP_defence = max;
				default: break;
			}
			if(temp<max&&sum != ut)
				updatetext();
	}
	else if(strbData->mode == 0x10){
		u8 max;
		if(strbData->select==1)
		{
			// max = 100;
			max = strbData->maxLvl;
		}
		else
			max = 255;
		switch(strbData->select){
			case 1:
				if(strbData->lvl < max-10){
					strbData->lvl+=10;
					updatetext();
				}
				else if(strbData->lvl != max){
					strbData->lvl = max;
					updatetext();
				}
				break;
			case 2:
				if(strbData->happiness < max-10){
					strbData->happiness+=10;
					updatetext();
				}
				else if(strbData->happiness != max){
					strbData->happiness = max;
					updatetext();
				}
				
			default :break;
		}
	}
	else if (strbData->mode == 0x14)
	{
		mode_4_right();
	}
	else if (strbData->mode == 0x15){
		u8 ft = 1;
		while (ft<=4){
			u16 pmax = pokeMax->max;
			if(check_802())
				pmax-=2;
			if(strbData->attackBuffer+ft > pmax)
				break;
			else
				ft++;
		}
		if(ft != 1){
			strbData->attackBuffer+=(ft-1);
			updatetext();
		}
	}
	else if(strbData->mode == 0x20){
		if(strbData->select == 2){
			u16 numt = strbData->Num;
			if(numt>89)
				strbData->Num = 99;
			else
				strbData->Num += 10;
			if(numt<99)
				updatetext();
		}
		else{
			u16 t = getbuffer(7);
			if(t < 6){
				strbData->attackBuffer = getbuffer(6);
				updatetext();
			}
		}
	}
	else if(strbData->mode == 0x30)
		{
			u16 bus = strbData->species;
			u16 var4021 = check_pw();
			if(bus<var4021-100)
				strbData->species+=100;
			else
				strbData->species = var4021;
			if(bus!=var4021)
				updatetext();
		}

	
	
	
}
void button_up()
{
	if(strbData->over == 0){
		if(strbData->mode > 0 && strbData->mode < 0x14){
			if(strbData->select > 2){
				if(strbData->egg){
						strbData->select = 0;
						mouseXY->pos_x = 0x8C;
						mouseXY->pos_y = 0x14;
					}
				else
				{
					if(strbData->select != 7){
					mouseXY->pos_y -= 0x18;
					strbData->select -= 2;
					}
					else{
						strbData->select = 6;
						mouseXY->pos_x = 0xC6;
						mouseXY->pos_y = 0x64;
					}
				}
			}
			else if(strbData->select != 0){
				strbData->select = 0;
				mouseXY->pos_x = 0x8C;
				mouseXY->pos_y = 0x14;
			}
			
		}
		else if(strbData->mode == 0x14){
			if (strbData->select != 1){
				if (strbData->select <= 4){
					mouseXY->pos_y -= 18;
					strbData->select -= 1;
					strbData->attackSelect--;
					strbData->modebuffer = 1;
					get_attackN();
					updatetext();
				}
				else{
					strbData->select = strbData->attackSelect+1;
					mouseXY->pos_x = 0x66;
					mouseXY->pos_y = 0x28+strbData->attackSelect*18;
				}
			}
		}
		else if (strbData->mode == 0x15 && strbData->select > 4){
			strbData->select = 4;
			mouseXY->pos_x = 0x86;
			mouseXY->pos_y = 0x5E;
					
		}
		else if(strbData->mode == 0x16){
			shuru_up_0();
		}
		else if(strbData->mode == 0x20&&strbData->select > 2){
			if(strbData->select <= 4){
				mouseXY->pos_y -= 0x18;
				strbData->select--;
			}
			else{
				strbData->select = 4;
				mouseXY->pos_x = 0xBE;
				mouseXY->pos_y = 0x5C;
			}
		}
		else if(strbData->mode == 0x30){
			if(strbData->select>2){
				if (strbData->select != 7){
					mouseXY->pos_y -= 0x1C;
					strbData->select -= 2;
				}
				else{
					strbData->select = 6;
					mouseXY->pos_x = 0xC6;
					mouseXY->pos_y = 0x60;
				}
			}
		}
		else if (strbData->mode == 0x31)
		{
			shuru_up_0();
		}
		
		
		
		
	}
	else if(strbData->mode == 0x12 || strbData->mode == 0x13){
			u8 temp,max;
			if(strbData->mode == 0x12)
				max = 31;
			else{
				if (strbData->sex){
					max = 85;
				}
				else{
					max = 255;
				}
				
				
			}
			u32 sum = strbData->hp+strbData->speed+strbData->attack+strbData->SP_attack+strbData->defence+strbData->SP_defence;
			u32 ut = max*6;
			if(sum<ut)
				switch(strbData->select){
					case 0:
						set_pat_u();
						break;
					case 1: temp = strbData->hp;
							if(max == 85){
								max = temp+(ut-sum);
								if(max>255)
									max=255;
							}
							if(temp<max)
								strbData->hp++;
							break;
					case 2: temp = strbData->speed;
							if(max == 85){
								max = temp+(ut-sum);
								if(max>255)
									max=255;
							}
							if(temp<max)
								strbData->speed++;
							break;
					case 3: temp = strbData->attack;
							if(max == 85){
								max = temp+(ut-sum);
								if(max>255)
									max=255;
							}
							if(temp<max)
								strbData->attack++;
							break;
					case 4: temp = strbData->SP_attack;
							if(max == 85){
								max = temp+(ut-sum);
								if(max>255)
									max=255;
							}
							if(temp<max)
								strbData->SP_attack++;
							break;
					case 5: temp = strbData->defence;
							if(max == 85){
								max = temp+(ut-sum);
								if(max>255)
									max=255;
							}
							if(temp<max)
								strbData->defence++;
							break;
					case 6: temp = strbData->SP_defence;
							if(max == 85){
								max = temp+(ut-sum);
								if(max>255)
									max=255;
							}
							if(temp<max)
								strbData->SP_defence++;
					default: break;
				}
			if(temp<max&&sum != ut)
				updatetext();
	}
	else if(strbData->mode == 0x10){
		u8 max;
		if(strbData->select==1)
		{
			// max = 100;
			max = strbData->maxLvl;
		}
		else
			max = 255;
		switch(strbData->select){
			case 0:
				set_pat_u();
				break;
			case 1:
				if(strbData->lvl < max){
					strbData->lvl++;
					updatetext();
				}
				break;
			case 2:
				if(strbData->happiness < max){
						strbData->happiness++;
						updatetext();
				}
				break;
			case 3:
				if(strbData->nature<0x18){
					strbData->nature++;
					updatetext();
				}
				break;
			case 4:
				strbData->shiny = !strbData->shiny;
				updatetext();
				break;
			case 5:
				set_ability();
				updatetext();
				break;
			case 6:
				if(strbData->sex == 1 || strbData->sex == 2)
					strbData->sex = !(strbData->sex-1)+1;
				updatetext();
			default : break;
		}
	}
	else if (strbData->mode == 0x11)
	{
		switch (strbData->select)
		{
		case 0:
			set_pat_u();
			break;
		case 1: 
			if(strbData->attackN && (strbData->defence > 0)){
					strbData->defence --;
					if(strbData->defence)
						strbData->attackBuffer = get_ballNum(strbData->defence-1);
					else
						strbData->attackBuffer = 0;
					
					updatetext();
				}
			break;
		case 2:
			if(strbData->hp == 0xFF)
				strbData->hp = 0xD4;
			else
				strbData->hp --;
			updatetext();
			break;
		case 3:
			if(strbData->speed){
				strbData->speed --;
				updatetext();
			}
			break;
		case 4:
			//if(strbData->SP_attack){
				strbData->SP_attack --;
				if(strbData->SP_attack==255)
					strbData->SP_attack = 23;
				updatetext();
			//}
			break;
		case 5:
			strbData->SP_defence = !(strbData->SP_defence);
			updatetext();
			break;
		case 6:
			strbData->ability = !(strbData->ability);
			updatetext();
		default:
			break;
		}
	}
	else if(strbData->mode == 0x14 || strbData->mode == 0x15){
			if(strbData->attackBuffer > 1){
				strbData->attackBuffer--;
				// if(strbData->mode == 5)
				// 	set_poke_tile();
				updatetext();
			}
		}
		else if(strbData->mode == 0x16)
		{
			shuru_up_1();
		}
		else if(strbData->mode == 0x20){
			if(strbData->select == 1){
				u16 t = getbuffer(7);
				if(t){
					strbData->attackBuffer = getbuffer(t-1);
					updatetext();
				}
			}
			else if(strbData->Num<99){
				strbData->Num++;
				updatetext();
			}	
		}
		else if(strbData->mode == 0x30)
		{
			u16 var4021 = check_pw();
			if(strbData->species<var4021){
				strbData->species++;
				updatetext();
			}
			
		}
		else if (strbData->mode == 0x31)
		{
			shuru_up_1();
		}
		
		
		
		
}
void button_down()
{
	if(strbData->over == 0){
		if(strbData->mode > 0&&strbData->mode < 0x14){
			if(strbData->select < 7){
				if(strbData->select == 0){
					if(strbData->egg){
						set_8();
					}
					else
					{
						strbData->select = 1;
						mouseXY->pos_x = 0x6C;
						mouseXY->pos_y = 0x34;
					}
					
					
				}
				else if(strbData->select != 5){
					mouseXY->pos_y += 0x18;
					strbData->select += 2;
				}
				else{
					set_8();
				}
			}
		}
		else if(strbData->mode == 0x14){
			if(strbData->select < 4){
					mouseXY->pos_y += 18;
					strbData->select += 1;
					strbData->attackSelect++;
					strbData->modebuffer = 1;
					get_attackN();
					updatetext();
				}
				else if(strbData->select == 4){
					set_8();
				}
		}
		else if(strbData->mode == 0x15){
			if(strbData->select < 7){
				set_8();
			}
		}
		else if (strbData->mode == 0x16){
			shuru_down_0();
			
			
		}
		else if(strbData->mode == 0x20){
			if(strbData->select > 1&&strbData->select < 4){
				mouseXY->pos_y += 0x18;
				strbData->select++;
			}
			else if(strbData->select == 1||strbData->select == 4){
				set_8();
			}
		}
		else if(strbData->mode == 0x30){
			if(strbData->select < 7){
				if(strbData->select != 5){
					mouseXY->pos_y += 0x1C;
					strbData->select += 2;
				}
				else{
					set_8();
				}
			}
			
		}
		else if (strbData->mode == 0x31)
		{
			shuru_down_0();
		}
		
		
	}
	else if(strbData->mode == 0x12 || strbData->mode == 0x13){
			u8 temp;
			switch(strbData->select){
				case 0:
					set_pat_d();
					break;
				case 1: temp = strbData->hp;
						if(temp)
							strbData->hp--;
						break;
				case 2: temp = strbData->speed;
						if(temp)
							strbData->speed--;
						break;
				case 3: temp = strbData->attack;
						if(temp)
							strbData->attack--;
						break;
				case 4: temp = strbData->SP_attack;
						if(temp)
							strbData->SP_attack--;
						break;
				case 5: temp = strbData->defence;
						if(temp)
							strbData->defence--;
						break;
				case 6: temp = strbData->SP_defence;
						if(temp)
							strbData->SP_defence--;
				default: break;
			}
			if(temp)
				updatetext();
	}
	else if(strbData->mode == 0x10){
		switch(strbData->select){
			case 0:
				set_pat_d();
				break;
			case 1:
				if(strbData->lvl){
					strbData->lvl--;
					updatetext();
				}
				break;
			case 2:
				if(strbData->happiness){
						strbData->happiness--;
						updatetext();
				}
				break;
			case 3:
				if(strbData->nature){
					strbData->nature--;
					updatetext();
				}
				break;
			case 4:
				strbData->shiny = !strbData->shiny;
				updatetext();
				break;
			case 5:
				set_ability();
				updatetext();
				break;
			case 6:
				if(strbData->sex == 1 || strbData->sex == 2)
					strbData->sex = !(strbData->sex-1)+1;
				updatetext();
			default :break;
		}
	}
	else if (strbData->mode == 0x11)
	{
		switch (strbData->select)
		{
		case 0:
			set_pat_d();
			break;
		case 1:
			if(strbData->attackN && (strbData->defence < strbData->attackN)){
				strbData->defence ++;
				strbData->attackBuffer = get_ballNum(strbData->defence-1);
				updatetext();
			}
			break;
		case 2:
			if(strbData->hp == 0xD4)
				strbData->hp = 0xFF;
			else
				strbData->hp ++;
			updatetext();
			break;
		case 3:
			if(strbData->speed <= strbData->sex){
				strbData->speed ++;
				updatetext();
			}
		break;
		case 4:
			//if(strbData->SP_attack){
				strbData->SP_attack ++;
				if(strbData->SP_attack==24)
					strbData->SP_attack = 0;
				updatetext();
			//}
		break;
		case 5:
			strbData->SP_defence = !(strbData->SP_defence);
			updatetext();
			break;
		case 6:
			strbData->ability = !(strbData->ability);
			updatetext();
		default:
			break;
		}
	}
	else if(strbData->mode == 0x14){
			if(get_attackName(strbData->attackBuffer+1)){
				strbData->attackBuffer++;
				updatetext();
			}
		}
		else if (strbData->mode == 0x15)
		{
			u16 pmax = pokeMax->max;
			if(check_802())
				pmax-=2;
			if(strbData->attackBuffer < pmax){
				strbData->attackBuffer++;
				updatetext();
			}
			
		}
		else if (strbData->mode == 0x16)
		{
			shuru_down_1();


		}
		else if(strbData->mode == 0x20){
			if(strbData->select == 1){
				u16 t = getbuffer(7);
				if(t < 6){
					strbData->attackBuffer = getbuffer(t+1);
					updatetext();
				}
			}
			else if(strbData->Num){
				strbData->Num--;
				updatetext();
			}
			
		}
		else if(strbData->mode == 0x30 && strbData->species)
		{
			strbData->species--;
			updatetext();
		}
		else if (strbData->mode == 0x31)
		{
			shuru_down_1();
		}
		
		
		
	
}
void aborter(u8 task_id)
{
	if(((pal_fade_control->mix_color) >> 8 & 0x80))
		return;
	task_del(task_id);
	rboxes_free();
	free(*malloc_pointer_loc);
	set_callback2(c2_exit_to_overworld_1_continue_scripts_and_music);
	return;
}
void open_shuru(){
	set_7();
	reset_IVs_buffer();
	reset_ff_buffer2_add10();
	strbData->sex = 1;
	strbData->attack = 0xBB;
}
void shuru_down_0(){
	if(strbData->select == 1){
		strbData->select = 2;
		mouseXY->pos_x = 0xE2;
		mouseXY->pos_y = 0x58;
	}
	else if (strbData->select == 2){
		set_7();
	}
	else
	{
		if(strbData->select > 0xD7){
			strbData->select -= 10;
			mouseXY->pos_y += 0x10;
		}
	}
}
void shuru_down_1(){
	struct get_a_u8 *Aa = (struct get_a_u8 *)&strbData->attackN;
	switch (Aa->bit)
	{
	case 0xBB:
		strbData->hp = 0;
		strbData->attack = 0xBB;
		break;
	case 0xBC:
		strbData->hp = 1;
		strbData->attack = 0;
		break;
	case 0xBD:
		strbData->hp = 1;
		strbData->attack = 0x24;
		break;
	case 0xBE:
		strbData->hp = 1;
		strbData->attack = 0xDC;
		break;
	case 0xBF:
		strbData->hp = 2;
		strbData->attack = 0xCE;
		break;
	case 0xC0:
		strbData->hp = 3;
		strbData->attack = 0x8F;
		break;
	case 0xC1:
		strbData->hp = 3;
		strbData->attack = 0xA5;
		break;
	case 0xC2:
		strbData->hp = 4;
		strbData->attack = 0x2B;
		break;
	case 0xC4:
		strbData->hp = 4;
		strbData->attack = 0xC6;
		break;
	case 0xC5:
		strbData->hp = 5;
		strbData->attack = 0x84;
		break;
	case 0xC6:
		strbData->hp = 7;
		strbData->attack = 0xB4;
		break;
	case 0xC7:
		strbData->hp = 8;
		strbData->attack = 0x21;
		break;
	case 0xC8:
		strbData->hp = 9;
		strbData->attack = 0x22;
		break;
	case 0xC9:
		strbData->hp = 9;
		strbData->attack = 0xB9;
		break;
	case 0xCA:
		strbData->hp = 0xA;
		strbData->attack = 0x13;
		break;
	case 0xCB:
		strbData->hp = 0xA;
		strbData->attack = 0x1B;
		break;
	case 0xCC:
		strbData->hp = 0xA;
		strbData->attack = 0x95;
		break;
	case 0xCD:
		strbData->hp = 0xB;
		strbData->attack = 0x3B;
		break;
	case 0xCE:
		strbData->hp = 0xB;
		strbData->attack = 0x76;
		break;
	case 0xD1:
		strbData->hp = 0xC;
		strbData->attack = 0x9D;
		break;
	case 0xD2:
		strbData->hp = 0xD;
		strbData->attack = 0x42;
		break;
	case 0xD3:
		strbData->hp = 0xD;
		strbData->attack = 0xBA;
		break;
	case 0xD4:
		strbData->hp = 0xE;
		strbData->attack = 0xA2;
		break;
	case 0xB0:
		strbData->hp = 0xF;
		strbData->attack = 0xDD;
		break;
	
	
	default:
		break;
	}
	if(Aa->bit == 0xBB)
		strbData->defence = 0;
	if(Aa->bit != 0xA1)
		updatetext();
}
void shuru_up_0(){
	if(strbData->select == 7||strbData->select == 8)
	{
		strbData->select = 2;
		mouseXY->pos_x = 0xE2;
		mouseXY->pos_y = 0x58;
	}
	else if(strbData->select == 2){
		strbData->select = 1;
		mouseXY->pos_x = 0xE2;
		mouseXY->pos_y = 0x48;
	}
	else
	{
		if(strbData->select > 8&&strbData->select < 0xF6){
			strbData->select += 10;
			mouseXY->pos_y -= 0x10;
		}
	}
}
void shuru_up_1(){
	struct get_a_u8 *Aa = (struct get_a_u8 *)&strbData->attackN;
	switch (Aa->bit)
	{
	case 0xA1:
		strbData->hp = 1;
		strbData->attack = 0;
		break;
	case 0xBB:
		strbData->hp = 1;
		strbData->attack = 0x24;
		break;
	case 0xBC:
		strbData->hp = 1;
		strbData->attack = 0xDC;
		break;
	case 0xBD:
		strbData->hp = 2;
		strbData->attack = 0xCE;
		break;
	case 0xBE:
		strbData->hp = 3;
		strbData->attack = 0x8F;
		break;
	case 0xBF:
		strbData->hp = 3;
		strbData->attack = 0xA5;
		break;
	case 0xC0:
		strbData->hp = 4;
		strbData->attack = 0x2B;
		break;
	case 0xC1:
		strbData->hp = 4;
		strbData->attack = 0xC6;
		break;
	case 0xC2:
		strbData->hp = 5;
		strbData->attack = 0x84;
		break;
	case 0xC4:
		strbData->hp = 7;
		strbData->attack = 0xB4;
		break;
	case 0xC5:
		strbData->hp = 8;
		strbData->attack = 0x21;
		break;
	case 0xC6:
		strbData->hp = 9;
		strbData->attack = 0x22;
		break;
	case 0xC7:
		strbData->hp = 9;
		strbData->attack = 0xB9;
		break;
	case 0xC8:
		strbData->hp = 0xA;
		strbData->attack = 0x13;
		break;
	case 0xC9:
		strbData->hp = 0xA;
		strbData->attack = 0x1B;
		break;
	case 0xCA:
		strbData->hp = 0xA;
		strbData->attack = 0x95;
		break;
	case 0xCB:
		strbData->hp = 0xB;
		strbData->attack = 0x3B;
		break;
	case 0xCC:
		strbData->hp = 0xB;
		strbData->attack = 0x76;
		break;
	case 0xCD:
		strbData->hp = 0xC;
		strbData->attack = 0x9D;
		break;
	case 0xCE:
		strbData->hp = 0xD;
		strbData->attack = 0x42;
		break;
	case 0xD1:
		strbData->hp = 0xD;
		strbData->attack = 0xBA;
		break;
	case 0xD2:
		strbData->hp = 0xE;
		strbData->attack = 0xA2;
		break;
	case 0xD3:
		strbData->hp = 0xF;
		strbData->attack = 0xDD;
		break;
	case 0xD4:
		strbData->hp = 0x11;
		strbData->attack = 0x32;
		
	
	default:
		break;
	}
	strbData->defence = 2;
	if(Aa->bit != 0xB0)
		updatetext();
}
void shuru_right_0(){
	if(strbData->select <= 8){
		if(strbData->select == 8)
			set_7();
	}
	else{
		if(umodsi3((strbData->select),10)!=6){
			if(strbData->defence > 1)
				mouseXY->pos_x+=15;
			else
				mouseXY->pos_x+=12;
			strbData->select -= 1;
		}
		else{
			if(strbData->select>=0xEC)
			{
				strbData->select = 1;
				mouseXY->pos_x = 0xE2;
				mouseXY->pos_y = 0x48;
			}
			else if (strbData->select == 0xE2)
			{
				strbData->select = 2;
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
	if(strbData->select<=8){
		if(strbData->select == 7){
			set_8();
		}
		else{
			strbData->select = 0xFF;
			mouseXY->pos_x = 0x1C;
			mouseXY->pos_y = 0x3C;
		}
		
	}
	else{
		if(umodsi3((strbData->select),10)!=5){
			if(strbData->defence > 1)
				mouseXY->pos_x-=15;
			else
				mouseXY->pos_x-=12;
			strbData->select += 1;
		}
	}
}
void shuru_L_1(){
	if(strbData->defence > 1)
	{
		if(strbData->hp+strbData->attack>1)
		{
			if(strbData->attack<50)
			{
				if(strbData->hp>1){
					strbData->hp--;
					strbData->attack = 0xC8;
					if(strbData->hp == 6)
							strbData->hp = 5;
					if(strbData->hp == 0x1B)
						strbData->hp = 0x1A;
				}
				else{
					strbData->attack = 0;
				}
			}
			else
				strbData->attack -= 50;
			updatetext();
		}
		else
		{
			strbData->defence = 1;
			strbData->hp = 0;
			strbData->attack = 0xD5;
			set_7();
			updatetext();
		}
		
	}
	else if(strbData->defence == 1)
	{
		strbData->defence = 0;
		
		strbData->attack = 0xBB;
		set_7();
		updatetext();
	}
}
void shuru_R_1(){
	if(strbData->sex == 1){//
		if(strbData->defence > 1)
		{
			if(check_font()){
				strbData->attack += 50;
				if(strbData->attack >= 0xF7){
					strbData->attack = 0;
					strbData->hp++;
					if(strbData->hp == 6)
						strbData->hp = 7;
					if(strbData->hp == 0x1B)
						strbData->hp = 0x1C;
				}

				updatetext();
			}
		}
		else{
			strbData->defence++;
			set_7();
			if(strbData->defence == 1)
				strbData->attack = 0xD5;
			else{
				strbData->hp = 1;
				strbData->attack = 0;
			}
			updatetext();
		}
		
	}
}
void shuru_A(){
	if(strbData->select == 1){
		mouse_color();
		strbData->over = 1;
		buttonbox_print(text_table+0x163);
	}
	if(strbData->select == 2)
		{delete_zi();}
	if(strbData->select == 7)
	{
		strbData->speed = 0;
		reset_ff_buffer2_add10();
		updatetext();
	}
	if(strbData->select == 8){
		// mouse_wait();
		struct get_a_u8 *name_text = (struct get_a_u8 *)0x02021DD4;
		if(strbData->mode == 0x16)
		{
			if(name_text->bit != 0xFF)
				set_poke_name();
			strbData->Num = 2;
			set_attributes(get_party_offset(),0x3,&strbData->Num);

			play_sound(6);
			set_7();
			setData();
			strbData->attackBuffer = strbData->species;
			strbData->mode --;
			strbData->modebuffer = 1;
			updatetext();
		}
		else
		{
			if(name_text->bit != 0xFF)
				strcpy_xFF_terminated(get_player_name_offset(),0x02021DD4);
			// updatetext();
			play_sound(6);
			strbData->modebuffer = 1;
			open_p8();
		}
		
	}
	if(strbData->select > 8){
		struct get_a_u8 *text_n = (struct get_a_u8 *)0x02021DD4;
		struct font *text_f = (struct font *)0x02021DF4;
		u32 m = 2;
		if(strbData->defence < 2)
			m --;
		int name_len = 10;
		if(strbData->mode == 0x31)
			name_len = 7;
		if(strbData->speed <= name_len-m)
		{
			text_n += strbData->speed;
			strbData->speed += m;
			text_f += (0xFF-strbData->select);

			if(m == 2){
				text_n->bit = text_f->zi1;
				text_n++;
				text_n->bit = text_f->zi2;
			}
			else{
				text_n->bit = text_f->zi2;
			}

			updatetext();
		}
				
	}
}


void delete_zi(){
	if(strbData->speed)
	{
		struct get_a_u8 *text_nd = (struct get_a_u8 *)0x02021DD4;
		u32 dm = 0;
		if(strbData->speed > 1)
			dm = strbData->speed-2;
		text_nd += dm;
		
		dm = 1;
		if(text_nd->bit > 0&&text_nd->bit < 0x20)
			dm = 2;
		
		if(strbData->speed != 1)
			text_nd++;

		strbData->speed -= dm;

		
		
		while (dm)
		{
			text_nd->bit = 0xFF;
			text_nd--;
			dm--;
		}
		
		play_sound(3);
		strbData->modebuffer = 1;
		updatetext();
	}
}

void open_p8(){
	struct get_a_u8 *cq = (struct get_a_u8 *)0x020322d6;
	cq->bit = 0;
	strbData->mode = 0x30;
	strbData->modebuffer = 2;
	setData();
	reset_IVs_buffer();
	buttonbox_print(text_table+0x13E);
	ldr_var4021();
	updatetext();
	set_7();
}

void set_8(){
	strbData->select = 8;
	mouseXY->pos_x = 0xC6;
	mouseXY->pos_y = 0x7C;
}
void set_7(){
	strbData->select = 7;
	mouseXY->pos_x = 0xE2;
	mouseXY->pos_y = 0x7C;
}

void set_pat_d(){
	struct get_a_u8 *partyMax = (struct get_a_u8 *)0x020244E9;
	if(strbData->party<partyMax->bit-1){
		strbData->party++;
		setData();
		if(strbData->mode == 0x11)
			get_ball_addr();
		updatetext();
	}
}
void set_pat_u(){
	if(strbData->party){
		strbData->party--;
		setData();
		if(strbData->mode == 0x11)
			get_ball_addr();
		updatetext();
	}
}

void buttonbox_print(u32 str)
{
	u8 boxid_t = strbData->boxid;
	rboxid_fill_pixels(boxid_t,0x11);
	rboxid_print(boxid_t,1,str,6,0,0,0); //按键提示
}
void set_ability(){
	if(check_Ultra_Emerald())
	{
		switch (strbData->ability)
		{
		case 0:
			strbData->ability = 1;
			break;
		case 1:
			strbData->ability = 4;
			break;
		case 4:
			strbData->ability = 0;
		default:
			break;
		}
	}
	else
	{
		strbData->ability = !strbData->ability;
	}
	
}
void mode_4_right(){
	u8 rt = 1;
		while (rt<=4){
			if(!get_attackName(strbData->attackBuffer+rt))
				break;
			else
				rt++;
		}
		if(rt != 1){
			strbData->attackBuffer+=(rt-1);
			updatetext();
		}
		
}
void mode_4_left(){
	u8 rt = 1;
	while (rt<=4)
	{
		if(strbData->attackBuffer-rt < 1)
			break;
		else
			rt++;
		
	}
	if(rt != 1){
		strbData->attackBuffer-=(rt-1);
		updatetext();
	}
	
}
void updatetext(){
	if(strbData->modebuffer)
		strbData->modebuffer--;
	else
		play_sound(5);
	set_text(strbData->mode);
}
void mouse_wait(){
	mouse_color();
	pause();
	mouse_color();
}
void ldr_var4021(){
	u16 var4021 = get_var_value(0x4021);
	if(check_pw()==0xFF){
		var4021 = (u8)var4021;
	}
	strbData->species = var4021;
}


void mouse_color(){
	asm("push {lr}\nldr r2, OBJ_PaletteMem2\nadd r2, #0x16\nldrb r0, [r2]\nmov r1, #0x46\ncmp r0, r1\nbeq color_red\nstrb r1, [r2]\nmov r1, #0x65\nstrb r1, [r2,#0x1]\nb color_end\ncolor_red:\nmov r1, #0x9F\nstrb r1, [r2]\nmov r1, #0x10\nstrb r1, [r2,#0x1]\ncolor_end:\npop {pc}\n.align 2\nOBJ_PaletteMem2:\n.word 0x02037D14");
}
void set_att(){
	asm("push {r4-r5,lr}\nldr r5, buffer3_showpic\nldrb r1, [r5]\ncmp r1,#0x10\nbeq mode1\ncmp r1,#0x12\nbeq mode2or3\ncmp r1,#0x13\nbeq mode2or3\nb endx\nmode1:\nbl get_party\nadd r0, #0x1E\nmov r1, #0\nstrb r1, [r0]\nldrb r1, [r5,#0x16]\nmov r2, r5\nadd r2, #0x28\nstrh r1, [r2]\nmov r0, #0x2E\nbl setattr\nldrb r1, [r5,#0x17]\nmov r2, r5\nadd r2, #0x28\nstrh r1, [r2]\nmov r0, #0x20\nbl setattr\nb endx\nmode2or3:\nsub r1, #0x12\nadd r5, #0x1A\nmov r2, #0xD\nmov r4, #0x27\nmul r2, r1\nsub r4, r2\nreturn1:\nmov r0, r4\nldrb r1, [r5]\nldr r2, buffer3_showpic\nadd r2, #0x28\nstrh r1, [r2]\nbl setattr\nadd r4, #0x1\nadd r5, #0x1\nldr r0, buffer3_showpic\nadd r0, #0x20\ncmp r5, r0\nbne return1\nendx:\npop {r4-r5,pc}\nsetattr:\npush {lr}\nmov r3, r0\nbl get_party\nmov r1, r3\nldr r3, set_attributesa\nbl BX_R3\npop {pc}\nBX_R3:\nbx r3\n.align 2\nset_attributesa:\n.word 0x0806ACAD");
}
void set_poke_name(){
	asm("push {lr}\nbl get_party\nadd r0, #0x8\nmov r1, r0\nldr r0, buffer2_poke_name\nmov r2, #0x5\nswi #0xB\npop {pc}\n.align 2\nbuffer2_poke_name:\n.word 0x02021DD4");
}
void get_party_offset(){
	asm("get_party:\npush {lr}\nldr r1, buffer3_showpic\nadd r1, #0x10\nldrb r1, [r1]\nmov r0, #0x64\nmul r1, r0\nldr r0, party_playergt\nadd r0, r1\npop {pc}\n.align 2\nparty_playergt:\n.word 0x020244EC");
}
void pause(){
	asm("push {lr}\nmov r1, #0xFF\nlsl r1, #0xA\npause_t:\nadd r0, #0x1\ncmp r0, r1\nbne pause_t\npop {pc}");
}
void chck_PID(){
	asm("push {lr}\nldr r3, buffer3_pid\nldrb r2, [r3]\ncmp r2, #0x11\nbeq changePID\nmov r2, r3\nadd r2, #0x10\nadd r3, #0x30\nldrb r0, [r2,#0x9]\nldrb r1, [r3,#0x9]\ncmp r0, r1\nbne G_PID\nldrb r0, [r2,#0x5]\nldrb r1, [r3,#0x5]\ncmp r0, r1\nbne changePID\nldrb r0, [r2,#0x8]\nldrb r1, [r3,#0x8]\ncmp r0, r1\nbne changePID\nmov r0, #0x0\nb notChange\nG_PID:\nldrh r0, [r3,#0x2]\nldr r2, basestat_table_pid\nldr r2, [r2]\nmov r1, #0x1C\nmul r0, r1\nadd r0, r2\nadd r0, #0x10\nldrb r0, [r0]\nldrb r1, [r3,#0x9]\ncmp r1, #0x1\nbeq gXY\ncmp r1, #0x2\nbeq gXY\nb changePID\ngXY:\nsub r0, #0x5\ncmp r1, #0x2\nbeq isXX\nadd r0, #0xA\nisXX:\nsub r3, #0x10\nstrb r0, [r3]\nchangePID:\nldr r3, buffer3_pid\nmov r2, r3\nadd r2, #0x10\nadd r3, #0x40\nmov r0, #0xFF\nstrh r0, [r3,#0x4]\nldrb r0, [r2,#0x5]\nstrh r0, [r3,#0x2]\nldrb r0, [r2,#0x8]\nstrh r0, [r3,#0x6]\nldrb r0, [r2]\nstrh r0, [r3]\nmov r0, #0x1\nnotChange:\npop {pc}\n.align 2\nbuffer3_pid:\n.word 0x02021EC4\nbasestat_table_pid:\n.word 0x080001BC");
}
void showitempic(){
	asm("push {lr}\nldr r2, buffer3_showpic\nadd r2, #0x2E\nldrb  r1, [r2]\nmov r2, #0x44\nmul r1, r2\nldr r2, obj_showicon\nadd r1, r2\nstrb r0, [r1,#0x1]\npop {pc}");
}
void showpokepic(){
	asm("push {lr}\nldr r2, buffer3_showpic\nldrb  r1, [r2,#0xA]\nmov r2, #0x44\nmul r1, r2\nldr r2, obj_showicon\nadd r1, r2\nstrb r0, [r1,#0x1]\npop {pc}\n.align 2\nbuffer3_showpic:\n.word 0x02021EC4");
}
void showicon(){
	asm("push {lr}\nldr r2, v8004icon\nldrb  r1, [r2,#0x6]\nmov r2, #0x44\nmul r1, r2\nldr r2, obj_showicon\nadd r1, r2\nstrb r0, [r1,#0x1]\npop {pc}\n.align 2\nv8004icon:\n.word 0x020375E0\nobj_showicon:\n.word 0x02020630");
}
void checkNmae(){
	asm("push {r4-r5,lr}\nldr r0, buffer2_changeName\nmov r1, #0x1\nctnChck:\nadd r0, r1\nldrb r2, [r0]\ncmp r2, #0xBA\nbne ctnChck\nmov r1, #0xFF\nstrb r1, [r0]\nadd r0, #0x1\nldr r1, buffer2_changeName\nldr r3, strcmp\nbl BX_R3\ncmp r0, #0x0\nbne end_changeName\nldr r0, buffer3_changeName\nldrb r0, [r0,#0x10]\nldr r1, party_player_changeName\nmov r2, #0x64\nmul r0,r2\nadd r1,r0 @;r1精灵昵称地址\nadd r1, #0x8\nldr r0, buffer3_changeName\nldrh r0, [r0,#0x2C]\nldr r3, poke_na\nldr r3, [r3]\nmov r2, #0xB\nmul r0, r2\nadd r0, r3\n@mov r2, #0x5\n@swi #0Xb\nmov r3, #0x0\nstrbr1:\nldrb r2, [r0,r3]\nstrb r2, [r1,r3]\nadd r3, #0x1\ncmp r3,#0xB\nbne strbr1\nend_changeName:\npop {r4-r5,pc}\n.align 2\nbuffer3_changeName:\n.word 0x02021EC4\nparty_player_changeName:\n.word 0x020244EC\nbuffer2_changeName:\n.word 0x02021DC4\npoke_na:\n.word 0x08000144\nstrcmp:\n.word 0x8008C45");
}
void set_poke_dex(){
	asm("push {r4,lr}\nldr r3, get_pokedex_num\nbl BX_R3\nmov r4, r0\nmov r1, #0x2\nldr r3, get_or_set_pokedex_flags\nbl BX_R3\nmov r0, r4\nmov r1, #0x3\nldr r3, get_or_set_pokedex_flags\nbl BX_R3\npop {r4,pc}\n.align 2\nget_or_set_pokedex_flags:\n.word 0x080C0665\nget_pokedex_num:\n.word 0x0806D4A5");
}
void get_pos(){
	asm("push {lr}\nldr r1, posoffset\nldr r0, [r1]\nldr r1, posbuffer\nstr r0, [r1]\npop {pc}\n.align 2\nposoffset:\n.word 0x02020650\nposbuffer:\n.word 0x02021ED0");
}
void check_pos(){
	asm("push {lr}\nldr r1, posoffsetc\nldr r1, [r1]\nldr r2, posbufferc\nldr r2, [r2]\nmov r0, #0x1\ncmp r1, r2\nbne poscend\nmov r0, #0x0\nposcend:\npop {pc}\n.align 2\nposoffsetc:\n.word 0x02020650\nposbufferc:\n.word 0x02021ED0");
}
void del_last_keyitem(){
	asm("push {lr}\nldr r3, item_sav\nldr r0, [r3]\nldrh r1, [r3,#0x4]\nmov r3, #0x0\nitem_check:\nlsl r2, r3,#0x2\nadd r2, r0\nldrh r2, [r2]\ncmp r2, #0x0\nbeq item_check_end\nadd r3, #0x1\ncmp r3, r1\nbne item_check\nsub r3, #0x1\nlsl r2, r3,#0x2\nadd r2, r0\nmov r1, #0\nstr r1, [r2]\nb del_keyitem_end\nitem_check_end:\ncmp r3, #0x0\nbeq del_keyitem_end\nsub r3, #0x1\nlsl r2, r3,#0x2\nadd r2, r0\nldr r1, [r2,#0x4]\nstr r1, [r2]\ndel_keyitem_end:\npop {pc}\n.align 2\nitem_sav:\n.word 0x02039DD8+0x20");
}
void check_802(){
	asm("push {lr}\nmov r0, #0\nldr r1, basestat_table_802\nldr r1, [r1]\nldr r2, Emerald_802_ver\ncmp r1, r2\nbne check_802_end\nmov r0, #0x1\ncheck_802_end:\npop {pc}\n.align 2\nEmerald_802_ver:\n.word 0x08F186E0\nbasestat_table_802:\n.word 0x080001BC");
}
void check_Ultra_Emerald(){
	asm("push {lr}\nmov r0, #0x1\nldr r1, Ultra_Emerald\nldr r1, [r1]\nldr r2, Ultra_Emerald_ver\ncmp r1, r2\nbeq is_Ultra_Emerald\nmov r0, #0\nis_Ultra_Emerald:\npop {pc}\n.align 2\nUltra_Emerald:\n.word 0x080BB100\nUltra_Emerald_ver:\n.word 0x09E0FF80");
}
/* void party_max(){
	asm("push {lr}\nldr r0, pt_max\nldrb r0, [r0]\nsub r0,#1\npop {pc}\n.align 2\npt_max:\n.word  0x020244E9");
} */
void reset_IVs_buffer(){
	asm("push {lr}\nmov r0, #0\nldr r1, buffer3_IVs\nstrh r0, [r1]\nstrh r0, [r1,#0x2]\nstrh r0, [r1,#0x4]\npop {pc}\n.align 2\nbuffer3_IVs:\n.word 0x02021EC4+0x1A");
}
void select_set_p(){
	asm("push {lr}\nldr r3, buffer3_select_p\nldrb r0, [r3,#0x1]\nadd r3, r0\nadd r3, #0x19\nldrb r0, [r3]\nmov r1, #1\nneg r1, r0\nadc r0, r1\nstrb r0, [r3]\npop {pc}\n.align 2\nbuffer3_select_p:\n.word 0x02021EC4");
}
void setvar(){
	asm("push {r4,lr}\nmov r4, r1\nldr r3, get_var_address\nbl BX_R3\nstrh r4, [r0]\npop {r4,pc}\nbx r3\n.align 2\nget_var_address:\n.word  0x0809D649");
}
void set_bingdu(){
	asm("push {r4-r6,lr}\nldr r4, buffer3_bd\nmov r0, #0xF\nstrh r0, [r4]\nldr r5, party_playerbd\nmov r6,#0x0\nctn_set_bingdu:\nmov r0, r5\nmov r1,#0x22\nmov r2, r4\nldr r3, set_att_bd\nbl BX_R3\nadd r5, #0x64\nadd r6,#0x1\ncmp r6, #0x6\nbne ctn_set_bingdu\nmov r0, #0x1\npop {r4-r6,pc}\n.align 2\nbuffer3_bd:\n.word 0x02021EC4+0x28\nparty_playerbd:\n.word 0x020244EC\nset_att_bd:\n.word 0x0806ACAD");
}
void shiye(){
	asm("push {lr}\nldr r2, sav1\nldr r0, [r2]\nadd r0, #0x30\nmov r1, #0x0\nstrb r1, [r0]\nldr r0, [r2,#0x4]\nmov r1, #0xE\nlsl r1, #0x8\nadd r0, r1\nadd r0, #0x68\nmov r1, #0\nldrb r2, [r0]\ncmp r2, #0\nbeq not_jin\nmov r1, #0xC0\nnot_jin:\nstrb r1, [r0]\npop {pc}\n.align 2\nsav1:\n.word 0x03005D8C");
}
void check_font(){
	asm("push {lr}\nldr r0, buffer3_check_font\nldrb r1, [r0,#0x1A]\nlsl r1, #0x8\nldrb r2, [r0,#0x1B]\nadd r1, r2\nmov r2, #0x1E\nlsl r2, #0x8\nadd r2, #0x2B\nmov r0, #1\ncmp r1, r2\nbcc check_font_end\nmov r0, #0\ncheck_font_end:\npop {pc}\n.align 2\nbuffer3_check_font:\n.word 0x02021EC4");
}

void reset_ff_buffer2_add10(){
	asm("push {lr}\nldr r0, buffer2_add10\nmov r1, #0\nsub r1, #1\nstr r1, [r0,#0x0]\nstr r1, [r0,#0x4]\nstr r1, [r0,#0x8]\nstr r1, [r0,#0xC]\npop {pc}\n.align 2\nbuffer2_add10:\n.word 0x02021DD4");
}

void check_pw(){
	asm("push {lr}\nmov r0, #0xFF\nldr r1, check_penw_f\nldrb r1, [r1]\ncmp r1, #0x6\nbeq check_penw_end\nlsl r0, #0x8\nadd r0, #0xFF\ncheck_penw_end:\npop {pc}\n.align 2\ncheck_penw_f:\n.word 0x080FE0CB");
}