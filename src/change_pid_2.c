#include "header/funcs.h"

extern struct Pokemon *getCurrentPartyplayer();
extern struct BaseStats* getSpeciesBaseStats(u16 species);
u32 CreateShinyPid(u8 nature, u8 gender, u8 ratio, u32 TiD);

#define CalcGender(pid, ratio)(((ratio) > (0xFF & pid) ? 0xFE : 0))
#define CalcNature(PiD)((umodsi3(PiD, 25)))


void ChangePid(u8 nature,u8 gender,u8 shininess){
    struct Pokemon *poke = getCurrentPartyplayer();

    u8 wanted_nature = nature;

    u16 species = myTempData->species_2;
    u8 ratio = getSpeciesBaseStats(species)->genderRatio;

    u32 PiD = myTempData->PID;
    u32 TiD = myTempData->TID;

    if (!shininess){
        do{
            PiD = Random() | (Random() << 0x10);
        } while( (nature != CalcNature(PiD))  || (gender != CalcGender(PiD,ratio)) );
    }
    else{
        PiD = CreateShinyPid(nature, gender, ratio, TiD);
    }

    //since pid completely changes pokemon structure we need to copy all the data
    struct pokemon* changed = Alloc(0x64);
    ZeroMonData(changed);
    CreateMon(changed, species, GetMonData(poke, ATTR_LEVEL, 0), 1, 1, PiD, 1, TiD);

    for (u8 i = 0xA; i <= 0x50; i++)
    {
        u32 attr = 0;
        attr = GetMonData(poke, i, 0);
        SetMonData(changed, i, &attr);
    }
    //set font lang and marks
    u32 attr = 0;
    attr = GetMonData(poke, ATTR_FONT_LANG, 0);
    SetMonData(changed, ATTR_FONT_LANG, &attr);

    attr = 0;
    attr = GetMonData(poke, ATTR_MARKS, 0);
    SetMonData(changed, ATTR_MARKS, &attr);

    //set nick and ot name
    u8 nick[12];
    GetMonData(poke, ATTR_NAME, nick);
    SetMonData(changed, ATTR_NAME, nick);

    GetMonData(poke, ATTR_OT_NAME, nick);
    SetMonData(changed, ATTR_OT_NAME, nick);

    //set correct ball in case of changing origin struct
    /* todo */

    memcpy(poke, changed, 0x64);
    Free(changed);
}

u32 CreateShinyPid(u8 nature, u8 gender, u8 ratio, u32 TiD){
    u16 xored_tid = (TiD & 0xFFFF) ^ (TiD >> 0x10);
    xored_tid = BIC(xored_tid, 7);
    xored_tid |= umodsi3(Random(), 8);

    u32 PiD;
    do{
        u16 pid1 = 0, pid2 = 0;
        for (u8 i = 0; i < 16; i++){
            u16 bit = 1 << i;
            bool32 set = Random() & 1;
            if (xored_tid & bit){
                if (set)
                    pid1 |= bit;
                else
                    pid2 |= bit;
            }
            else{
                if (set){
                    pid1 |= bit;
                    pid2 |= bit;
                }
            }
        }
        if (Random() & 1)
            PiD = (pid1) | (pid2 << 0x10);
        else
            PiD = (pid2) | (pid1 << 0x10);
    } while((nature <= 25 && nature != CalcNature(PiD)) || (gender != 0xFF && gender != CalcGender(PiD, ratio)));

    return PiD;
}