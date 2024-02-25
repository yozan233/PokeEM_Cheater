
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

