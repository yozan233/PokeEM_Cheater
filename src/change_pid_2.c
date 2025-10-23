#include "header/data.h"

extern struct Pokemon *getCurrentPlayerParty();
extern struct BaseStats* getSpeciesBaseStats(u16 species);
extern u32 GetMonData(struct Pokemon* poke_address, u8 request, const void* data);
u32 CreateShinyPid(u8 nature, u8 gender, u8 ratio, u32 TiD);
bool8 checkAbilityNumInvalid(u32 pid);

#define CalcNature(PiD)((umodsi3(PiD, 25)))
#define BIC(value, bit)(value & (~(bit)))

u8 CalcGender(u32 pid,u8 ratio){
    u8 flag = pid & 0xFF;
    if(flag == 0 || flag >= 0xFE || flag > ratio)
        return GENDER_MALE;
    else
        return GENDER_FEMALE;
}

void SetMonPidTid(struct Pokemon *mon,u32 pid,u32 tid){
    struct Pokemon* changed = Alloc(0x64);

    memcpy(changed, mon, 0x64);
    SetMonData(changed, ATTR_PID, &pid);
    DecryptBoxMon(changed);
    if(changed->checksum == 0 || changed->checksum == CalculateBoxMonChecksum(changed)){
        EncryptBoxMon(changed);
        memcpy(mon, changed, 0x64);
        Free(changed);
        return;
    }

    //如果校验和不正确则重新创建一只精灵
    ZeroMonData(changed);
    CreateMon(changed, GetMonData(mon,ATTR_SPECIES,0), GetMonData(mon, ATTR_LEVEL, 0), 1, 1, pid, 1, tid);

    u8 startAttrNum = 0xA;
    u8 endAttrNum;
#ifdef RUBY_SAPPHIRE
    endAttrNum = 0x4E;
#else
    endAttrNum = 0x50;
#endif

    for (u8 i = startAttrNum; i <= endAttrNum; i++)
    {
#ifdef RUBY_SAPPHIRE
        if(i == 0x42)
            continue;
#endif
        u32 attr = 0;
        attr = GetMonData(mon, i, 0);
        SetMonData(changed, i, &attr);
    }
    //set font lang and marks
    u32 attr = 0;
    attr = GetMonData(mon, ATTR_FONT_LANG, 0);
    SetMonData(changed, ATTR_FONT_LANG, &attr);

    attr = 0;
    attr = GetMonData(mon, ATTR_MARKS, 0);
    SetMonData(changed, ATTR_MARKS, &attr);

    //set nick and ot name
    u8 nick[12];
    GetMonData(mon, ATTR_NAME, nick);
    SetMonData(changed, ATTR_NAME, nick);

    GetMonData(mon, ATTR_OT_NAME, nick);
    SetMonData(changed, ATTR_OT_NAME, nick);

    memcpy(mon, changed, 0x64);
    Free(changed);
}

void ChangePid(u8 nature,u8 gender,u8 shininess){
    struct Pokemon *poke = getCurrentPlayerParty();

    u16 species = myTempData->species_2;
    u8 ratio = getSpeciesBaseStats(species)->genderRatio;

    u32 PiD = myTempData->PID;
    u32 TiD = myTempData->TID;

    if(nature == 0xFF){
        nature = CalcNature(PiD);
    }
    if(gender > 1){
        gender = CalcGender(PiD,ratio);
    }

    if (!shininess){
        do{
            PiD = Random() | (Random() << 0x10);
        } while((nature <= 25 && nature != CalcNature(PiD)) || (gender != CalcGender(PiD, ratio)) || checkAbilityNumInvalid(PiD));
    }
    else{
        PiD = CreateShinyPid(nature, gender, ratio, TiD);
    }

    myTempData->PID = PiD;

    SetMonPidTid(poke,PiD,TiD);
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
    } while((nature <= 25 && nature != CalcNature(PiD)) || (gender != CalcGender(PiD, ratio)) || checkAbilityNumInvalid(PiD));

    return PiD;
}

bool8 checkAbilityNumInvalid(u32 pid){
    #ifdef FIRE_RED_LEAF_GREEN
    if(gQuantityLimit.abilityHook == TRUE && myTempData->abilityNumPos != 2){
        return (pid & 1) != myTempData->abilityNumPos;
    }
    #endif
    return FALSE;
}
