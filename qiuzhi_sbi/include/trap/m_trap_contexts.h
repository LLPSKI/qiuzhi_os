#ifndef _TRAP_M_TRAP_CONTEXTS_H
#define _TRAP_M_TRAP_CONTEXTS_H

#include <types.h>

typedef struct m_trap_contexts
{
    //由低地址到高地址
    u64_t mstatus;
    u64_t mepc;
    u64_t mcause;
    u64_t mtval;
    u64_t ra;
    // u64_t sp;
    u64_t gp;
    u64_t tp;
    u64_t a[8];
    u64_t t[7];
    u64_t s[12];
}m_trap_contexts;

#endif /* _TRAP_M_TRAP_CONTEXTS_H */