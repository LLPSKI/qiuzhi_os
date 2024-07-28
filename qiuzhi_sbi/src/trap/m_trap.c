#include <trap/m_trap.h>
#include <io/printf.h>
#include <asm/reg.h>

// 宏定义
// #define 

// 函数定义
void m_trap_init(void)
{
    extern void m_trap_entry(void);
    w_mtvec((u64_t)m_trap_entry);
    printf("mtvec = 0x%016lX\n", r_mtvec());
}
void m_trap_handler(m_trap_contexts *ctx)
{
    u64_t mcause = ctx->mcause;
    bool is_interrupt = (bool)(mcause & ((u64_t)1 << 63));
    u64_t ec = mcause & ~((u64_t)1 << 63);
    if(is_interrupt)
    {
        printf("中断处理尚未实现！\n");
        printf_reg();
        while(1);
    }
    else
    {
        switch(ec)
        {
            default:
                printf("异常处理尚未实现！\n");
                printf_reg();
                while(1);
            break;
        }
        
    }
}