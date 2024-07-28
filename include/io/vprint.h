#ifndef _IO_VPRINT_H
#define _IO_VPRINT_H

#include <types.h>
#include <utils/stdarg.h>

// 类型声明
typedef void (*fmt_callback_t)(const u8_t *buf, 
    size_t len);

// 函数声明
void vprintfmt(fmt_callback_t out, const u8_t *fmt, 
    va_list ap);

#endif /* _IO_VPRINT_H */