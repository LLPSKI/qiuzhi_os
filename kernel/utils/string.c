#include <utils/string.h>
#include <mm/io.h>

//函数定义
void *memset(void *dst, u8_t c, size_t n)
{
    u64_t data;
    if(c == 0)
    {
        data = 0;
    }
    else
    {
        data = ((u64_t)c << 56) 
			 | ((u64_t)c << 48) 
			 | ((u64_t)c << 40) 
			 | ((u64_t)c << 32)
			 | ((u64_t)c << 24) 
			 | ((u64_t)c << 16) 
			 | ((u64_t)c << 8) 
			 | ((u64_t)c);
    }

    u64_t *cdst = dst;
    if((u64_t)cdst % 8 != 0) // 写入地址没有对齐
    {
        u8_t *tmp = (u8_t *)cdst;
        size_t po = 8 - ((u64_t)cdst & (8 - 1));
        for(size_t i = 0; i < po; i++)
        {
            mem_writeb((u64_t)&tmp[i], c);
        }
        cdst = (u64_t *)((u64_t)cdst + po);
        n -= po;
    }
    size_t s = n;
    for(size_t i = 0; i <= (n - 8); i += 8, s -= 8)
    {
        mem_writed((u64_t)cdst, data);
        cdst++;
    }
    n = s;

    if(n != 0) // 仍有剩余的
    {
        for(size_t i = 0; i < n; i++)
        {
            mem_writeb((u64_t)&cdst[i], c);
        }
    }

    return dst;
}