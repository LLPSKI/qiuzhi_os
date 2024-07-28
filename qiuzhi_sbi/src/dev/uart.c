#include <dev/uart.h>
#include <mm/io.h>
#include <mm/memlayout.h>

#define UART UART0

// UART控制寄存器
#define UART_DAT        (UART + 0x00) /* 数据寄存器*/
#define UART_IER        (UART + 0x01) /* 中断使能寄存器*/
#define UART_IIR        (UART + 0x02) /* 中断标识寄存器 (read only)*/
#define UART_FCR        (UART + 0x02) /* FIFO控制寄存器 (write only)*/
#define UART_LCR        (UART + 0x03) /* 线路控制寄存器*/
#define UART_MCR        (UART + 0x04) /* MODEN控制寄存器*/
#define UART_LSR        (UART + 0x05) /* 线路状态寄存器*/
#define UART_MSR        (UART + 0x06) /* MODEN状态寄存器*/

#define UART_DLR_LSB    (UART + 0x00) /*预分频寄存器低8位*/
#define UART_DLR_MSB    (UART + 0x01) /*预分频寄存器高8位*/

// 线路状态
#define UART_LSR_ERROR  0x80  /* 出错 */
#define UART_LSR_EMPTY  0x40  /* 传输FIFO和移位寄存器为空 */
#define UART_LSR_TFE	0x20  /* 传输FIFO为空 */
#define UART_LSR_BI	    0x10  /* 传输被打断 */
#define UART_LSR_FE	    0x08  /* 接收到没有停止位的帧 */
#define UART_LSR_PE	    0x04  /* 奇偶校验错误位 */
#define UART_LSR_OE	    0x02  /* 数据溢出 */
#define UART_LSR_DR	    0x01  /* FIFO有数据 */

#define UART_16550_clock    (1843200)
#define UART_DEFAULT_BAUD   (115200)

void uart_init(void)
{
    // 关闭中断
    mem_writeb(UART_IER, 0);

    // 设置波特率
	mem_writeb(UART_LCR, 0x80);
    u16_t divisor = (u16_t)(UART_16550_clock / (16 * UART_DEFAULT_BAUD));
	mem_writeb(UART_DLR_MSB, (u8_t)(divisor >> 8));
    mem_writeb(UART_DLR_LSB, (u8_t)divisor);

    // 初始化FIFO
    mem_writeb(UART_FCR, 0x06);

    // 8 bits, no parity, one stop bit
    mem_writeb(UART_LCR, 0x03);

}

void uart_send(u8_t c)
{
    while((mem_readb(UART_LSR) & UART_LSR_EMPTY) == 0);
    mem_writeb(UART_DAT, c);
}

void uart_send_string(u8_t *str)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        uart_send(str[i]);
    }
}

void uart_send_buf(const u8_t *buf, size_t length)
{
    for(size_t i = 0; i < length; i++)
    {
        uart_send(buf[i]);
    }
}

void uart_test(void)
{
    uart_send_string("uart_test here!\n");
}