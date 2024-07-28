#include <mm/vmm.h>
#include <mm/pmm.h>
#include <mm/mem_config.h>
#include <mm/memlayout.h>
#include <mm/io.h>
#include <io/printf.h>

// 内部类型定义
typedef u64_t pte_t;


// 静态函数声明
static void vm_map(pte_t *pt, u64_t pa, u64_t va, size_t len, u64_t perm);
static pte_t *pt_walk(u64_t *pt, u64_t va, bool create);
static void pte_modify(pte_t *pte, pte_t value);
static __inline__ __attribute__((always_inline))
    u64_t pte_to_pa(pte_t pte);
static __inline__ __attribute__((always_inline))
    pte_t pa_to_pte(u64_t pa);


// 宏定义
// Sv39 页表结构
#define PT_LEVELS       3
#define PT_INDEX_LEN    9
#define PT_INDEX(va, level) \
(((u64_t)va >> (PAGE_SIZE_SHIFT + (PT_LEVELS - level) * \
PT_INDEX_LEN)) & 0x1FF)
#define PTE_V           (1 << 0)
#define PTE_R           (1 << 1)
#define PTE_W           (1 << 2)
#define PTE_X           (1 << 3)
#define PTE_PPN_SHIFT   10


// 静态变量定义
static u64_t *kernel_pt;


// 函数定义
void vmm_init(void)
{
    kernel_pt = (u64_t *)pm_alloc();
}


// 静态函数定义
static void vm_map(pte_t *pt, u64_t pa, u64_t va, size_t len, u64_t perm)
{

}
static pte_t *pt_walk(u64_t *pt, u64_t va, bool create)
{
    u64_t *top_pt = pt;
    u64_t *cur_pt = top_pt;

    for(size_t i = 0; i < PT_LEVELS; i++)
    {
        pte_t *cur_pte = &cur_pt[PT_INDEX(va, i)];
        if(*cur_pte & PTE_V) // 该页表项有效
        {
            cur_pt = (pte_t *)pte_to_pa(*cur_pte);
        }
        else // 该页表项无效
        {
            if(create) // 创建
            {
                u64_t *new_page = (u64_t *)pm_alloc();
                pte_modify(cur_pte, 
                    pa_to_pte((u64_t)new_page) | PTE_V);

            }
            else // 不创建
            {
                return NULL;
            }
        }
    }
}
static void pte_modify(pte_t *pte, pte_t value)
{
    // 获取对应映射地址
    u64_t oldpa = pte_to_pa(*pte);
    u64_t newpa = pte_to_pa(value);

    // 检查合法性
    u64_t free_mem_begin = get_free_pm_begin();
    if((oldpa < free_mem_begin || oldpa >= RAMTOP) 
    || (newpa < free_mem_begin || newpa >= RAMTOP))
    {
        printf("pte_modify: ");
        printf("oldpa = 0x%016lX ", oldpa);
        printf("newpa = 0x%016lX\n", newpa);
        while(1);
    }

    if((oldpa = newpa) || ((*pte & PTE_V) == 0))
    {   
        // 映射相同或者当前页表项无效
        // 可以随意更改
        mem_writed((u64_t)pte, (u64_t)value);
    }
    else // 映射发生变化且当前页表项有效
    {
        // page_dec_ref(oldpa);
        mem_writed((u64_t)pte, (u64_t)value);
        // page_inc_ref(newpa);
    }
}


// 静态函数实现
static __inline__ __attribute__((always_inline))
    u64_t pte_to_pa(pte_t pte)
{
    return (u64_t)((pte >> PTE_PPN_SHIFT) << PAGE_SIZE_SHIFT);
}
static __inline__ __attribute__((always_inline))
    pte_t pa_to_pte(u64_t pa)
{
    return (pte_t)((pa >> PAGE_SIZE_SHIFT) << PTE_PPN_SHIFT);
}