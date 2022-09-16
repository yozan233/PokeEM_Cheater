#include "header/funcs.h"

void cb_execute(void);
extern void task_loader(u8);
extern void obj_callback();

void main_func()
{
	*malloc_pointer_loc = (u8 *) malloc_and_clear(0x1004);
	obj_and_aux_reset_all();
	pal_fade_control_and_dead_struct_reset();
	gpu_pal_allocator_reset();
	// reset_db();
	task_add(task_loader,1);
	set_callback2(cb_execute);
	return;
}

void cb_execute()
{
	task_exec();
	objc_exec();
	obj_sync_something();
	fade_and_return_progress_probably();
	obj_callback();
	return;
}

// void reset_db(){
// 	asm("push {lr}\nsub sp, #4\nmov r1, #0\nlsl r0, r1,#0x18\nlsl r3, r1,#0x10\norr r0,r3\nlsl r3, r1,#0x8\norr r0, r3\norr r0, r1\nstr r0, [sp]\nmov r0, #0x80\nmov r2, #0xC0\nlsl r0, r0,#0x11\norr r2, r0\nmov r0, r13\nldr r1, clear_buffer2\nswi #0xC\nadd sp, #4\npop {pc}\n.align 2\nclear_buffer2:\n.word 0x02021DC4");
// }