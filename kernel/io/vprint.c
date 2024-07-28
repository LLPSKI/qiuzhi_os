#include <io/vprint.h>

// 静态函数声明
static void print_num(fmt_callback_t out, u64_t num, 
    u8_t base, bool neg_flag, size_t length, bool align, 
    u8_t padc, bool upcase);
static void print_str(fmt_callback_t out, const u8_t *s, 
    size_t length, bool align);
static void print_char(fmt_callback_t out, u8_t c, 
    size_t length, bool align);

// 函数实现
void vprintfmt(fmt_callback_t out, const u8_t *fmt, 
    va_list ap)
{
    const u8_t *s;
    bool align;
    u8_t padc;
    size_t width;
    bool long_flag;
    i64_t num;
    while(1)
    {
        // 扫描到下一个'%'
		size_t length = 0;
		s = fmt;
		for(; *fmt != '\0'; fmt++) 
		{
			if(*fmt != '%') 
			{
				length++;
			} 
			else 
			{
				out(s, length);
				length = 0;
				fmt++; // 跳过%
				break;
			}
		}

        // 处理扫描到尾的情况
        out(s, length);
        if(!*fmt)
        {
            break;
        }

        // 处于下一个%的位置
        align = true;   // 默认右对齐
        padc = ' ';     // 默认空格填充
        if(*fmt == '-') // 左对齐
        {
            align = false;
            padc = ' ';
            fmt++;
        }
        else if(*fmt == '0') // 0填充
        {
            align = true;
            padc = '0';
            fmt++;
        }

        // 得到输出宽度
        width = 0;
        while((*fmt >= '0') && (*fmt <= '9'))
        {
            width = width * 10 + (*fmt) - '0';
            fmt++;
        }

        long_flag = false;
        while(*fmt == 'l')
        {
            long_flag = true;
            fmt++;
        }
        
        bool neg_flag = false;
        u8_t c;
        u8_t *s;
        switch(*fmt)
        {
            case 'b':
                if(long_flag)
                {
                    num = va_arg(ap, i64_t);
                }
                else
                {
                    num = va_arg(ap, i32_t);
                }
                print_num(out, (u64_t)num, 2, false, 
                    width, align, padc, false);
                break;
            
            case 'd':
            case 'D':
                if(long_flag)
                {
                    num = va_arg(ap, i64_t);
                }
                else
                {
                    num = va_arg(ap, i32_t);
                }
                if(num < 0)
                {
                    num = -num;
                    neg_flag = true;
                }
                print_num(out, (u64_t)num, 10, neg_flag, 
                    width, align, padc, false);
            break;
            
            case 'o':
            case 'O':
                if(long_flag)
                {
                    num = va_arg(ap, i64_t);
                }
                else
                {
                    num = va_arg(ap, i32_t);
                }
                print_num(out, (u64_t)num, 8, false, 
                    width, align, padc, false);
            break;

            case 'u':
            case 'U':
                if(long_flag)
                {
                    num = va_arg(ap, i64_t);
                }
                else
                {
                    num = va_arg(ap, i32_t);
                }
                print_num(out, (u64_t)num, 10, false, 
                    width, align, padc, false);
            break;

            case 'x':
            case 'p':
                if(long_flag)
                {
                    num = va_arg(ap, i64_t);
                }
                else
                {
                    num = va_arg(ap, i32_t);
                }
                print_num(out, (u64_t)num, 16, false, 
                    width, align, padc, false);
            break;

            case 'X':
                if(long_flag)
                {
                    num = va_arg(ap, i64_t);
                }
                else
                {
                    num = va_arg(ap, i32_t);
                }
                print_num(out, (u64_t)num, 16, false, 
                    width, align, padc, true);
            break;

            case 'c':
                c = (u8_t)va_arg(ap, i32_t);
                print_char(out, c, width, align);
            break;

            case 's':
                s = (u8_t *)va_arg(ap, u8_t *);
                print_str(out, s, width, align);
            break;

            case '\0':
                fmt--;
            break;

            default:
                out(fmt, 1);
        }
        fmt++;
    }
}

// 静态函数实现
static void print_num(fmt_callback_t out, u64_t num, 
    u8_t base, bool neg_flag, size_t length, bool align, 
    u8_t padc, bool upcase)
{
    u8_t output_buf[length + 64]; // 本地缓冲区，不能多个线程同时使用该函数
    u8_t *p = output_buf;
    do
    {
        u8_t tmp = (u8_t)(num % base);
        if(tmp <= 9)
        {
            *p++ = '0' + tmp;
        }
        else if(upcase)
        {
            *p++ = 'A' + tmp - 10;
        }
        else 
        {
            *p++ = 'a' + tmp - 10;
        }
        num /= base;
    }while(num != 0);

    if(neg_flag)
    {
        *p++ = '-';
    }

    size_t actual_length = p - output_buf;
    if(length < actual_length)
    {
        length = actual_length;
    }

    if(align == false) // 左对齐
    {
        padc = ' '; // 必须是空格填充
    }

    if(neg_flag && align && (padc == '0'))
    {
        for(size_t i = actual_length - 1; i < length - 1; i++)
        {
            output_buf[i] = padc;
        }
        output_buf[length - 1] = '-';
    }
    else
    {
        for(size_t i = actual_length; i < length; i++)
        {
            output_buf[i] = padc;
        }
    }

    size_t begin = 0;
    size_t end;
    if(align) // 右对齐
    {
        end = length - 1;
    }
    else
    {
        end = actual_length - 1;
    }

    while(end > begin)
    {
        u8_t tmp = output_buf[begin];
        output_buf[begin] = output_buf[end];
        output_buf[end] = tmp;
        begin++;
        end--;
    }
    out(output_buf, length);
}

static void print_str(fmt_callback_t out, const u8_t *s, 
    size_t length, bool align)
{
    // 得到真实长度
    size_t actual_length = 0;
    const u8_t *s1 = s;
    while(*s1++)
    {
        actual_length++;
    }
    if(length < actual_length)
    {
        length = actual_length;
    }

    if(align) // 右对齐
    {
        // 左侧进行填充
        for(size_t i = 0; i < length - actual_length; i++)
        {
            out(" ", 1);
        }
        out(s, actual_length);
    }
    else // 左对齐
    {
        out(s, actual_length);
        for(size_t i = actual_length; i < length; i++)
        {
            out(" ", 1);
        }
    }
}

static void print_char(fmt_callback_t out, u8_t c, 
    size_t length, bool align)
{
    if(length == 0)
    {
        length = 1;
    }

    if(align) // 右对齐
    {
        for(size_t i = 0; i < length - 1; i++)
        {
            out(" ", 1);
        }
        out(&c, 1);
    }
    else // 左对齐
    {
        out(&c, 1);
        for(size_t i = 0; i < length - 1; i++)
        {
            out(" ", 1);
        }
    }
}