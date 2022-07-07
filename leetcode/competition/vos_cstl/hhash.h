#ifndef HHASH_H
#define HHASH_H

#include <stdbool.h>
#include <stdlib.h>

/* ��������������ַ�� */
#include "hlist.h"

/* 
 * �û����壬�ж������ڵ��Ƿ���ͬ
 * ����� node ָ�룡��ʹ�� NODE_ENTRY ��ȡ��Ӧ entry
 */
typedef bool (*HashEqualFunc)(const struct Node *a, const struct Node *b);

/*
 * �û����壬hash key ���ɺ������������� hash Ͱ
 * ����ֵ��Ӧ���� hash Ͱ��С���ƣ�
 * ����� node ָ�룡��ʹ�� NODE_ENTRY ��ȡ��Ӧ entry
 */
typedef size_t (*HashKeyFunc)(const struct Node *node, size_t bktSize);

/* 
 * Thomas Wong ����ɢ�к���
 * ����԰���ʹ�ã���ʵ����� HashKeyFunc
 * ע�⣺����ֵ�򳬹���ϣͰ��С����Ҫ��һ��������
 */
static inline size_t TwIntHash(unsigned int key)
{
    key = ~key + (key << 15);
    key = key ^ (key >> 12);
    key = key + (key << 2);
    key = key ^ (key >> 4);
    key = (key + (key << 3)) + (key << 11);
    key = key ^ (key >> 16);
    return (size_t)key;
}

/* 
 * BKDR �ַ���ɢ�к���
 * ����԰���ʹ�ã���ʵ����� HashKeyFunc
 * ע�⣺����ֵ�򳬹���ϣͰ��С����Ҫ��һ��������
 */
static inline size_t BkdrHash(const char *str)
{
    size_t hash = 0;
    register size_t ch = 0;
    while ((ch = (size_t)(*str++)) != '\0') {
        // hash = hash * 131 + ch;
        hash = (hash << 7) + (hash << 1) + hash + ch;
    }
    return hash;
}

struct HashTable {
    size_t bktSize;
    HashEqualFunc equal;
    HashKeyFunc key;
    struct List *bkts;
};

/* �ɹ����� 0��ʧ�ܷ��� -1 */
static inline int HashInit(struct HashTable *ht, 
                           size_t bktSize, 
                           HashEqualFunc equal, 
                           HashKeyFunc key)
{
    ht->bktSize = bktSize;
    ht->equal = equal;
    ht->key = key;
    ht->bkts = (struct List*)malloc(sizeof(struct List) * bktSize);
    if (ht->bkts == NULL) {
        return -1;
    }

    size_t i;
    for (i = 0; i < bktSize; i++) {
        ListInit(&ht->bkts[i]);
    }
    return 0;
}

/* ע�⣺NodeFunc ��������� node ���� entry! */
static inline void HashDeinit(struct HashTable *ht, NodeFunc nodeDeinit)
{
    if (nodeDeinit != NULL) {
        size_t i;
        for (i = 0; i < ht->bktSize; i++) {
            ListDeinit(&ht->bkts[i], nodeDeinit);
        }
    }
    free(ht->bkts);
}

static inline void HashAdd(struct HashTable *ht, struct Node *node)
{
    size_t k = ht->key(node, ht->bktSize);
    struct List *list = &ht->bkts[k];
    ListAddTail(list, node);
}

static inline void HashRemove(struct Node *node)
{
    ListRemove(node);
}

static inline struct Node *HashFind(const struct HashTable *ht, 
                                    const struct Node *cmpNode)
{
    size_t k = ht->key(cmpNode, ht->bktSize);
    struct List *list = &ht->bkts[k];
    struct Node *node;
    LIST_FOR_EACH(node, list) {
        if (ht->equal(cmpNode, node)) {
            return node;
        }
    }
    return NULL;
}

/* 
 * ����������ϣ�ڵ�
 * ע��: nodeProc ��������� node ָ�룡
 *       ����ʱ��Ҫ�ı� key ֵ�������ṹ��
 */
static inline void HashIterate(struct HashTable *ht,
                               NodeFuncX nodeProc,
                               void *arg)
{
    size_t i;
    for (i = 0; i < ht->bktSize; i++) {
        struct Node *node;
        LIST_FOR_EACH(node, &ht->bkts[i]) {
            nodeProc(node, arg);
        }
    }
}

/* 
 * ���ù�ϣ������������ rehash
 * ������ֵ�����ɱ���ԭֵ����
 * �ɹ����� 0��ʧ�ܷ��� -1��ʧ��ʱ��ԭ��ϣ���Կ�ʹ��
 */
static inline int HashReset(struct HashTable *ht, 
                            size_t bktSize, 
                            HashEqualFunc equal, 
                            HashKeyFunc key)
{
    bktSize = bktSize != 0 ? bktSize : ht->bktSize;
    equal = equal != NULL ? equal : ht->equal;
    key = key != NULL ? key : ht->key;

    struct HashTable newHt;
    int ret = HashInit(&newHt, bktSize, equal, key);
    if (ret != 0) {
        return -1;
    }

    size_t i;
    for (i = 0; i < ht->bktSize; i++) {
        struct List *list = &ht->bkts[i];
        struct Node *node, *tmp;
        LIST_FOR_EACH_SAFE(node, tmp, list) {
            HashAdd(&newHt, node);
        }
    }

    free(ht->bkts);
    *ht = newHt;
    return 0;
}


#endif /* HHASH_H */

