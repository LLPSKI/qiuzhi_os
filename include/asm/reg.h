#ifndef _ASM_REG_H
#define _ASM_REG_H

#include <types.h>

// 内联函数声明
// S模式csr
__inline__ __attribute__((always_inline)) u64_t r_sstatus(void);

// trap
__inline__ __attribute__((always_inline)) u64_t r_sepc(void);
__inline__ __attribute__((always_inline)) u64_t r_stval(void);
__inline__ __attribute__((always_inline)) u64_t r_stvec(void);
__inline__ __attribute__((always_inline)) void w_stvec(u64_t x);
__inline__ __attribute__((always_inline)) u64_t r_scause(void);
__inline__ __attribute__((always_inline)) u64_t r_sie(void);
__inline__ __attribute__((always_inline)) u64_t r_sip(void);

// sv39
__inline__ __attribute__((always_inline)) u64_t r_satp(void);

// 通用寄存器
__inline__ __attribute__((always_inline)) u64_t r_pc(void);
__inline__ __attribute__((always_inline)) u64_t r_ra(void);
__inline__ __attribute__((always_inline)) u64_t r_sp(void);
__inline__ __attribute__((always_inline)) u64_t r_gp(void);
__inline__ __attribute__((always_inline)) u64_t r_tp(void);
__inline__ __attribute__((always_inline)) u64_t r_fp(void);



// 内联函数定义
// S模式csr
__inline__ __attribute__((always_inline)) u64_t r_sstatus(void)
{
    u64_t x;
    asm volatile("csrr %0, sstatus" : "=r"(x));
    return x;
}

// trap
__inline__ __attribute__((always_inline)) u64_t r_sepc(void)
{
    u64_t x;
    asm volatile("csrr %0, sepc" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_stval(void)
{
    u64_t x;
    asm volatile("csrr %0, stval" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_stvec(void)
{
    u64_t x;
    asm volatile("csrr %0, stvec" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) void w_stvec(u64_t x)
{
    asm volatile("csrw stvec, %0" : : "r"(x));
}
__inline__ __attribute__((always_inline)) u64_t r_scause(void)
{
    u64_t x;
    asm volatile("csrr %0, scause" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_sie(void)
{
    u64_t x;
    asm volatile("csrr %0, sie" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_sip(void)
{
    u64_t x;
    asm volatile("csrr %0, sip" : "=r"(x));
    return x;
}

// sv39
__inline__ __attribute__((always_inline)) u64_t r_satp(void)
{
    u64_t x;
    asm volatile("csrr %0, satp" : "=r"(x));
    return x;
}

// 通用寄存器
__inline__ __attribute__((always_inline)) u64_t r_pc(void)
{
    u64_t x;
    asm volatile("auipc %0, 0" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_ra(void)
{
    u64_t x;
    asm volatile("mv %0, ra" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_sp(void)
{
    u64_t x;
    asm volatile("mv %0, sp" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_gp(void)
{
    u64_t x;
    asm volatile("mv %0, gp" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_tp(void)
{
    u64_t x;
    asm volatile("mv %0, tp" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_fp(void)
{
    u64_t x;
    asm volatile("mv %0, fp" : "=r"(x));
    return x;
}

#endif /* _ASM_REG_H */