/**
 * @defgroup vos_map
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
 * @ingroup vos_map
 * vos_map节点
 */
typedef struct tagVosMapNode {
    rbtree_node rbtNode;
    uintptr_t  key;
    uintptr_t  value;
}VosMapNode;

/**
 * @ingroup vos_map
 * vos_map控制块
 */
struct tagVosMap {
    struct rb_root      tree;
    VosKeyCmpFunc       keyCmpFunc;
    VosDupFreeFuncPair  keyFunc;
    VosDupFreeFuncPair  dataFunc;

    size_t nodeCnt; /**< 树上的结点数目 */
};

static inline void VosMapHookRegister(VosMap *map,
                                      VosKeyCmpFunc keyCmpFunc,
                                      VosDupFreeFuncPair *keyFunc,
                                      VosDupFreeFuncPair *dataFunc)
{
    if (keyCmpFunc == NULL) {
        map->keyCmpFunc = VOS_IntCmpFunc;
    } else {
        map->keyCmpFunc = keyCmpFunc;
    }

    if (keyFunc == NULL) {
        map->keyFunc.dupFunc = NULL;
        map->keyFunc.freeFunc = NULL;
    } else {
        map->keyFunc.dupFunc = keyFunc->dupFunc;
        map->keyFunc.freeFunc = keyFunc->freeFunc;
    }

    if (dataFunc == NULL) {
        map->dataFunc.dupFunc = NULL;
        map->dataFunc.freeFunc = NULL;
    } else {
        map->dataFunc.dupFunc = dataFunc->dupFunc;
        map->dataFunc.freeFunc = dataFunc->freeFunc;
    }
}

/* 删除当前节点并返回下一个节点 */
static inline VosMapIterator VosMapNodeErase(VosMap *map, VosMapIterator it)
{
    VosMapIterator nextIt = VOS_MapIterNext(map, it);
    rb_erase(&it->rbtNode, &map->tree);
    if (map->keyFunc.freeFunc != NULL) {
        map->keyFunc.freeFunc((void *)it->key);
    }
    if (map->dataFunc.freeFunc != NULL) {
        map->dataFunc.freeFunc((void *)it->value);
    }
    free((void*)it);
    map->nodeCnt--;
    return nextIt;
}

static inline VosMap *VOS_MapCreate(VosKeyCmpFunc keyCmpFunc, VosDupFreeFuncPair *keyFunc, VosDupFreeFuncPair *valueFunc)
{
    VosMap *map = (VosMap *)calloc(1, sizeof(VosMap));
    if (map == NULL) {
        VOS_PRINTF("[vos_map] malloc failed. File = %s, line = %d.\n", __FILE__, __LINE__);
        return NULL;
    }
    VosMapHookRegister(map, keyCmpFunc, keyFunc, valueFunc);
    return map;
}

static inline VosMapNode *VosMapNodeCreate(VosMap *map, uintptr_t key, uintptr_t value)
{
    VosMapNode *mapNode = (VosMapNode *)malloc(sizeof(VosMapNode));
    if (mapNode == NULL) {
        VOS_PRINTF("[vos_map] malloc failed. File = %s, line = %d.\n", __FILE__, __LINE__);
        return NULL;
    }
    uintptr_t userKey;
    if (map->keyFunc.dupFunc != NULL) {
        userKey = (uintptr_t)map->keyFunc.dupFunc((void *)key);
        if (userKey == (uintptr_t)NULL) {
            /* 考虑用户返回失败的场景 */
            free(mapNode);
            return NULL;
        }
    } else {
        userKey = key;
    }

    uintptr_t userValue;
    if (map->dataFunc.dupFunc != NULL) {
        userValue = (uintptr_t)map->dataFunc.dupFunc((void *)value);
        if (userValue == (uintptr_t)NULL) {
            /* 考虑用户返回失败的场景 */
            if (map->keyFunc.freeFunc != NULL) {
                map->keyFunc.freeFunc((void *)userKey);
            }

            free(mapNode);
            return NULL;
        }
    } else {
        userValue = value;
    }

    mapNode->value = userValue;
    mapNode->key = userKey;
    return mapNode;
}

