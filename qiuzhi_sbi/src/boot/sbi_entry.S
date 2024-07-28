.section ".text.boot"

.globl sbi_entry
sbi_entry:

    # 
    la sp, sbi_stack_bottom
    li t0, 4096
    add sp, sp ,t0

    tail sbi_main

.section .data

.align 12
.globl sbi_stack_bottom
sbi_stack_bottom:
    .skip 4096