#ifndef _MM_MEM_CONFIG_H
#define _MM_MEM_CONFIG_H

#include <feature.h>

// 宏定义
#define PAGE_SIZE_SHIFT     12
#define PAGE_SIZE           (1 << PAGE_SIZE_SHIFT)
#define CORE_STACK_SIZE     (PAGE_SIZE)
#define CORE_STACKS_SIZE    (NCPU * CORE_STACK_SIZE)

#endif /* _MM_MEM_CONFIG_H */