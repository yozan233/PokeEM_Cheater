#include "structs.h"

/*offsets*/
extern void *VRAM;
extern void *PRAM;
extern void *OAM;
extern void *volatile*DMA3SAD;
extern void *volatile*DMA3DAD;
extern vu32 *DMA3CNT;
extern struct task *tasks;
extern struct saveblock1 **sav1;
extern u8 **malloc_pointer_loc;
extern struct fade_ctrl *pal_fade_control;
// extern struct obj *objects;
extern const char text_table[];
// extern char *fcode_buffer2;
// extern struct pokemon *partypokemon;
// extern char *displayed_string;
// extern u8 *hand_id_loc;
extern struct superstate *super;
extern struct Datastruct *strbData;
// extern struct mybuffer *bfr;
extern struct mouse *mouseXY;
extern struct AllPokemons *pokeMax;
// extern struct main8004 *main_8004;
// extern u8 *pokemon_quanitity;