static inline uint32_t VosMapInsertLocate(VosMap *map, uintptr_t key, rbtree_node **parent, rbtree_node ***bestNode)
{
    rbtree_node *nilt = NULL;
    rbtree_node *tmpParent = nilt;
    rbtree_node **tmpBestNode = &map->tree.rb_node;
    VosKeyCmpFunc cmpFunc = map->keyCmpFunc;
    while (*tmpBestNode != nilt) {
        tmpParent = *tmpBestNode;

        VosMapNode *tmpNode = VOS_CONTAINER_OF(*tmpBestNode, VosMapNode, rbtNode);
        /* keycmpFunc的原型修改:入参类型修改为uintptr_t，把用户保存的数据返还用户，
           用户可以更直观的感知其自身的数据 */
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

static inline uint32_t VOS_MapInsNonexistentNode(VosMap *map, uintptr_t key, uintptr_t value)
{
    rbtree_node *parent, **bestNode;

    /* 查找key对应的插入位置，返回VOS_ERROR表示key已经存在 */
    uint32_t ret = VosMapInsertLocate(map, key, &parent, &bestNode);
    if (ret != VOS_OK) {
        VOS_PRINTF("[vos_map] this key is exist. File = %s, line = %d.\n", __FILE__, __LINE__);
        return ret;
    }

    VosMapNode *mapNode = VosMapNodeCreate(map, key, value);
    if (mapNode == NULL) {
        VOS_PRINTF("[vos_map] create map node failed. File = %s, line = %d.\n", __FILE__, __LINE__);
        return VOS_ERROR;
    }
    rb_link_node(&mapNode->rbtNode, parent, bestNode);
    rb_insert_color(&mapNode->rbtNode, &map->tree);
    map->nodeCnt++;

    return VOS_OK;
}

static inline VosMapIterator VOS_MapIterEnd(const VosMap *map)
{
    return NULL;
}

static inline uint32_t VOS_MapInsert(VosMap *map, uintptr_t key, uintptr_t value)
{
    if (map == NULL) {
        VOS_PRINTF("[vos_map] map is NULL pointer. File = %s, line = %d.\n", __FILE__, __LINE__);
        return VOS_ERROR;
    }

    if (VOS_MapFind(map, key) != VOS_MapIterEnd(map)) {
        return VOS_ERROR;
    }
    return VOS_MapInsNonexistentNode(map, key, value);
}

static inline uint32_t VOS_MapPut(VosMap *map, uintptr_t key, uintptr_t value)
{
    if (map == NULL) {
        return VOS_ERROR;
    }
    VosMapIterator it = VOS_MapFind(map, key);
    if (it == VOS_MapIterEnd(map)) { // If the node does not exist, add it
        return VOS_MapInsNonexistentNode(map, key, value);
    }
    if (it->value == value) {
        return VOS_OK;
    }

    if (map->dataFunc.freeFunc != NULL) {
        map->dataFunc.freeFunc((void *)it->value);
    }
    if (map->dataFunc.dupFunc != NULL) {
        it->value = (uintptr_t)map->dataFunc.dupFunc((void *)value);
        if (it->value == (uintptr_t)NULL) {
            /* 考虑用户返回失败的场景 */
            return VOS_ERROR;
        }
    } else {
        it->value = value;
    }
    return VOS_OK;
}

static inline VosMapIterator VOS_MapErase(VosMap *map, uintptr_t key)
{
    VosMapIterator it = VOS_MapFind(map, key);
    if (it == VOS_MapIterEnd(map)) {
        return it;
    }
    return VosMapNodeErase(map, it);
}

static inline uint32_t VOS_MapAt(const VosMap *map, uintptr_t key, uintptr_t *value)
{
    if ((map == NULL) || (value == NULL)) {
        VOS_PRINTF("[vos_map] map or value is NULL. File = %s, line = %d.\n", __FILE__, __LINE__);
        return VOS_ERROR;
    }

    VosMapIterator it = VOS_MapFind(map, key);
    if (it == VOS_MapIterEnd(map)) {
        VOS_PRINTF("[vos_map] not found. File = %s, line = %d.\n", __FILE__, __LINE__);
        return VOS_ERROR;
    }
    *value = it->value;
    return VOS_OK;
}

static inline VosMapIterator VOS_MapFind(const VosMap *map, uintptr_t key)
{
    if (map == NULL) {
        VOS_PRINTF("[vos_map] map is NULL. File = %s, line = %d.\n", __FILE__, __LINE__);
        return NULL;
    }

    VosKeyCmpFunc cmpFunc = map->keyCmpFunc;
    rbtree_node *rbtNode = map->tree.rb_node;
    rbtree_node *nilt = NULL;

    while (rbtNode != nilt) {
        VosMapNode *tmpNode = VOS_CONTAINER_OF(rbtNode, VosMapNode, rbtNode);

        int32_t ret = cmpFunc(key, tmpNode->key);
        if (ret > 0) {
            rbtNode = rbtNode->rb_right;
        } else if (ret < 0) {
            rbtNode = rbtNode->rb_left;
        } else {
            return tmpNode;
        }
    }
    /* 沒查到，返回VOS_MapIterEnd() */
    return (VosMapIterator)rbtNode;
}

static inline size_t VOS_MapSize(const VosMap *map)
{
    if (map == NULL) {
        return 0;
    }
    return map->nodeCnt;
}

static inline bool VOS_MapEmpty(const VosMap *map)
{
    if (map == NULL) {
        VOS_PRINTF("[vos_map] map is NULL. File = %s, line = %d.\n", __FILE__, __LINE__);
        return true;
    }
    return (map->nodeCnt == 0);
}

static inline VosMapNode* GetMapNodeByRbNode(rbtree_node *rbtNode)
{
    if (rbtNode == NULL) {
        return NULL;
    }
    VosMapNode *mapNode = VOS_CONTAINER_OF(rbtNode, VosMapNode, rbtNode);
    return mapNode;
}

static inline VosMapIterator VOS_MapIterBegin(const VosMap *map)
{
    if (map == NULL) {
        return NULL;
    }
    rbtree_node *rbtNode  = rb_first(&map->tree);
    VosMapNode *mapNode = GetMapNodeByRbNode(rbtNode);
    return mapNode;
}

static inline VosMapIterator VOS_MapIterNext(const VosMap *map, VosMapIterator it)
{
    if ((map == NULL) || (it == NULL) || (it == VOS_MapIterEnd(map))) {
        return VOS_MapIterEnd(map);
    }

    rbtree_node *rbtNode = rb_next(&it->rbtNode);
    VosMapNode *mapNode = GetMapNodeByRbNode(rbtNode);
    return mapNode;
}

static inline uintptr_t VOS_MapIterKey(const VosMap *map, VosMapIterator it)
{
    if (it == VOS_MapIterEnd(map)) {
        return 0;
    }
    return it->key;
}

static inline uintptr_t VOS_MapIterValue(const VosMap *map, VosMapIterator it)
{
    if (it == VOS_MapIterEnd(map)) {
        return 0;
    }
    return it->value;
}

static inline void VOS_MapClear(VosMap *map)
{
    if (map == NULL) {
        return;
    }
    VosMapIterator it = VOS_MapIterBegin(map);
    while (it != VOS_MapIterEnd(map)) {
        it = VosMapNodeErase(map, it);
    }
    map->nodeCnt = 0;
}

static inline void VOS_MapDestroy(VosMap *map)
{
    if (map == NULL) {
        return;
    }
    VOS_MapClear(map);
    free(map);
}

#ifdef __cplusplus
}
#endif
