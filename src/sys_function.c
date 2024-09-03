#include "header/structs.h"

void CpuSet(void *src, void *dest, int control);
//
//#define CPU_SET_SRC_FIXED 0x01000000
//#define CPU_SET_16BIT     0x00000000
//#define CPU_SET_32BIT     0x04000000
//#define CPU_COPY_UNCHECKED(src, dest, size, bit) CpuSet(src, dest, CPU_SET_##bit##BIT | ((size)/(bit/8) & 0x1FFFFF))
//#define CPU_COPY(src, dest, size, bit) CPU_COPY_UNCHECKED(src, dest, size, bit)
//#define CpuCopy16(src, dest, size) CPU_COPY(src, dest, size, 16)

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

void CopyItemIconPicTo4x4Buffer(void *src, void *dest)
{
    u8 i;

    for (i = 0; i < 3; i++) {
        //CpuCopy16(src + i * 96, dest + i * 128, 0x60);
        CpuSet(src + i * 96, dest + i * 128, 0x00000000 | ((0x60) / (16 / 8) & 0x1FFFFF));
    }
}

#ifdef RUBY_SAPPHIRE
extern u32 gBGTilemapBuffers[];

struct MallocBlock {
	void *malloc;
	u32 size;
};

struct AllocMemory {
    u32 pointer;
    struct MallocBlock blocks[20];
    u8 memory[0x8000];
};

struct AllocMemory *gAllocMemory = (struct AllocMemory*)&gBGTilemapBuffers;

void *Alloc(u32 size){
//	int head = (&gBGTilemapBuffers[21]);
//	int pointer = gBGTilemapBuffers[0];
//
//	struct MallocBlock *block = &gBGTilemapBuffers;

	void *malloc;
	if(gAllocMemory->pointer == 0){
		malloc = &gAllocMemory->memory;
	}
	else{
//		malloc = head + block[pointer].size;
        struct MallocBlock *block = &gAllocMemory->blocks[gAllocMemory->pointer];
        malloc = &(block->malloc) + block->size;
	}
    gAllocMemory->pointer++;

    gAllocMemory->blocks[gAllocMemory->pointer].malloc = malloc;
    gAllocMemory->blocks[gAllocMemory->pointer].size = size;

	return malloc;
}

void *AllocZeroed(u32 size){
	void *malloc = Alloc(size);
	CpuFastFill(0, malloc, size);
	return malloc;
}

void Free(void *malloc){
	if(gAllocMemory->pointer == 0)
		return;
    gAllocMemory->pointer--;
}

void SetGpuReg(u8 reg, u16 value){
	u16 *ptr = (u16 *)(0x04000000 + reg);
    *ptr = value;
}

#endif