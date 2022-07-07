#ifndef HLIST_H
#define HLIST_H

#include <stddef.h>
#include <stdbool.h>

/* 
 * �ýṹ������Ƕ�뵽ҵ�����ݽṹ����(entry)������ʵ������
 * ����
 *     struct Entry {           // ���ҵ�����ݽṹ��
 *         ...
 *         struct Node node;    // Ƕ�����У�λ������
 *         ...
 *     };
 */
struct Node {
    struct Node *next, *prev;
};

/* 
 * �ɳ�Ա���� node ��ַ��ȡ�ṹ�� entry ��ַ
 * ����
 *     struct Entry entry;
 *     struct Node *n = &entry.node;
 *     struct Entry *p = NODE_ENTRY(n, struct Entry, node);
 *     ��ʱ p ָ�� entry
 */
#define NODE_ENTRY(node, type, member) \
    ((type*)((char*)(node) - (size_t)&((type*)0)->member))

/* 
 * �û����壬��� node �ڵ�Ĵ�������
 * ע��: ����� node ָ�룡
 * �������Ҫʹ�� NODE_ENTRY ����ȡ������ entry
 */
typedef void (*NodeFunc)(struct Node *node);

/* 
 * �û����壬��� node �ڵ�Ĵ�������������ѡ����
 * ע��: ����� node ָ�룡
 * �������Ҫʹ�� NODE_ENTRY ����ȡ������ entry
 */
typedef void (*NodeFuncX)(struct Node *node, void *arg);


/* ���ڱ��ڵ��˫������ */
struct List {
    struct Node base;
};

static inline void ListInit(struct List *list)
{
    list->base.next = &list->base;
    list->base.prev = &list->base;
}

static inline bool ListEmpty(const struct List *list)
{
    return list->base.next == &list->base;
}

static inline bool ListIsHead(const struct List *list, const struct Node *node)
{
    return list->base.next == node;
}

static inline bool ListIsTail(const struct List *list, const struct Node *node)
{
    return list->base.prev == node;
}

/* node ���뵽 pos ǰ�� */
static inline void ListInsert(struct Node *pos, struct Node *node)
{
    node->prev = pos->prev;
    node->next = pos;
    node->prev->next = node;
    node->next->prev = node;
}

static inline void ListAddTail(struct List *list, struct Node *node)
{
    ListInsert(&list->base, node);
}

static inline void ListAddHead(struct List *list, struct Node *node)
{
    ListInsert(list->base.next, node);
}

static inline void ListRemove(struct Node *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

static inline void ListRemoveTail(struct List *list)
{
    ListRemove(list->base.prev);
}

static inline void ListRemoveHead(struct List *list)
{
    ListRemove(list->base.next);
}

static inline void ListReplace(struct Node *old, struct Node *node)
{
    node->next = old->next;
    node->next->prev = node;
    node->prev = old->prev;
    node->prev->next = node;
}

#define LIST_FOR_EACH(node, list) \
    for (node = (list)->base.next; \
         node != &(list)->base; \
         node = (node)->next)

#define LIST_FOR_EACH_SAFE(node, tmp, list) \
    for (node = (list)->base.next, tmp = (node)->next; \
         node != &(list)->base; \
         node = tmp, tmp = (node)->next)

/* 
 * �������������ڵ�
 * ע��: nodeProc ��������� node ָ�룡
 *       ����ʱ��Ҫ�ı������ṹ��
 */
static inline void ListIterate(struct List *list,
                               NodeFuncX nodeProc,
                               void *arg)
{
    struct Node *node;
    LIST_FOR_EACH(node, list) {
        nodeProc(node, arg);
    }
}

/* ע�⣺NodeFunc ��������� node ���� entry! */
static inline void ListDeinit(struct List *list, NodeFunc nodeDeinit)
{
    if (nodeDeinit == NULL) {
        return;
    }

    struct Node *node, *tmp;
    LIST_FOR_EACH_SAFE(node, tmp, list) {
        nodeDeinit(node);
    }
}

/* ��ȡͷ��㣬��� */
#define LIST_HEAD_ENTRY(list, type, member) \
    (ListEmpty(list) ? NULL : NODE_ENTRY((list)->base.next, type, member))

/* ��ȡβ��㣬��� */
#define LIST_TAIL_ENTRY(list, type, member) \
    (ListEmpty(list) ? NULL : NODE_ENTRY((list)->base.prev, type, member))

/* ��ȡ��һ��㣬��� */
#define LIST_NEXT_ENTRY(entry, list, type, member) \
    (ListIsTail(list, &(entry)->member) ? \
        NULL : \
        NODE_ENTRY((entry)->member.next, type, member))

/* ��ȡ��һ��㣬��� */
#define LIST_PREV_ENTRY(entry, list, type, member) \
    (ListIsHead(list, &(entry)->member) ? \
        NULL : \
        NODE_ENTRY((entry)->member.prev, type, member))

/* �������������������������������ʹ�� _SAFE �汾 */
#define LIST_FOR_EACH_ENTRY(entry, list, type, member) \
    for (entry = NODE_ENTRY((list)->base.next, type, member); \
         &(entry)->member != &(list)->base; \
         entry = NODE_ENTRY((entry)->member.next, type, member))

#define LIST_FOR_EACH_ENTRY_SAFE(entry, tmp, list, type, member) \
    for (entry = NODE_ENTRY((list)->base.next, type, member), \
         tmp = NODE_ENTRY((entry)->member.next, type, member); \
         &(entry)->member != &(list)->base; \
         entry = tmp, tmp = NODE_ENTRY((entry)->member.next, type, member))

/* ����������������������������������ʹ�� _SAFE �汾 */
#define LIST_FOR_EACH_ENTRY_REVERSE(entry, list, type, member) \
    for (entry = NODE_ENTRY((list)->base.prev, type, member); \
         &(entry)->member != &(list)->base; \
         entry = NODE_ENTRY((entry)->member.prev, type, member))

#define LIST_FOR_EACH_ENTRY_REVERSE_SAFE(entry, tmp, list, type, member) \
    for (entry = NODE_ENTRY((list)->base.prev, type, member), \
         tmp = NODE_ENTRY((entry)->member.prev, type, member); \
         &(entry)->member != &(list)->base; \
         entry = tmp, tmp = NODE_ENTRY((entry)->member.prev, type, member))

#endif /* HLIST_H */

