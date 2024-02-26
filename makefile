AS=arm-none-eabi-as
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
CC=arm-none-eabi-gcc

ASFLAGS=-mthumb
CFLAGS= -std=gnu11 -mthumb -mthumb-interwork -mcpu=arm7tdmi -fno-inline -mlong-calls -march=armv4t -Wall -Wextra -Wconversion -O2 -w
LDFLAGS=-z muldefs --relocatable
MAPFILE=-Map test.map
GAME_VERSION = BPEE0

CFLAGS += -D$(GAME_VERSION)
ASFLAGS += --defsym $(GAME_VERSION)=1

.PHONY: clean,objects

all: objects
	$(LD) $(LDFLAGS) $(MAPFILE) \
-T linker.lsc \
-T ${GAME_VERSION}.ld \
-o "build\linked.o" \
"build\exit_asm.o" \
"build\sys_function.o" \
"build\main.o" \
"build\sub_bg_init.o" \
"build\task_loader.o" \
"build\change_pid_2.o" \
"build\tiles_load.o" \
"build\create_sprites.o" \
"build\Chuan.o" "build\task_02.o" \
"build\button_events.o" \
"build\set_text.o" \
"build\keyboard.o" \
"build\resource.o"
	armips insert_${GAME_VERSION}.asm
	@echo "Compile Successfully."
		

objects:
	mkdir -p build
	$(CC) $(CFLAGS) -c "src\main.c" -o "build\main.o"
	$(CC) $(CFLAGS) -c "src\sys_function.c" -o "build\sys_function.o"
	$(CC) $(CFLAGS) -c "src\create_sprites.c" -o "build\create_sprites.o"
	$(CC) $(CFLAGS) -c "src\set_text.c" -o "build\set_text.o"
	$(CC) $(CFLAGS) -c "src\keyboard.c" -o "build\keyboard.o"
	$(CC) $(CFLAGS) -c "src\sub_bg_init.c" -o "build\sub_bg_init.o"
	$(CC) $(CFLAGS) -c "src\task_loader.c" -o "build\task_loader.o"
	$(CC) $(CFLAGS) -c "src\tiles_load.c" -o "build\tiles_load.o"
	$(CC) $(CFLAGS) -c "src\change_pid_2.c" -o "build\change_pid_2.o"
	$(CC) $(CFLAGS) -c "src\task_02.c" -o "build\task_02.o"
	$(CC) $(CFLAGS) -c "src\button_events.c" -o "build\button_events.o"
	$(CC) $(CFLAGS) -c "src\resource.c" -o "build\resource.o"
	$(AS) $(ASFLAGS) -c "src\exit_asm.s" -o "build\exit_asm.o"
	$(AS) $(ASFLAGS) -c "src\Chuan.asm" -o "build\Chuan.o"
	
clean:
	rm build//*

bpee0:              ; @$(MAKE) GAME_VERSION=BPEE0
bpee0_legend:       ; @$(MAKE) GAME_VERSION=BPEE_LEGEND
bpre0:              ; @$(MAKE) GAME_VERSION=BPRE0


