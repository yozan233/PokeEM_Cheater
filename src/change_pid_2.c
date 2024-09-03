#include "header/data.h"

extern struct Pokemon *getCurrentPlayerParty();
extern u32 GetMonData(struct Pokemon* poke_address, u8 request, const void* data);
u32 CreateShinyPid(u8 nature, u8 gender, u16 species, u32 TiD);

#define BIC(value, bit)(value & (~(bit)))

u8 CalcGender(u16 species, u32 personality){
    return GetGenderFromSpeciesAndPersonality(species, personality);
}

u8 CalcNature(u32 pid){
    return umodsi3(pid, 25);
}

u16 Random16(){
    return Random();
}

u32 Random32(){
    return Random() | (Random() << 0x10);
}

bool8 CheckNotNatureGender(u32 pid,u16 species,u8 nature,u8 gender){
    if (nature != CalcNature(pid))
        return TRUE;

    if (gender != CalcGender(species,pid))
        return TRUE;

    return FALSE;
}

void SetMonPidTid(struct Pokemon *mon,u32 pid,u32 tid){
    SetMonData(mon, ATTR_PID, &pid);
    SetMonData(mon, ATTR_TID, &tid);

//
//    struct Pokemon* changed = Alloc(MON_DATA_SIZE);
//
//    memcpy(changed, mon, MON_DATA_SIZE);
//    SetMonData(changed, ATTR_PID, &pid);
//    DecryptBoxMon(changed);
//
//    u32 checksum = GetMonData(changed,ATTR_CHECKSUM,0);
//
//    if(checksum == 0 || checksum == CalculateBoxMonChecksum(changed)){
//        EncryptBoxMon(changed);
//        memcpy(mon, changed, MON_DATA_SIZE);
//        Free(changed);
//        return;
//    }
//
//    //如果校验和不正确则重新创建一只精灵
//    ZeroMonData(changed);
//    CreateMon(changed, GetMonData(mon,ATTR_SPECIES,0), GetMonData(mon, ATTR_LEVEL, 0), 1, 1, pid, 1, tid);
//
//    u8 startAttrNum = 0xA;
//    u8 endAttrNum;
//#ifdef RUBY_SAPPHIRE
//    endAttrNum = 0x4E;
//#else
//    endAttrNum = 0x50;
//#endif
//
//    for (u8 i = startAttrNum; i <= endAttrNum; i++)
//    {
//#ifdef RUBY_SAPPHIRE
//        if(i == 0x42)
//            continue;
//#endif
//        u32 attr = 0;
//        attr = GetMonData(mon, i, 0);
//        SetMonData(changed, i, &attr);
//    }
//    //set font lang and marks
//    u32 attr = 0;
//    attr = GetMonData(mon, ATTR_FONT_LANG, 0);
//    SetMonData(changed, ATTR_FONT_LANG, &attr);
//
//    attr = 0;
//    attr = GetMonData(mon, ATTR_MARKS, 0);
//    SetMonData(changed, ATTR_MARKS, &attr);
//
//    //set nick and ot name
//    u8 nick[12];
//    GetMonData(mon, ATTR_NAME, nick);
//    SetMonData(changed, ATTR_NAME, nick);
//
//    GetMonData(mon, ATTR_OT_NAME, nick);
//    SetMonData(changed, ATTR_OT_NAME, nick);
//
//    memcpy(mon, changed, MON_DATA_SIZE);
//    Free(changed);
}

void ChangePid(u8 nature,u8 gender,u8 shininess){
    u16 species = myTempData->species_2;

    u32 PiD = myTempData->PID;
    u32 TiD = myTempData->TID;

    if(nature > 25){
        nature = CalcNature(PiD);
    }

    if(gender > 1){
        gender = CalcGender(species,PiD);
    } else{
        gender = gender == GENDER_FEMALE ? 0xFE : 0x00;
    }

    if (!shininess){
        do{
            PiD = Random32();
        } while(CheckNotNatureGender(PiD,species,nature,gender));
    }
    else{
        PiD = CreateShinyPid(nature, gender, species, TiD);
    }

    myTempData->PID = PiD;

    struct Pokemon *poke = getCurrentPlayerParty();
    SetMonPidTid(poke,PiD,TiD);
}

u32 CreateShinyPid(u8 nature, u8 gender, u16 species, u32 TiD){
    u16 xored_tid = (TiD & 0xFFFF) ^ (TiD >> 0x10);
    xored_tid = BIC(xored_tid, 7);
    xored_tid |= umodsi3(Random16(), 8);

    u32 PiD;
    do{
        u16 pid1 = 0, pid2 = 0;
        for (u8 i = 0; i < 16; i++){
            u16 bit = 1 << i;
            bool32 set = Random16() & 1;
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
        if (Random16() & 1)
            PiD = (pid1) | (pid2 << 0x10);
        else
            PiD = (pid2) | (pid1 << 0x10);
    } while(CheckNotNatureGender(PiD,species,nature,gender));

    return PiD;
}