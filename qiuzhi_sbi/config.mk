# 目标配置
TARGET = qiuzhi_sbi

# 机器配置
MACHINE = virt
MEMORY = 128
NCPU = 1

# 选项配置
DEBUG = 1
PIC = 0
PIE = 0
FP = 1
O = 0
FREE = 1
GRAPHIC = 0

# 路径配置
C_INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build
LINKER_DIR = linker

# 工具链配置
GNU = riscv64-linux-gnu
CC = $(GNU)-gcc
LD = $(GNU)-ld
OBJCOPY = $(GNU)-objcopy
MKDIR = mkdir
RM = rm
QEMU = qemu-system-riscv64

# gcc选项配置
COPS = -c -I$(C_INCLUDE_DIR)

ifeq ($(PIC), 1)
	COPS += -fpic
else
	COPS += -fno-pic
endif

ifeq ($(PIE), 1)
	COPS += -fPIE
else
	COPS += -fno-PIE
endif

ifeq ($(FP), 1)
	COPS += -fno-omit-frame-pointer
else
	COPS += -fomit-frame-pointer
endif

ifeq ($(DEBUG), 1)
	COPS += -g
	COPS += -save-temps=obj
else

endif

ifeq ($(FREE), 1)
	COPS += -nostdlib
	COPS += -nostdinc
	COPS += -ffreestanding
else

endif

ifeq ($(O), 0)
	COPS += -O0
else ifeq ($(O), 1)
	COPS += -O1
else ifeq ($(O), 2)
	COPS += -O2
endif

ifeq ($(GNU), riscv64-linux-gnu)
	COPS += -mcmodel=medany 
	COPS += -mabi=lp64 
	COPS += -march=rv64imafd
else 

endif

ifeq ($(MACHINE), virt)
	COPS += -DMACHINE=VIRT
else

endif

# ld选项配置
ifeq ($(O), 0)
	LDOPS += -O0
else ifeq ($(O), 1)
	LDOPS += -O1
else ifeq ($(O), 2)
	LDOPS += -O2
endif

# qemu选项配置
QEMUOPS = -bios $(TARGET) \
-smp $(NCPU)
QEMU_DEBUG_OPS = -S -s

ifeq ($(GRAPHIC), 0)
	QEMUOPS += -nographic
else
	
endif

ifeq ($(MACHINE), virt)
	QEMUOPS += -machine virt
else
	
endif

ifdef MEMORY
	QEMUOPS += -m $(MEMORY)M
else
	
endif

ifdef NCPU
	QEMUOPS += -smp $(NCPU)
else

endif