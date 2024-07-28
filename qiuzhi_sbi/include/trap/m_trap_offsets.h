#ifndef _TRAP_M_TRAP_OFFSETS_H
#define _TRAP_M_TRAP_OFFSETS_H

#define M_TRAP_CTX_SIZE     272
#define M_TRAP_CTX_MSTATUS  0
#define M_TRAP_CTX_MEPC     8
#define M_TRAP_CTX_MCAUSE   16
#define M_TRAP_CTX_MTVAL    24
#define M_TRAP_CTX_RA       32
#define M_TRAP_CTX_GP       40
#define M_TRAP_CTX_TP       48
#define M_TRAP_CTX_A(x)     (56 + (8 * x))
#define M_TRAP_CTX_T(x)     (128 + (8 * x))
#define M_TRAP_CTX_S(x)     (176 + (8 * x))

#endif /* _TRAP_M_TRAP_OFFSETS_H */