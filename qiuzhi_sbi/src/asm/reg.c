#include <asm/reg.h>
#include <io/printf.h>

// 宏定义
#define MSTATUS_SIE 1

// 函数定义
void analyse_mstatus(u64_t mstatus)
{
    // SIE
    if(mstatus & (u64_t)(1 << MSTATUS_SIE))
    {
        // printf("")
    }
}