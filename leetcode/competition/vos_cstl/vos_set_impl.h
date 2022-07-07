/**
 * @defgroup vos_set
 * @ingroup cstl
 */
#include <stdlib.h>
#include <stdbool.h>
#include "vos_common.h"
#include "rbtree.h" // from https://github.com/forhappy/rbtree

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rb_node rbtree_node;

/**
 * @ingroup vos_set
 * vos_set节点
 */
typedef struct tagVosSetNode {
    rbtree_node rbtNode;
    uintptr_t  key;
}VosSetNode;

/**
 * @ingroup vos_set
 * vos_set控制块
 */
struct tagVosSet {
    struct rb_root      tree;
    VosKeyCmpFunc       keyCmpFunc;
    VosDupFreeFuncPair  keyFunc;
    VosDupFreeFuncPair  dataFunc;

    size_t nodeCnt; /* 树上的结点数目 */
};

static inline void VosSetHookRegister(VosSet *set,
                                      VosKeyCmpFunc keyCmpFunc,
                                      VosDupFreeFuncPair *keyFunc)
{
    if (keyFunc == NULL) {
        set->keyFunc.dupFunc = NULL;
        set->keyFunc.freeFunc = NULL;
    } else {
        set->keyFunc.dupFunc = keyFunc->dupFunc;
        set->keyFunc.freeFunc = keyFunc->freeFunc;
    }

    if (keyCmpFunc == NULL) {
        set->keyCmpFunc = VOS_IntCmpFunc;
    } else {
        set->keyCmpFunc = keyCmpFunc;
    }
}

/* 删除当前节点并返回下一个节点 */
static inline VosSetIterator VosSetNodeErase(VosSet *set, VosSetIterator it)
{
    VosSetIterator nextIt;
    nextIt = VOS_SetIterNext(set, it);

    rb_erase(&it->rbtNode, &set->tree);
    
    if (set->keyFunc.freeFunc != NULL) {
        set->keyFunc.freeFunc((void *)it->key);
    }

    free((void*)it);
    set->nodeCnt--;
    return nextIt;
}

static inline VosSet *VOS_SetCreate(VosKeyCmpFunc keyCmpFunc, VosDupFreeFuncPair *keyFunc)
{
    VosSet *set = (VosSet *)calloc(1, sizeof(VosSet));
    if (set == NULL) {
        VOS_PRINTF("[vos_set] malloc failed. File = %s, line = %d.\n", __FILE__, __LINE__);
        return NULL;
    }

    VosSetHookRegister(set, keyCmpFunc, keyFunc);

    return set;
}

static inline VosSetNode *VosSetNodeCreate(VosSet *set, uintptr_t key)
{
    VosSetNode *setNode = (VosSetNode *)malloc(sizeof(VosSetNode));
    if (setNode == NULL) {
        VOS_PRINTF("[vos_set] malloc failed. File = %s, line = %d.\n", __FILE__, __LINE__);
        return NULL;
    }

    uintptr_t  userKey;
    if (set->keyFunc.dupFunc != NULL) {
        userKey = (uintptr_t)set->keyFunc.dupFunc((void *)key);
        if (userKey == (uintptr_t)NULL) {
            /* 考虑用户返回失败的场景 */
            free(setNode);
            return NULL;
        }
    } else {
        userKey = key;
    }

    setNode->key = userKey;

    return setNode;
}

static inline uint32_t VosSetInsertLocate(VosSet *set, uintptr_t key, rbtree_node **parent, rbtree_node ***bestNode)
{
    rbtree_node *nilt = NULL;
    rbtree_node *tmpParent = nilt;
    rbtree_node **tmpBestNode = &set->tree.rb_node;
    VosKeyCmpFunc cmpFunc = set->keyCmpFunc;
    while (*tmpBestNode != nilt) {
        tmpParent = *tmpBestNode;

        VosSetNode *tmpNode = VOS_CONTAINER_OF(*tmpBestNode, VosSetNode, rbtNode);
        /* keycmpFunc的原型修改:入参类型修改为uintptr_t，把用户保存的数据返还用户，用户可以更直观的感知其自身的数据 */
        int32_t ret = cmpFunc(key, tmpNode->key);
        if (ret > 0) {
            tmpBestNode = &((*tmpBestNode)->rb_right);
        } else if (ret < 0) {
            tmpBestNode = &((*tmpBestNode)->rb_left);
        } else {
            return VOS_ERROR;
        }
    }

    *parent = tmpParent;
    *bestNode = tmpBestNode;
    return VOS_OK;
}

