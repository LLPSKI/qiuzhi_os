include config.mk

all: $(TARGET)

run:
	$(QEMU) $(QEMUOPS)

debug:
	$(QEMU) $(QEMUOPS) $(QEMU_DEBUG_OPS)

clean:
	$(RM) -rf $(BUILD_DIR) $(TARGET) $(TARGET).elf

test:
	

KERNEL_SRC_DIR = $(shell find $(SRC_DIR) -maxdepth 2 -type d)
KERNEL_C_FILES = $(foreach dir, $(KERNEL_SRC_DIR), $(wildcard $(dir)/*.c))
KERNEL_ASM_FILES = $(foreach dir, $(KERNEL_SRC_DIR), $(wildcard $(dir)/*.S))
KERNEL_OBJ_FILES = $(foreach file, $(KERNEL_C_FILES), $(BUILD_DIR)/$(dir $(file))$(basename $(notdir $(file)))_c.o)
KERNEL_OBJ_FILES += $(foreach file, $(KERNEL_ASM_FILES), $(BUILD_DIR)/$(dir $(file))$(basename $(notdir $(file)))_s.o)

define c_files_compile_rule
$(BUILD_DIR)/$(dir $(1))$(basename $(notdir $(1)))_c.o: $(1)
	$(MKDIR) -p $$(@D)
	$(CC) $(COPS) -o $$@ $$<
endef

define asm_files_compile_rule
$(BUILD_DIR)/$(dir $(1))$(basename $(notdir $(1)))_s.o: $(1)
	$(MKDIR) -p $$(@D)
	$(CC) $(COPS) -o $$@ $$<
endef

$(foreach c_file, $(KERNEL_C_FILES), $(eval $(call c_files_compile_rule, $(c_file))))
$(foreach asm_file, $(KERNEL_ASM_FILES), $(eval $(call asm_files_compile_rule, $(asm_file))))

$(TARGET): $(LINKER_DIR)/kernel.ld $(KERNEL_OBJ_FILES)
	$(LD) $(LDOPS) -T $< -o $(TARGET).elf $(KERNEL_OBJ_FILES)
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET)