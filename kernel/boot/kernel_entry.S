#include <mm/mem_config.h>

# OpenSBI传递参数
# a0 = hartid

# kernel启动代码段
.section .text.boot

.align 2 # 地址对齐
.global kernel_entry # kernel.ld用于指定入口地址
kernel_entry:

    # 加载CPU core对应的栈空间
    la sp, core_stacks
    li t0, CORE_STACK_SIZE
    mv t1, a0
    addi t1, t1, 1
    mul t0, t0, t1
    add sp, sp, t0

    # 远跳kernel_main函数
    mv a0, a0 # 传参a0 = hartid
    tail kernel_main

# CPU核的栈空间
.section .data

.align 12 # 0x1000地址对齐
.global core_stacks # 向外引出
core_stacks:

    .skip CORE_STACKS_SIZE