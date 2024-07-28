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
    
    printf("mvendorid = 0x%016lX\n", r_mvendorid());
    printf("marchid = 0x%016lX\n", r_marchid());
    printf("mimpid = 0x%016lX\n", r_mimpid());
    printf("mhartid = 0x%016lX\n", r_mhartid());
    // printf("mconfigptr = 0x%016lX\n", r_mconfigptr());
    printf("misa = 0x%016lX\n", r_misa());
    printf("mstatus = 0x%016lX\n", r_mstatus());
    printf("mepc = 0x%016lX\n", r_mepc());
    printf("mtval = 0x%016lX\n", r_mtval());
    printf("mtvec = 0x%016lX\n", r_mtvec());
    printf("mcause = 0x%016lX\n", r_mcause());
    printf("mie = 0x%016lX\n", r_mie());
    printf("mip = 0x%016lX\n", r_mip());
    printf("mideleg = 0x%016lX\n", r_mideleg());
    printf("medeleg = 0x%016lX\n", r_medeleg());
    printf("pc = 0x%016lX\n", r_pc());
    printf("ra = 0x%016lX\n", r_ra());
    printf("sp = 0x%016lX\n", r_sp());
    printf("gp = 0x%016lX\n", r_gp());
    printf("tp = 0x%016lX\n", r_tp());
    printf("fp = 0x%016lX\n", r_fp());
}