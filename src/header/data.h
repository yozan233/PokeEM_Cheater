#include "structs.h"
#include "get_attr.h"


extern struct task *tasks;
extern u8 **malloc_pointer_loc;
extern struct fade_ctrl *pal_fade_control;

#define itemTilesArm 0x06012000
#define monTilesArm  0x06010C00

extern const u8 *text_table[];
extern const u8 *mouse_pos_table[];
// extern char *fcode_buffer2;
// extern struct pokemon *partypokemon;
// extern char *displayed_string;
// extern u8 *hand_id_loc;
extern struct superstate *super;
extern struct MyDatastruct *myTempData;
extern struct TextBuffer *textBuffer;
extern struct MySaveblock *mySav;
// extern struct MyBuffer *bfr;
extern struct MousePos *mouseXY;

// extern struct main8004 *main_8004;
// extern u8 *pokemon_quanitity;

