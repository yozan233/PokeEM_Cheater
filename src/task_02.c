#include "header/funcs.h"
//flags for buttons3_new_remapped:1=A,2=B,4=SELECT,8=START,0x10=RIGHT,0x20=LEFT,0x40=UP,0x80=DOWN,0x100=L,0x200=R
extern struct rbox_short rbox_table[];
extern void ButtonAEvent();
extern bool8 ButtonBEvent();
extern void ButtonSelectEvent();
extern void ButtonStartEvent();
extern void ButtonRightEvent();
extern void ButtonLeftEvent();
extern void ButtonUpEvent();
extern void ButtonDownEvent();
extern void ButtonShoulderR();
extern void ButtonShoulderL();

void aborter(u8 task_id);

void task_02(u8 task_id)
{
	switch(*(*malloc_pointer_loc))
	{
		case 0:
			(tasks[task_id].priv[2])++;
			if(tasks[task_id].priv[2] == 0x20)
				break;
			else
                return;
		case 1:
			switch(super->buttons4_new_and_keyrepeat)
			{
				case BUTTONS_A:
					ButtonAEvent();
					return;
				case BUTTONS_B:{
					bool8 finish = ButtonBEvent();
					if (finish)
						break;
					else
						return;
				}
				case BUTTONS_SELECT:
					ButtonSelectEvent();
					return;
				case BUTTONS_START:
					ButtonStartEvent();
					return;
				case BUTTONS_RIGHT:
					ButtonRightEvent();
					return;
				case BUTTONS_LEFT:
					ButtonLeftEvent();
					return;
				case BUTTONS_UP:
					ButtonUpEvent();
					return;
				case BUTTONS_DOWN:
					ButtonDownEvent();
					return;
				case BUTTONS_R:
					ButtonShoulderR();
					return;
				case BUTTONS_L:
					ButtonShoulderL();
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
}

void aborter(u8 task_id)
{
	if(((pal_fade_control->mix_color) >> 8 & 0x80))
		return;
	DestroyTask(task_id);
	#ifndef AXVE0
	FreeAllWindowBuffers();
	#endif
	Free(*malloc_pointer_loc);
	SetMainCallback2(CB2_ReturnToFieldContinueScript);
}






