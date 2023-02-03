/*
 * @file vos_hash.h
 * Description: hash表实现文件
 */

#ifndef VOS_HASH_IMPL_H
#define VOS_HASH_IMPL_H
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hhash.h" // cstl 1.3
#include "hlist.h" // cstl 1.3

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HashTable CstlHashTable;
typedef struct Node CstlNode;
typedef struct List CstlList;

struct vosHash {
    VosHashCodeCalcFunc hashFunc; // 哈希函数
    VosHashMatchFunc matchFunc;   // 匹配函数
    VosDupFreeFuncPair keyFunc;
    VosDupFreeFuncPair dataFunc;
    size_t hashSize;  // Hash表大小
    void* rawHashTbl; // 保存cstl1.3 HashTable 的指针
    size_t nodeCnt;
};

typedef struct tagHashNode {
    uintptr_t key;
    uintptr_t value;
    VosHash* origHashTbl; // 节点内反过来存储VosHashTable，这样才可以访问到比较函数等,只存储hash table指针比较省空间
    CstlNode node;
} VosHashNode;

static inline CstlNode *HashFirstNodeByBktIndex(const CstlHashTable *ht, size_t bktIndex)
{
    for (size_t i = bktIndex; i < ht->bktSize; i++) {
        CstlList *list = &ht->bkts[i];
        if (!ListEmpty(list)) {
            return list->base.next;
        }
    }
    return NULL;
}

static inline CstlNode *HashFirstNode(const CstlHashTable *ht)
{
    return HashFirstNodeByBktIndex(ht, 0);
}

static inline CstlNode *HashNextNode(const CstlHashTable *ht, const CstlNode *fromNode)
{
    size_t k = ht->key(fromNode, ht->bktSize);
    CstlList *list = &ht->bkts[k];
    if (ListIsTail(list, fromNode)) {
        return HashFirstNodeByBktIndex(ht, ++k);
    }
    return fromNode->next;
}

static inline void FreeDataEntry(VosHashNode *entry)
{
    VosHash *hash = entry->origHashTbl;
    if (hash->keyFunc.freeFunc != NULL) {
        hash->keyFunc.freeFunc((void*)entry->key);
    }

    if (hash->dataFunc.freeFunc != NULL) {
        hash->dataFunc.freeFunc((void*)entry->value);
    }
    free(entry);
}

static inline bool AdaptDataEntryMatch(const CstlNode *a, const CstlNode *b)
{
    VosHashNode *d1 = NODE_ENTRY(a, VosHashNode, node);
    VosHashNode *d2 = NODE_ENTRY(b, VosHashNode, node);
    VosHash *hash = d1->origHashTbl;
    if (hash->matchFunc != NULL) {
        return hash->matchFunc(d1->key, d2->key);
    }
    return false;
}

// 这个是cstl1.3 的接口类型，不要修改
static inline size_t AdaptDataEntryKey(const CstlNode *node, size_t bktSize)
{
    VosHashNode *e = NODE_ENTRY(node, VosHashNode, node);
    VosHash *hash = e->origHashTbl;

    if (hash->hashFunc != NULL) {
        return (size_t)hash->hashFunc(e->key, hash->hashSize);
    }
    // 如果没有 hashFunc，默认当 int 处理
    size_t pc = TwIntHash(*(int*)e->key);
    return (pc % bktSize);
}

static inline void FreeListNode(CstlNode *node)
{
    VosHashNode *entry = NODE_ENTRY(node, VosHashNode, node);
    FreeDataEntry(entry);
}

static inline void VosHashHookRegister(VosHash *hash,
                                       VosHashCodeCalcFunc hashFunc,
                                       VosHashMatchFunc matchFunc,
                                       VosDupFreeFuncPair *keyFunc,
                                       VosDupFreeFuncPair *dataFunc)
{
    if (hashFunc == NULL) {
        hash->hashFunc = VOS_HashCodeCalcInt;
    } else {
        hash->hashFunc = hashFunc;
    }

    if (matchFunc == NULL) {
        hash->matchFunc = VOS_HashMatchInt;
    } else {
        hash->matchFunc = matchFunc;
    }

    if (keyFunc == NULL) {
        hash->keyFunc.dupFunc = NULL;
        hash->keyFunc.freeFunc = NULL;
    } else {
        hash->keyFunc.dupFunc = keyFunc->dupFunc;
        hash->keyFunc.freeFunc = keyFunc->freeFunc;
    }

    if (dataFunc == NULL) {
        hash->dataFunc.dupFunc = NULL;
        hash->dataFunc.freeFunc = NULL;
    } else {
        hash->dataFunc.dupFunc = dataFunc->dupFunc;
        hash->dataFunc.freeFunc = dataFunc->freeFunc;
    }
}

