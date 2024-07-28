#ifndef _UTILS_LIST_H
#define _UTILS_LIST_H

// 宏定义
/*
    name：链表头结构名称
    type：链表元素类型
*/
#define LIST_HEAD(name, type) \
struct name \
{ \
    struct type *lh_first; \
}
#define LIST_ENTRY(type) \
struct \
{ \
    struct type *le_next; \
    struct type **le_prev; \
}
#define LIST_INIT(head) \
do{ \
    (head)->lh_first = NULL; \
}while(0)
#define LIST_FIRST(head) ((head)->lh_first)
// #define LIST_INSERT_AFTER()
#define LIST_INSERT_HEAD(head, elm, field) \
{ \
    if(((elm)->field.le_next = (head)->lh_first) != NULL) \
    { \
        (head)->lh_first->field.le_prev = &(elm)->field.le_next; \
    } \
    (head)->lh_first = (elm); \
    (elm)->field.le_prev = &(head)->lh_first; \
}
#define LIST_REMOVE(elm, field) \
do{ \
    if((elm)->field.le_next != NULL) \
    { \
        (elm)->field.le_next->field.le_prev = (elm)->field.le_prev; \
    } \
    *(elm)->field.le_prev = (elm)->field.le_next; \
}while(0)


#endif /* _UTILS_LIST_H */