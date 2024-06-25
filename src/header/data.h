#include "funcs.h"
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
extern struct MySaveblock *mySav;

extern const struct ListQuantityLimit gQuantityLimit;
extern const struct NameLengthConfig gNameLengthConfig;


extern void ShowBg01();
extern void ChangeBgXY(u8 bg_id);
extern void SetBg1TilemapBuffer();
extern void CopyDiplomaTilemapBuffer();
extern void CopyBgTilemapBufferToVram01();
extern void InitMainWindows();
extern u8 InitSecondWindows();
extern void FillMainWindowPixelRect(u16 x, u16 y, u16 width, u16 height);
extern void UpdateMainWindowsText(u8 font,u8 *str,u8 x,u8 y);
extern void UpdateSecondWindowsText(u8 *str,u8 x,u8 y);
extern void ResetAllSpriteData();
extern u16 *GetBGPaletteMem(int offset);
extern u16 *GetOBJPaletteMem(int offset);
extern u16 *GetBGPaletteMem2(int offset);
extern u16 *GetOBJPaletteMem2(int offset);







