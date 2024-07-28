include config.mk

all: $(TARGET)

run:
	$(QEMU) $(QEMUOPS)

debug:
	$(QEMU) $(QEMUOPS) $(QEMU_DEBUG_OPS)

clean:
	$(RM) -rf $(BUILD_DIR) $(TARGET)

test:
	@echo $(SBI_SRC_DIR)
	@echo $(SBI_C_FILES)
	@echo $(SBI_ASM_FILES)
	@echo $(SBI_OBJ_FILES)
	$(info No other machine supported now!)

SBI_SRC_DIR = $(shell find $(SRC_DIR) -maxdepth 2 -type d)
SBI_C_FILES = $(foreach dir, $(SBI_SRC_DIR), $(wildcard $(dir)/*.c))
SBI_ASM_FILES = $(foreach dir, $(SBI_SRC_DIR), $(wildcard $(dir)/*.S))
SBI_OBJ_FILES = $(foreach file, $(SBI_C_FILES), $(BUILD_DIR)/$(dir $(file))$(basename $(notdir $(file)))_c.o)
SBI_OBJ_FILES += $(foreach file, $(SBI_ASM_FILES), $(BUILD_DIR)/$(dir $(file))$(basename $(notdir $(file)))_s.o)

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

$(foreach c_file, $(SBI_C_FILES), $(eval $(call c_files_compile_rule, $(c_file))))
$(foreach asm_file, $(SBI_ASM_FILES), $(eval $(call asm_files_compile_rule, $(asm_file))))

$(TARGET): $(LINKER_DIR)/sbi.ld $(SBI_OBJ_FILES)
	$(LD) $(LDOPS) -T $< -o $(TARGET).elf $(SBI_OBJ_FILES)
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET)