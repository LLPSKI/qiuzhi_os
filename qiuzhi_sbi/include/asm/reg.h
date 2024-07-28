#ifndef _ASM_REG_H
#define _ASM_REG_H

#include <types.h>

// 内联函数声明
// M模式csr
__inline__ __attribute__((always_inline)) u64_t r_mvendorid(void);
__inline__ __attribute__((always_inline)) u64_t r_marchid(void);
__inline__ __attribute__((always_inline)) u64_t r_mimpid(void);
__inline__ __attribute__((always_inline)) u64_t r_mhartid(void);
// __inline__ __attribute__((always_inline)) u64_t r_mconfigptr(void);
__inline__ __attribute__((always_inline)) u64_t r_misa(void);
__inline__ __attribute__((always_inline)) u64_t r_mstatus(void);

// trap
__inline__ __attribute__((always_inline)) u64_t r_mepc(void);
__inline__ __attribute__((always_inline)) u64_t r_mtval(void);
__inline__ __attribute__((always_inline)) u64_t r_mtvec(void);
__inline__ __attribute__((always_inline)) void w_mtvec(u64_t x);
__inline__ __attribute__((always_inline)) u64_t r_mcause(void);
__inline__ __attribute__((always_inline)) u64_t r_mie(void);
__inline__ __attribute__((always_inline)) u64_t r_mip(void);
__inline__ __attribute__((always_inline)) u64_t r_mideleg(void);
__inline__ __attribute__((always_inline)) u64_t r_medeleg(void);

// 通用寄存器
__inline__ __attribute__((always_inline)) u64_t r_pc(void);
__inline__ __attribute__((always_inline)) u64_t r_ra(void);
__inline__ __attribute__((always_inline)) u64_t r_sp(void);
__inline__ __attribute__((always_inline)) u64_t r_gp(void);
__inline__ __attribute__((always_inline)) u64_t r_tp(void);
__inline__ __attribute__((always_inline)) u64_t r_fp(void);

// 函数声明
void analyse_mstatus(u64_t mstatus);

// 内联函数定义
// M模式csr
__inline__ __attribute__((always_inline)) u64_t r_mvendorid(void)
{
    u64_t x;
    asm volatile("csrr %0, mvendorid" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_marchid(void)
{
    u64_t x;
    asm volatile("csrr %0, marchid" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_mimpid(void)
{
    u64_t x;
    asm volatile("csrr %0, mimpid" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_mhartid(void)
{
    u64_t x;
    asm volatile("csrr %0, mhartid" : "=r"(x));
    return x;
}
// __inline__ __attribute__((always_inline)) u64_t r_mconfigptr(void)
// {
//     u64_t x;
//     asm volatile("csrr %0, mconfigptr" : "=r"(x));
//     return x;
// }
__inline__ __attribute__((always_inline)) u64_t r_misa(void)
{
    u64_t x;
    asm volatile("csrr %0, misa" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_mstatus(void)
{
    u64_t x;
    asm volatile("csrr %0, mstatus" : "=r"(x));
    return x;
}

// trap
__inline__ __attribute__((always_inline)) u64_t r_mepc(void)
{
    u64_t x;
    asm volatile("csrr %0, mepc" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_mtval(void)
{
    u64_t x;
    asm volatile("csrr %0, mtval" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_mtvec(void)
{
    u64_t x;
    asm volatile("csrr %0, mtvec" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) void w_mtvec(u64_t x)
{
    asm volatile("csrw mtvec, %0" : : "r"(x));
}
__inline__ __attribute__((always_inline)) u64_t r_mcause(void)
{
    u64_t x;
    asm volatile("csrr %0, mcause" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_mie(void)
{
    u64_t x;
    asm volatile("csrr %0, mie" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_mip(void)
{
    u64_t x;
    asm volatile("csrr %0, mip" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_mideleg(void)
{
    u64_t x;
    asm volatile("csrr %0, mideleg" : "=r"(x));
    return x;
}
__inline__ __attribute__((always_inline)) u64_t r_medeleg(void)
{
    u64_t x;
    asm volatile("csrr %0, medeleg" : "=r"(x));
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