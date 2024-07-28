#include <trap/m_trap_offsets.h>

.section .text
.align 3
.global m_trap_entry
m_trap_entry:

    # 保存异常上下文
    addi sp, sp, -M_TRAP_CTX_SIZE
    sd ra, M_TRAP_CTX_RA(sp)
    sd gp, M_TRAP_CTX_GP(sp)
    sd tp, M_TRAP_CTX_TP(sp)
    sd a0, M_TRAP_CTX_A(0)(sp)
    sd a1, M_TRAP_CTX_A(1)(sp)
    sd a2, M_TRAP_CTX_A(2)(sp)
    sd a3, M_TRAP_CTX_A(3)(sp)
    sd a4, M_TRAP_CTX_A(4)(sp)
    sd a5, M_TRAP_CTX_A(5)(sp)
    sd a6, M_TRAP_CTX_A(6)(sp)
    sd a7, M_TRAP_CTX_A(7)(sp)
    sd t0, M_TRAP_CTX_T(0)(sp)
    sd t1, M_TRAP_CTX_T(1)(sp)
    sd t2, M_TRAP_CTX_T(2)(sp)
    sd t3, M_TRAP_CTX_T(3)(sp)
    sd t4, M_TRAP_CTX_T(4)(sp)
    sd t5, M_TRAP_CTX_T(5)(sp)
    sd t6, M_TRAP_CTX_T(6)(sp)
    sd s0, M_TRAP_CTX_S(0)(sp)
    sd s1, M_TRAP_CTX_S(1)(sp)
    sd s2, M_TRAP_CTX_S(2)(sp)
    sd s3, M_TRAP_CTX_S(3)(sp)
    sd s4, M_TRAP_CTX_S(4)(sp)
    sd s5, M_TRAP_CTX_S(5)(sp)
    sd s6, M_TRAP_CTX_S(6)(sp)
    sd s7, M_TRAP_CTX_S(7)(sp)
    sd s8, M_TRAP_CTX_S(8)(sp)
    sd s9, M_TRAP_CTX_S(9)(sp)
    sd s10, M_TRAP_CTX_S(10)(sp)
    sd s11, M_TRAP_CTX_S(11)(sp)

    csrr t0, mstatus
    sd t0, M_TRAP_CTX_MSTATUS(sp)

    csrr t0, mepc
    sd t0, M_TRAP_CTX_MEPC(sp)

    csrr t0, mcause
    sd t0, M_TRAP_CTX_MCAUSE(sp)

    csrr t0, mtval
    sd t0, M_TRAP_CTX_MTVAL(sp)

    mv a0, sp
    call m_trap_handler

.align 2
.global trap_test
trap_test:
    li t0, 0x7770000000
    ld t0, (t0)
    ret