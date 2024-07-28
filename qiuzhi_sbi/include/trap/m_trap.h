#ifndef _TRAP_M_TRAP_H
#define _TRAP_M_TRAP_H

#include <types.h>
#include <trap/m_trap_contexts.h>

// 函数声明
void m_trap_init(void);
void m_trap_handler(m_trap_contexts *ctx);

#endif /* _TRAP_M_TRAP_H */