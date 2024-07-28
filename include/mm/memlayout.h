#ifndef _MM_MEMLAYOUT_H
#define _MM_MEMLAYOUT_H

#include <feature.h>

// 宏定义
// 物理地址空间
#define UART0       (0x10000000UL)
#define RAMBASE     (0x80000000UL)
#define KERNELBASE  (0x80200000UL)
#define RAMTOP      (RAMBASE + (MEMORY << 20))

// 内核地址空间
// 目前是物理地址空间的一一映射
// 相当于 PA = VA

// 用户地址空间

#endif /* _MM_MEMLAYOUT_H */