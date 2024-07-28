#include <mm/pmm.h>
#include <mm/mem_config.h>
#include <mm/memlayout.h>
#include <utils/string.h>
#include <io/printf.h>
#include <feature.h>

// 内部类型定义 
typedef enum page_status_t
{
    BUILD_IN,
    FREE,
    USED
}page_status_t;
typedef struct page_t
{
    u64_t ref_cnt; // 表示引用该页的地址空间的数量
    page_status_t status;
    LIST_ENTRY(page_t) free_link;
}page_t;
typedef LIST_HEAD(, page_t) page_list_head_t;

// 静态变量定义
static u64_t free_pm_begin;
// static u64_t free_pm_end;
static u64_t total_page;
static u64_t page_build_in;
static u64_t page_avail;
static u64_t page_free;
static u64_t page_used;
static page_list_head_t pmm_free_page_list_head;
static page_t pmm_pages[(MEMORY << 20) >> PAGE_SIZE_SHIFT];

// 内部静态内联函数声明
// 使用了pmm_pages静态变量，所以需要静态修饰符
static __inline__ __attribute__((always_inline))
    u64_t page_to_ppn(page_t *p);
static __inline__ __attribute__((always_inline))
    u64_t ppn_to_pa(u64_t ppn);
static __inline__ __attribute__((always_inline))
    u64_t page_to_pa(page_t *p);
static __inline__ __attribute__((always_inline))
    u64_t pa_to_ppn(u64_t pa);
static __inline__ __attribute__((always_inline))
    page_t *ppn_to_page(u64_t ppn);
static __inline__ __attribute__((always_inline))
    page_t *pa_to_page(u64_t pa);


// 函数定义
void pmm_init(void)
{
    // 静态变量初始化
    extern char _end[]; // 引入自kernel.ld
    free_pm_begin = (u64_t)_end;
    total_page = (MEMORY << 20) >> PAGE_SIZE_SHIFT;
    page_build_in = (free_pm_begin - RAMBASE) >> PAGE_SIZE_SHIFT;
    page_avail = total_page - page_build_in;
    page_free = page_avail;
    page_used = 0;
    
    // pmm_pages初始化
    for(size_t i = 0; i < page_build_in; i++)
    {
        pmm_pages[i].status = BUILD_IN;
        pmm_pages[i].ref_cnt = 0;
    }
    for(size_t i = page_build_in; i < total_page; i++)
    {
        pmm_pages[i].status = FREE;
        pmm_pages[i].ref_cnt = 0;
    }

    // 初始化pmm_free_page_list
    LIST_INIT(&pmm_free_page_list_head);
    for(size_t i = page_build_in; i < total_page; i++)
    {
        LIST_INSERT_HEAD(&pmm_free_page_list_head, &pmm_pages[i], free_link);
    }

    pmm_info_print();
}
void pmm_info_print(void)
{
    printf("free_pm_begin = 0x%016lX\n", free_pm_begin);
    printf("total_page = %d\n", total_page);
    printf("page_build_in = %d\n", page_build_in);
    printf("page_avail = %d\n", page_avail);
    printf("page_free = %d\n", page_free);
    printf("page_used = %d\n", page_used);
    printf("pmm_pages -> 0x%016lX\n", pmm_pages);
}
void *pm_alloc(void)
{
    page_t *p = LIST_FIRST(&pmm_free_page_list_head);
    if(p == NULL) // 不存在空闲内存了
    {
        printf("pm_alloc: No free memory for use!\n");
        while(1);
    }
    
    LIST_REMOVE(p, free_link);
    page_free--;
    page_used++;

    p->status = USED;
    memset((void *)page_to_pa(p), 0, PAGE_SIZE);

    return (void *)page_to_pa(p);
}
// void page_dec_ref(u64_t pa)
// {
//     // 检查合法性
//     if(pa < free_pm_begin || pa >= RAMTOP) // 范围不对
//     {
//         printf("page_dec_ref: pa = 0x%016lX!\n", pa);
//         while(1);
//     }
//     page_t *p = pa_to_page(pa);
//     if(p->ref_cnt == 0) // 引用到free list中的page
//     {
//         printf("page_dec_ref: p->ref_cnt == 0!\n");
//         while(1);
//     }

//     p->ref_cnt--;
//     if(p->ref_cnt == 0)
//     {
//         LIST_INSERT_HEAD(&pmm_free_page_list_head, p, link);
//         page_free++;
//         page_used--;
//     }
// }
// void page_inc_ref(u64_t pa)
// {
//     // 检查合法性
//     if(pa < free_pm_begin || pa >= RAMTOP) // 范围不对
//     {
//         printf("page_inc_ref: pa = 0x%016lX!\n", pa);
//         while(1);
//     }
//     page_t *p = pa_to_page(pa);
//     if(p->ref_cnt == 0) // 引用到free list中的page
//     {
//         printf("page_inc_ref: p->ref_cnt == 0!\n");
//         while(1);
//     }

//     p->ref_cnt++;
// }
u64_t get_free_pm_begin(void)
{
    return free_pm_begin;
}


// 内部静态内联函数定义
static __inline__ __attribute__((always_inline)) 
    u64_t page_to_ppn(page_t *p)
{
    return (u64_t)(p - pmm_pages);
}
static __inline__ __attribute__((always_inline))
    u64_t ppn_to_pa(u64_t ppn)
{
    return (u64_t)((ppn << PAGE_SIZE_SHIFT) + RAMBASE);
}
static __inline__ __attribute__((always_inline))
    u64_t page_to_pa(page_t *p)
{
    return ppn_to_pa(page_to_ppn(p));
}
static __inline__ __attribute__((always_inline))
    u64_t pa_to_ppn(u64_t pa)
{
    return (u64_t)((pa - RAMBASE) >> PAGE_SIZE_SHIFT);
}
static __inline__ __attribute__((always_inline))
    page_t *ppn_to_page(u64_t ppn)
{
    return &pmm_pages[ppn];
}
static __inline__ __attribute__((always_inline))
    page_t *pa_to_page(u64_t pa)
{
    return ppn_to_page(pa_to_ppn(pa));
}