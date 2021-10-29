AS=arm-none-eabi-as
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
CC=arm-none-eabi-gcc

ASFLAGS=-mthumb
CFLAGS= -std=gnu11 -mthumb -mthumb-interwork -mcpu=arm7tdmi -fno-inline -mlong-calls -march=armv4t -Wall -Wextra -Wconversion -O2 -w
LDFLAGS=-z muldefs --relocatable
MAPFILE=-Map test.map

.PHONY: clean,objects

all: objects
	$(LD) $(LDFLAGS) $(MAPFILE) -T linker.lsc -T bpee.ld -o "build\linked.o" "build\exit_asm.o" "build\main.o" "build\sub_bg_init.o" "build\task_loader.o" "build\tiles_load.o" "build\string_print.o" "build\load_icons.o" "build\obj_callback.o" "build\change_pid.o" "build\Chuan.o" "build\task_02.o" "build\set_text.o" "build\resource.o"
	armips insert.asm
	@echo "Compile Successfully."
		

objects:
	mkdir -p build
	$(CC) $(CFLAGS) -c "src\resource.c" -o "build\resource.o"
	$(CC) $(CFLAGS) -c "src\set_text.c" -o "build\set_text.o"
	$(CC) $(CFLAGS) -c "src\main.c" -o "build\main.o"
	$(CC) $(CFLAGS) -c "src\sub_bg_init.c" -o "build\sub_bg_init.o"
	$(CC) $(CFLAGS) -c "src\task_loader.c" -o "build\task_loader.o"
	$(CC) $(CFLAGS) -c "src\tiles_load.c" -o "build\tiles_load.o"
	$(CC) $(CFLAGS) -c "src\string_print.c" -o "build\string_print.o"
	$(CC) $(CFLAGS) -c "src\task_02.c" -o "build\task_02.o"
	$(AS) $(ASFLAGS) -c "src\exit_asm.s" -o "build\exit_asm.o"
	$(AS) $(ASFLAGS) -c "src\load_icons.asm" -o "build\load_icons.o"
	$(AS) $(ASFLAGS) -c "src\obj_callback.asm" -o "build\obj_callback.o"
	$(AS) $(ASFLAGS) -c "src\change_pid.asm" -o "build\change_pid.o"
	$(AS) $(ASFLAGS) -c "src\Chuan.asm" -o "build\Chuan.o"
	
clean:
	rm build//*
