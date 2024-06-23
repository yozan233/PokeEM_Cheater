#include "header/structs.h"

void debug(){

}

void restart(int i){
    asm("bx r0");
}

void LZ77UnCompVram(void *src, void *dest){
	asm("swi 0x12");
}

void CpuSet(void *src, void *dest, int control){
	asm("swi 0xB");
}

void CpuFastSet(const void *src, void *dest, int control){
	asm("swi 0xC");
}

void CpuFastFill(int value, void *dest, int size)                             
{                                                                  
    int tmp = value;                                     
    CpuFastSet(&tmp,dest,0x01000000 | ((size)/(32/8) & 0x1FFFFF));
}

#ifdef RUBY_SAPPHIRE
extern u32 gBGTilemapBuffers[];

struct MallocBlock {
	int malloc;
	int size;
};

int Alloc(u32 size){
	int head = (&gBGTilemapBuffers[21]);
	int pointer = gBGTilemapBuffers[0];

	struct MallocBlock *block = &gBGTilemapBuffers;

	int malloc;
	if(pointer == 0){
		malloc = head;
	}
	else{
		malloc = head + block[pointer].size;
	}
	pointer++;

	block[pointer].malloc = malloc;
	block[pointer].size = size;

	gBGTilemapBuffers[0] = pointer;

	return malloc;
}

int AllocZeroed(u32 size){
	int malloc = Alloc(size);
	CpuFastFill(0, malloc, size);
	return malloc;
}

void Free(int malloc){
	int pointer = gBGTilemapBuffers[0];
	if(pointer == 0)
		return;
	gBGTilemapBuffers[0] = pointer - 1;
}

void SetGpuReg(u8 reg, u16 value){
	u16 *ptr = (u16 *)(0x04000000 + reg);
    *ptr = value;
}

#endif