#ifndef _MM_PMM_H
#define _MM_PMM_H

#include <types.h>
#include <utils/list.h>

// 函数声明
void pmm_init(void);
void pmm_info_print(void);
void *pm_alloc(void);
// void page_dec_ref(u64_t pa);
// void page_inc_ref(u64_t pa);
u64_t get_free_pm_begin(void);

#endif /* _MM_PMM_H */