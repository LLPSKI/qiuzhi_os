#ifndef _UART_H
#define _UART_H

#include <types.h>

void uart_init(void);
void uart_send(u8_t c);
void uart_send_string(u8_t *str);
void uart_send_buf(const u8_t *buf, size_t length);
void uart_test(void);

#endif /* _UART_H */