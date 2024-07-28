#ifndef _TYPES_H
#define _TYPES_H

typedef char i8_t;
typedef short i16_t;
typedef int i32_t;
typedef long i64_t;

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;
typedef unsigned long u64_t;

typedef u32_t size_t;

typedef enum bool
{ 
	false = 0, 
	true = 1 

}bool;

#define NULL ((void *)0)

#endif /* _TYPES_H */