static inline VosHash *VOS_HashCreate(size_t bktSize,
                                      VosHashCodeCalcFunc hashFunc,
                                      VosHashMatchFunc matchFunc,
                                      VosDupFreeFuncPair *keyFunc,
                                      VosDupFreeFuncPair *valueFunc)
{
    CstlHashTable* ht =  (CstlHashTable*)malloc(sizeof(CstlHashTable));
    if (ht == NULL) {
        return NULL;
    }

    int ret = HashInit(ht, (size_t)bktSize, AdaptDataEntryMatch, AdaptDataEntryKey);
    if (ret == -1) {
        free(ht);
        return NULL;
    }

    VosHash *hash = (VosHash*)calloc(1, sizeof(VosHash));
    if (hash == NULL) {
        HashDeinit(ht, FreeListNode);
        free(ht);
        return NULL;
    }
    hash->hashSize = bktSize;

    VosHashHookRegister(hash, hashFunc, matchFunc, keyFunc, valueFunc);

    hash->rawHashTbl = ht; // 保存cstl1.3 CstlHashTable 的指针
    hash->nodeCnt = 0;

    return hash;
}

// 插入一个不存在的节点
static inline uint32_t VOS_HashInsNonexistentNode(VosHash *hash, uintptr_t key, uintptr_t value)
{
    VosHashNode* newNode = (VosHashNode*)malloc(sizeof(VosHashNode));
    if (newNode == NULL) {
        return VOS_ERROR;
    }
    if (hash->keyFunc.dupFunc != NULL) {
        newNode->key = (uintptr_t)hash->keyFunc.dupFunc((void*)key);
    } else {
        newNode->key = key;
    }

    if (hash->dataFunc.dupFunc != NULL) {
        newNode->value = (uintptr_t)hash->dataFunc.dupFunc((void*)value);
    } else {
        newNode->value = value;
    }

    CstlHashTable *ht = (CstlHashTable*)hash->rawHashTbl;
    newNode->origHashTbl = hash;
    HashAdd(ht, &newNode->node);
    hash->nodeCnt++;

    return VOS_OK;
}

static inline uint32_t VOS_HashInsert(VosHash *hash, uintptr_t key, uintptr_t value)
{
    if (VOS_HashFind(hash, key) != VOS_HashIterEnd(hash)) {
        return VOS_ERROR;
    }

    return VOS_HashInsNonexistentNode(hash, key, value);
}

static inline uint32_t VOS_HashPut(VosHash *hash, uintptr_t key, uintptr_t value)
{
    VosHashIterator it = VOS_HashFind(hash, key);
    if (it == VOS_HashIterEnd(hash)) { // If the node does not exist, add it
        return VOS_HashInsNonexistentNode(hash, key, value);
    }
    VosHashNode *entry = NODE_ENTRY(it, VosHashNode, node);
    if (entry->value == value) {
        return VOS_OK;
    }

    if (hash->dataFunc.freeFunc != NULL) {
        hash->dataFunc.freeFunc((void*)entry->value);
    }
    if (hash->dataFunc.dupFunc != NULL) {
        entry->value = (uintptr_t)hash->dataFunc.dupFunc((void*)value);
    } else {
        entry->value = value;
    }
    return VOS_OK;
}

static inline VosHashIterator VOS_HashFind(const VosHash *hash, uintptr_t key)
{
    VosHashNode cmpNode = {};
    cmpNode.key = key;
    cmpNode.origHashTbl = (VosHash*)hash;

    CstlHashTable *ht = (CstlHashTable*)hash->rawHashTbl;
    CstlNode *node = HashFind(ht, &cmpNode.node);
    if (node != NULL) {
        return node;
    }
    return VOS_HashIterEnd(hash);
}

