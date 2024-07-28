#ifndef _DEV_UART_H
#define _DEV_UART_H

#include <types.h>

// 函数声明
void uart_init(void);
void uart_send(u8_t c);
void uart_send_string(u8_t *str);
void uart_send_buf(const u8_t *buf, size_t length);
void uart_test(void);

#endif /* _DEV_UART_H */