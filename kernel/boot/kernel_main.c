#include <io/printf.h>
#include <mm/pmm.h>
// #include <mm/vmm.h>
#include <utils/string.h>

void kernel_main(u64_t hartid)
{
    
    pmm_init();
    printf_reg();
    // vmm_init();
    while(1);
    
}