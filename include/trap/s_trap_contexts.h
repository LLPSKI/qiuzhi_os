#ifndef _TRAP_S_TRAP_CONTEXTS_H
#define _TRAP_S_TRAP_CONTEXTS_H

#include <types.h>

typedef struct s_trap_contexts_t
{
    //由低地址到高地址
    u64_t sstatus;
    u64_t sepc;
    u64_t scause;
    u64_t stval;
    u64_t ra;
    // u64_t sp;
    u64_t gp;
    u64_t tp;
    u64_t a[8];
    u64_t t[7];
    u64_t s[12];
}s_trap_contexts_t;

#endif /* _TRAP_S_TRAP_CONTEXTS_H */