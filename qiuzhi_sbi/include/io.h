#ifndef _IO_H
#define _IO_H

#include <types.h>

__inline__ __attribute__((always_inline)) u64_t mem_readd(u64_t a);
__inline__ __attribute__((always_inline)) u32_t mem_readw(u64_t a);
__inline__ __attribute__((always_inline)) u16_t mem_readh(u64_t a);
__inline__ __attribute__((always_inline)) u8_t mem_readb(u64_t a);

__inline__ __attribute__((always_inline)) void mem_writed(u64_t a, u64_t v);
__inline__ __attribute__((always_inline)) void mem_writew(u64_t a, u32_t v);
__inline__ __attribute__((always_inline)) void mem_writeh(u64_t a, u16_t v);
__inline__ __attribute__((always_inline)) void mem_writeb(u64_t a, u8_t v);

__inline__ __attribute__((always_inline)) void mem_barrier();

#define __arch_getd(a) (*(volatile u64_t *)(a))
#define __arch_putd(a, v) (*(volatile u64_t *)(a) = (v))

#define __arch_getw(a) (*(volatile u32_t *)(a))
#define __arch_putw(a, v) (*(volatile u32_t *)(a) = (v))

#define __arch_geth(a) (*(volatile u16_t *)(a))
#define __arch_puth(a, v) (*(volatile u16_t *)(a) = (v))

#define __arch_getb(a) (*(volatile u8_t *)(a))
#define __arch_putb(a, v) (*(volatile u8_t *)(a) = (v))

#define dmb() __asm__ __volatile__ ("" : : :"memory")
#define __iormb() dmb()
#define __iowmb() dmb()

__inline__ __attribute__((always_inline)) u64_t mem_readd(u64_t a)
{
    u64_t __v = __arch_getd(a);
    __iormb();
    return __v;
}
__inline__ __attribute__((always_inline)) u32_t mem_readw(u64_t a)
{
    u32_t __v = __arch_getw(a);
    __iormb();
    return __v;
}
__inline__ __attribute__((always_inline)) u16_t mem_readh(u64_t a)
{
    u16_t __v = __arch_geth(a);
    __iormb();
    return __v;
}
__inline__ __attribute__((always_inline)) u8_t mem_readb(u64_t a)
{
    u8_t __v = __arch_getb(a);
    __iormb();
    return __v;
}

__inline__ __attribute__((always_inline)) void mem_writed(u64_t a, u64_t v)
{
    u64_t __v = v;
    __arch_putd(a, __v);
    __iowmb();
}
__inline__ __attribute__((always_inline)) void mem_writew(u64_t a, u32_t v)
{
    u32_t __v = v;
    __arch_putw(a, __v);
    __iowmb();
}
__inline__ __attribute__((always_inline)) void mem_writeh(u64_t a, u16_t v)
{
    u16_t __v = v;
    __arch_puth(a, __v);
    __iowmb();
}
__inline__ __attribute__((always_inline)) void mem_writeb(u64_t a, u8_t v)
{
    u8_t __v = v;
    __arch_putb(a, __v);
    __iowmb();
}

__inline__ __attribute__((always_inline)) void mem_barrier()
{
    __sync_synchronize();
}

#endif /* _IO_H */