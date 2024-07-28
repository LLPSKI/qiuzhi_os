#include <dev/uart.h>
#include <io/printf.h>
#include <trap/m_trap.h>

void sbi_main(void)
{
    uart_init();
    uart_test();

    printf_reg();

    m_trap_init();

    // extern void trap_test(void);
    // trap_test();
    u64_t *addr = 0x200BFF8;
    u64_t mtime = *addr;

    printf("mtime = 0x%016lX\n", mtime);
    
    while(1);
}