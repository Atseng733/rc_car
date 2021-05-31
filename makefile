PROJECT_NAME = rc_car
CC = arm-none-eabi-gcc
PROCESSOR = cortex-m4
CFLAGS = -c -mcpu=$(PROCESSOR) -mthumb -std=c11 -O0 -Iinclude -g -fno-common -ffunction-sections -fdata-sections
LFLAGS = -mthumb -mcpu=$(PROCESSOR) -Tstm32f407xx.ld -g -nostartfiles
SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c, build/%.o, $(SRCS))
$(info SRCS: $(SRCS))
$(info OBJS: $(OBJS))

OUTPUT_DIR = build
SRC_DIR = src



default: $(OUTPUT_DIR)/$(PROJECT_NAME).bin

$(OUTPUT_DIR)/$(PROJECT_NAME).bin: $(OUTPUT_DIR)/$(PROJECT_NAME).elf
	arm-none-eabi-objcopy -O binary $< $@

$(OUTPUT_DIR)/$(PROJECT_NAME).elf: $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

$(OUTPUT_DIR)/%.o: $(SRC_DIR)/%.c $(OUTPUT_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(OUTPUT_DIR):
	mkdir build

.PHONY: clean
clean: 
	-rmdir /q /s build