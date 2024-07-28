#ifndef _UTILS_STDARG_H
#define _UTILS_STDARG_H

// 类型声明
typedef __builtin_va_list va_list;

// 宏定义
#define va_start(v, l)  __builtin_va_start(v, l)
#define va_end(v)       __builtin_va_end(v)
#define va_arg(v, l)    __builtin_va_arg(v, l)

#endif /* _UTILS_STDARG_H */