static inline uint32_t VOS_SetInsert(VosSet *set, uintptr_t key)
{
    rbtree_node *parent, **bestNode;

    if (set == NULL) {
        VOS_PRINTF("[vos_set] set is NULL pointer. File = %s, line = %d.\n", __FILE__, __LINE__);
        return VOS_ERROR;
    }

    /* 查找key对应的插入位置，返回VOS_ERROR表示key已经存在 */
    uint32_t ret = VosSetInsertLocate(set, key, &parent, &bestNode);
    if (ret != VOS_OK) {
        VOS_PRINTF("[vos_set] this key is exist. File = %s, line = %d.\n", __FILE__, __LINE__);
        return ret;
    }

    VosSetNode *setNode = VosSetNodeCreate(set, key);
    if (setNode == NULL) {
        VOS_PRINTF("[vos_set] create set node failed. File = %s, line = %d.\n", __FILE__, __LINE__);
        return VOS_ERROR;
    }
    rb_link_node(&setNode->rbtNode, parent, bestNode);
    rb_insert_color(&setNode->rbtNode, &set->tree);
    set->nodeCnt++;

    return VOS_OK;
}

static inline VosSetIterator VOS_SetIterEnd(const VosSet *set)
{
    return NULL;
}

static inline VosSetIterator VOS_SetErase(VosSet *set, uintptr_t key)
{
    VosSetIterator it = VOS_SetFind(set, key);
    if (it == VOS_SetIterEnd(set)) {
        return it;
    }

    return VosSetNodeErase(set, it);
}

static inline VosSetIterator VOS_SetFind(const VosSet *set, uintptr_t key)
{
    if (set == NULL) {
        VOS_PRINTF("[vos_set] set is NULL. File = %s, line = %d.\n", __FILE__, __LINE__);
        return NULL;
    }

    VosKeyCmpFunc cmpFunc = set->keyCmpFunc;
    rbtree_node *rbtNode = set->tree.rb_node;
    rbtree_node *nilt = NULL;

    while (rbtNode != nilt) {
        VosSetNode *tmpNode = VOS_CONTAINER_OF(rbtNode, VosSetNode, rbtNode);

        int32_t ret = cmpFunc(key, tmpNode->key);
        if (ret > 0) {
            rbtNode = rbtNode->rb_right;
        } else if (ret < 0) {
            rbtNode = rbtNode->rb_left;
        } else {
            return tmpNode;
        }
    }    
    /* 沒查到，返回VOS_SetIterEnd() */
    return (VosSetIterator)rbtNode;
}

static inline size_t VOS_SetSize(const VosSet *set)
{
    if (set == NULL) {
        return 0;
    }

    return set->nodeCnt;
}

static inline bool VOS_SetEmpty(const VosSet *set)
{
    if (set == NULL) {
        VOS_PRINTF("[vos_set] set is NULL. File = %s, line = %d.\n", __FILE__, __LINE__);
        return true;
    }
    return (set->nodeCnt == 0);
}

static inline VosSetNode* GetSetNodeByRbNode(rbtree_node *rbtNode)
{
    if (rbtNode == NULL) {
        return NULL;
    }
    VosSetNode *setNode = VOS_CONTAINER_OF(rbtNode, VosSetNode, rbtNode);
    return setNode;
}

static inline VosSetIterator VOS_SetIterBegin(const VosSet *set)
{
    if (set == NULL) {
        return NULL;
    }
    rbtree_node *rbtNode  = rb_first(&set->tree);
    VosSetNode *setNode = GetSetNodeByRbNode(rbtNode);
    return setNode;
}

static inline VosSetIterator VOS_SetIterNext(const VosSet *set, VosSetIterator it)
{
    if ((set == NULL) || (it == NULL) || (it == VOS_SetIterEnd(set))) {
        return VOS_SetIterEnd(set);
    }

    rbtree_node *rbtNode = rb_next(&it->rbtNode);
    VosSetNode *setNode = GetSetNodeByRbNode(rbtNode);
    return setNode;
}

static inline uintptr_t VOS_SetIterKey(const VosSet *set, VosSetIterator it)
{
    if (it == VOS_SetIterEnd(set)) {
        return 0;
    }

    return it->key;
}

static inline void VOS_SetClear(VosSet *set)
{
    VosSetIterator it;
    if (set == NULL) {
        return;
    }

    it = VOS_SetIterBegin(set);
    while (it != VOS_SetIterEnd(set)) {
        it = VosSetNodeErase(set, it);
    }
}

static inline void VOS_SetDestroy(VosSet *set)
{
    if (set == NULL) {
        return;
    }
    VOS_SetClear(set);

    free(set);
    return;
}

#ifdef __cplusplus
}
#endif