static inline uint32_t VOS_HashAt(const VosHash *hash, uintptr_t key, uintptr_t *value)
{
    CstlNode* node = (CstlNode*)VOS_HashFind(hash, key);
    if (node != VOS_HashIterEnd(hash)) {
        if (value != NULL) {
            VosHashNode *entry = NODE_ENTRY(node, VosHashNode, node);
            *value = entry->value;
        }
        return VOS_OK;
    }
    return VOS_ERROR;
}

static inline VosHashIterator VOS_HashErase(VosHash *hash, uintptr_t key)
{
    CstlNode* node = (CstlNode*)VOS_HashFind(hash, key);
    if (node != VOS_HashIterEnd(hash)) {
        CstlHashTable *ht = (CstlHashTable*)hash->rawHashTbl;
        CstlNode *nextNode = HashNextNode(ht, node);

        VosHashNode *entry = NODE_ENTRY(node, VosHashNode, node);
        HashRemove(node);
        hash->nodeCnt--;
        FreeDataEntry(entry);

        if (nextNode != NULL) {
            return nextNode;
        }
    }
    return VOS_HashIterEnd(hash);
}

static inline size_t VOS_HashSize(const VosHash *hash)
{
    return hash->nodeCnt;
}

static inline bool VOS_HashEmpty(const VosHash *hash)
{
    return VOS_HashSize(hash) == 0;
}

// 执行 VOS_HashClear 时只清除内容，不释放HASH桶
static inline void VOS_HashClear(VosHash *hash)
{
    CstlHashTable *ht = (CstlHashTable*)hash->rawHashTbl;
    // HashDeinit 会释放hash桶，这样会导致后面的查找coredump，所以需要再次初始化
    HashDeinit(ht, FreeListNode);
    (void)HashInit(ht, hash->hashSize, AdaptDataEntryMatch, AdaptDataEntryKey);
    hash->nodeCnt = 0;
}

static inline void VOS_HashDestroy(VosHash *hash)
{
    CstlHashTable *ht = (CstlHashTable*)hash->rawHashTbl;
    HashDeinit(ht, FreeListNode);
    free(ht);
    free(hash);
}

static inline VosHashIterator VOS_HashIterBegin(const VosHash *hash)
{
    CstlHashTable *ht = (CstlHashTable*)hash->rawHashTbl;
    CstlNode *node = HashFirstNode(ht);
    if (node != NULL) {
        return node;
    }
    return VOS_HashIterEnd(hash);
}

static inline VosHashIterator VOS_HashIterNext(const VosHash *hash, VosHashIterator it)
{
    CstlHashTable *ht = (CstlHashTable*)hash->rawHashTbl;
    CstlNode *node = HashNextNode(ht, (const CstlNode *)it);
    if (node != NULL) {
        return node;
    }
    return VOS_HashIterEnd(hash);
}

static inline VosHashIterator VOS_HashIterEnd(const VosHash *hash)
{
    CstlHashTable *ht = (CstlHashTable*)hash->rawHashTbl;
    CstlList *list = &ht->bkts[ht->bktSize - 1];
    return &list->base;
}

static inline uintptr_t VOS_HashIterKey(const VosHash *hash, VosHashIterator it)
{
    VosHashNode *entry = NODE_ENTRY(it, VosHashNode, node);
    return entry->key;
}

static inline uintptr_t VOS_HashIterValue(const VosHash *hash, VosHashIterator it)
{
    VosHashNode *entry = NODE_ENTRY(it, VosHashNode, node);
    return entry->value;
}

// 默认的整型哈希函数
static inline size_t VOS_HashCodeCalcInt(uintptr_t key, size_t bktSize)
{
    size_t pc = (size_t)TwIntHash((unsigned int)key);
    return (pc % bktSize);
}

// 默认的整型匹配函数
static inline bool VOS_HashMatchInt(uintptr_t key1, uintptr_t key2)
{
    return key1 == key2;
}

// 默认的字符串哈希函数
static inline size_t VOS_HashCodeCalcStr(uintptr_t key, size_t bktSize)
{
    uint32_t k = (uint32_t)BkdrHash((const char*)key);
    return k % bktSize;
}

// 默认的字符串匹配函数
static inline bool VOS_HashMatchStr(uintptr_t key1, uintptr_t key2)
{
    char *tkey1 = (char *)key1;
    char *tkey2 = (char *)key2;
    if (strcmp(tkey1, tkey2) == 0) {
        return true;
    }
    return false;
}

#ifdef __cplusplus
}
#endif

#endif
