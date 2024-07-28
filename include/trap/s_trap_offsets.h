#ifndef _TRAP_S_TRAP_OFFSETS_H
#define _TRAP_S_TRAP_OFFSETS_H

#define S_TRAP_CTX_SIZE     272
#define S_TRAP_CTX_SSTATUS  0
#define S_TRAP_CTX_SEPC     8
#define S_TRAP_CTX_SCAUSE   16
#define S_TRAP_CTX_STVAL    24
#define S_TRAP_CTX_RA       32
#define S_TRAP_CTX_GP       40
#define S_TRAP_CTX_TP       48
#define S_TRAP_CTX_A(x)     (56 + (8 * x))
#define S_TRAP_CTX_T(x)     (128 + (8 * x))
#define S_TRAP_CTX_S(x)     (176 + (8 * x))

#endif /* _TRAP_S_TRAP_OFFSETS_H */