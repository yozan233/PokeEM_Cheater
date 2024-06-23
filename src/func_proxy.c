#include "header/funcs.h"

extern u8 **malloc_pointer_loc;
extern struct rbox_short rbox_table[];
extern struct MySaveblock *mySav;
extern const u8 sTrainerCardTextColors[];

struct superstate *super = (struct superstate *)&gMain;
struct TextBuffer *textBuffer = (struct TextBuffer *)&gStringVar1[0x100];
struct MyDatastruct *myTempData = (struct MyDatastruct *)&gStringVar1;
struct MousePos *mouseXY = (struct MousePos *)(&gSprites[0].pos1);
struct task *tasks = (struct task *)&gTasks;
struct fade_ctrl *pal_fade_control = &gPaletteFade;

struct MySaveblock *mySav = (struct MySaveblock *)&gSpecialVar_0x8004;
u8 **malloc_pointer_loc = (u8 **)&gSpecialVar_0x8004;

void ShowBg01(){
    ShowBg(0);
    ShowBg(1);
}

void ChangeBgXY(u8 bg_id){
    ChangeBgX(bg_id,0,0);
    ChangeBgY(bg_id,0,0);
}

void SetBg1TilemapBuffer(){
    SetBgTilemapBuffer(1,*malloc_pointer_loc+4);
}

void CopyDiplomaTilemapBuffer(){
    CopyToBgTilemapBuffer(1,sDiplomaTilemap,0,0);
}

void CopyBgTilemapBufferToVram01(){
    CopyBgTilemapBufferToVram(0);
    CopyBgTilemapBufferToVram(1);
}

void ResetAllSpriteData(){
    ResetSpriteData();
    ResetPaletteFade();
    FreeAllSpritePalettes();
}

void InitMainWindows(){
    InitWindows(rbox_table);
    DeactivateAllTextPrinters();
}

u8 InitSecondWindows(){
    return AddWindow(rbox_table+2);
}

void FillMainWindowPixelRect(u16 x, u16 y, u16 width, u16 height){
    FillWindowPixelRect(0,0,x,y,width,height);
}

void UpdateMainWindowsText(u8 font,u8 *str,u8 x,u8 y){
    AddTextPrinterParameterized3(0,font,x,y,sTrainerCardTextColors,0,str);
}

void UpdateSecondWindowsText(u8 *str,u8 x,u8 y){
    AddTextPrinterParameterized(mySav->boxId,1,str,x,y,0,0); //按键提示
}


