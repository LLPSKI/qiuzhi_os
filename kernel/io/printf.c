#include <io/printf.h>
#include <io/vprint.h>
#include <dev/uart.h>
#include <asm/reg.h>

// 函数定义
void printf(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vprintfmt(uart_send_buf, fmt, ap);
    va_end(ap);
}

void printf_test(void)
{
    
}

void printf_reg(void)
{
    printf("reg is below:\n");
    
    printf("sstatus\t = 0x%016lX\n", r_sstatus());
    printf("sepc\t = 0x%016lX\t", r_sepc());
    printf("stval\t = 0x%016lX\t", r_stval());
    printf("stvec\t = 0x%016lX\t\n", r_stvec());
    printf("scause\t = 0x%016lX\t", r_scause());
    printf("sie\t = 0x%016lX\t", r_sie());
    printf("sip\t = 0x%016lX\t\n", r_sip());
    printf("satp\t = 0x%016lX\t\n", r_satp());

    printf("pc = 0x%016lX\t", r_pc());
    printf("ra = 0x%016lX\t", r_ra());
    printf("sp = 0x%016lX\t\n", r_sp());
    printf("gp = 0x%016lX\t", r_gp());
    printf("tp = 0x%016lX\t", r_tp());
    printf("fp = 0x%016lX\t\n", r_fp());
}