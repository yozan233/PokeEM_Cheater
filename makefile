AS=arm-none-eabi-as
LD=arm-none-eabi-ld
CC=arm-none-eabi-gcc
ARMIPS=armips

ASFLAGS=-mthumb
CFLAGS=-std=gnu11 -mthumb -mthumb-interwork -mcpu=arm7tdmi -fno-inline -mlong-calls -march=armv4t -Wall -Wextra -Wconversion -O2 -w
LDFLAGS=-z muldefs --relocatable

GAME_VERSION?=BPEE0
DEFINES?=EMERALD
BUILD_DIR=build
MAP_FILE=$(BUILD_DIR)/$(GAME_VERSION).map

C_DEFINE_FLAGS=$(foreach name,$(GAME_VERSION) $(DEFINES),-D $(name))
AS_DEFINE_FLAGS=$(foreach name,$(GAME_VERSION) $(DEFINES),--defsym $(name)=1)

.PHONY: all objects link armips clean

all: link

objects:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(C_DEFINE_FLAGS) -c "src/main.c" -o "$(BUILD_DIR)/main.o"
	$(CC) $(CFLAGS) $(C_DEFINE_FLAGS) -c "src/sys_function.c" -o "$(BUILD_DIR)/sys_function.o"
	$(CC) $(CFLAGS) $(C_DEFINE_FLAGS) -c "src/func_proxy.c" -o "$(BUILD_DIR)/func_proxy.o"
	$(CC) $(CFLAGS) $(C_DEFINE_FLAGS) -c "src/create_sprites.c" -o "$(BUILD_DIR)/create_sprites.o"
	$(CC) $(CFLAGS) $(C_DEFINE_FLAGS) -c "src/set_text.c" -o "$(BUILD_DIR)/set_text.o"
	$(CC) $(CFLAGS) $(C_DEFINE_FLAGS) -c "src/keyboard.c" -o "$(BUILD_DIR)/keyboard.o"
	$(CC) $(CFLAGS) $(C_DEFINE_FLAGS) -c "src/sub_bg_init.c" -o "$(BUILD_DIR)/sub_bg_init.o"
	$(CC) $(CFLAGS) $(C_DEFINE_FLAGS) -c "src/task_loader.c" -o "$(BUILD_DIR)/task_loader.o"
	$(CC) $(CFLAGS) $(C_DEFINE_FLAGS) -c "src/tiles_load.c" -o "$(BUILD_DIR)/tiles_load.o"
	$(CC) $(CFLAGS) $(C_DEFINE_FLAGS) -c "src/change_pid_2.c" -o "$(BUILD_DIR)/change_pid_2.o"
	$(CC) $(CFLAGS) $(C_DEFINE_FLAGS) -c "src/task_02.c" -o "$(BUILD_DIR)/task_02.o"
	$(CC) $(CFLAGS) $(C_DEFINE_FLAGS) -c "src/button_events.c" -o "$(BUILD_DIR)/button_events.o"
	$(CC) $(CFLAGS) $(C_DEFINE_FLAGS) -c "$(BUILD_DIR)/resource_text.c" -o "$(BUILD_DIR)/resource_text.o"
	$(CC) $(CFLAGS) $(C_DEFINE_FLAGS) -c "src/resource.c" -o "$(BUILD_DIR)/resource.o"
	$(AS) $(ASFLAGS) $(AS_DEFINE_FLAGS) -c "src/exit_asm.s" -o "$(BUILD_DIR)/exit_asm.o"
	$(AS) $(ASFLAGS) $(AS_DEFINE_FLAGS) -c "src/Chuan.asm" -o "$(BUILD_DIR)/Chuan.o"

link: objects
	$(LD) $(LDFLAGS) -Map "$(MAP_FILE)" \
	 -T linker.lsc \
	 -T rom_offsets.ld \
	 -o "$(BUILD_DIR)/linked.o" \
	 "$(BUILD_DIR)/exit_asm.o" \
	 "$(BUILD_DIR)/sys_function.o" \
	 "$(BUILD_DIR)/func_proxy.o" \
	 "$(BUILD_DIR)/main.o" \
	 "$(BUILD_DIR)/sub_bg_init.o" \
	 "$(BUILD_DIR)/task_loader.o" \
	 "$(BUILD_DIR)/change_pid_2.o" \
	 "$(BUILD_DIR)/tiles_load.o" \
	 "$(BUILD_DIR)/create_sprites.o" \
	 "$(BUILD_DIR)/Chuan.o" \
	 "$(BUILD_DIR)/task_02.o" \
	 "$(BUILD_DIR)/button_events.o" \
	 "$(BUILD_DIR)/set_text.o" \
	 "$(BUILD_DIR)/keyboard.o" \
	 "$(BUILD_DIR)/resource_text.o" \
	 "$(BUILD_DIR)/resource.o"

armips:
	$(ARMIPS) insert.asm

clean:
	rm -rf "$(BUILD_DIR)"
	rm -f rom_offsets.ld insert.asm
