#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "vos_common.h"
#include "pqueue.h" // from https://github.com/vy/libpqueue

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define DEFAULT_PRIORITY_QUEUE_SIZE 256

struct tagVosPriQue {
    VosPriQueCmpFunc cmpFunc;
    VosDupFreeFuncPair dataFunc;
    pqueue_t* pque;
};
typedef struct tagVosPriQue VosPriQue;

// 采用 node_t 包装一个节点的做法，在每次push节点时都会申请内存，会有性能问题。
// 所以还是直接将用户数据传入 pqueue
static inline int32_t TsaPqCmpFunc(void *priQueue, void* node1, void* node2)
{
    VosPriQue *que = (VosPriQue*)priQueue;
    return que->cmpFunc((uintptr_t)node1, (uintptr_t)node2);
}

// 不要删除此函数，否则需要修改pqueue较多地方
static inline void set_pos(void *a, size_t pos)
{
}

static inline void VosPriQueHookRegister(VosPriQue *priQue, 
                                      VosPriQueCmpFunc cmpFunc,
                                      VosDupFreeFuncPair *dataFunc)
{
    if (cmpFunc == NULL) {
        priQue->cmpFunc = VOS_IntCmpFunc;
    } else {
        priQue->cmpFunc = cmpFunc;
    }

    if (dataFunc == NULL) {
        priQue->dataFunc.dupFunc = NULL;
        priQue->dataFunc.freeFunc = NULL;
    } else {
        priQue->dataFunc.dupFunc = dataFunc->dupFunc;
        priQue->dataFunc.freeFunc = dataFunc->freeFunc;
    }
}

static inline VosPriQue *VOS_PriQueCreate(VosPriQueCmpFunc cmpFunc, VosDupFreeFuncPair *dataFunc)
{
    VosPriQue *priQueue;
    size_t size = sizeof(VosPriQue);

    priQueue = (VosPriQue *)calloc(1, size);
    if (priQueue == NULL) {
        VOS_PRINTF("[vos_priorityqueue] create priorityqueue failed. File = %s, line = %d.\n", __FILE__, __LINE__);
        return NULL;
    }

    VosPriQueHookRegister(priQueue, cmpFunc, dataFunc);
    // set_pos 没有用到，但是pqueue有调用
    priQueue->pque = pqueue_init(DEFAULT_PRIORITY_QUEUE_SIZE, TsaPqCmpFunc, NULL, NULL, NULL, set_pos, priQueue);

    return priQueue;
}

static inline uint32_t VOS_PriQuePush(VosPriQue *priQueue, uintptr_t value)
{
    uintptr_t userData;

    if (priQueue->dataFunc.dupFunc != NULL) {
        userData = (uintptr_t)priQueue->dataFunc.dupFunc((void *)value);
    } else {
        userData = value;
    }

    pqueue_insert(priQueue->pque, (void*)userData);

    return VOS_OK;
}

static inline uint32_t VOS_PriQuePushBatch(VosPriQue *priQueue, void *beginItemAddr, size_t itemNum, size_t itemSize)
{
    size_t i;
    uintptr_t currentAddr;

    if (priQueue->dataFunc.dupFunc == NULL) {
        VOS_PRINTF("[vos_priorityqueue]DupFunc is not registered. File = %s, line = %d.\n", __FILE__, __LINE__);
        return VOS_ERROR;
    }

    for (i = 0; i < itemNum; i++) {
        currentAddr = (uintptr_t)beginItemAddr + i * itemSize;
        (void)VOS_PriQuePush(priQueue, currentAddr);
    }

    return VOS_OK;
}

static inline void VOS_PriQuePop(VosPriQue *priQueue)
{
    void *node = pqueue_pop(priQueue->pque);
    if (priQueue->dataFunc.freeFunc != NULL) {
        priQueue->dataFunc.freeFunc(node);
    }
}

static inline uintptr_t VOS_PriQueTop(const VosPriQue *priQueue)
{
    void *node = pqueue_peek(priQueue->pque);
    return (uintptr_t)node;
}

static inline bool VOS_PriQueEmpty(const VosPriQue *priQueue)
{
    return (VOS_PriQueSize(priQueue) == 0);
}

static inline size_t VOS_PriQueSize(const VosPriQue *priQueue)
{
    if (priQueue == NULL) {
        VOS_PRINTF("[vos_priorityqueue] priority queue is NULL pointer. File = %s, line = %d.\n", __FILE__, __LINE__);
        return 0;
    }

    return pqueue_size(priQueue->pque);
}

static inline void VOS_PriQueClear(VosPriQue *priQueue)
{
    if (priQueue == NULL) {
        VOS_PRINTF("[vos_priorityqueue] priority queue is NULL. File = %s, line = %d.", __FILE__, __LINE__);
        return;
    }

    // 注意pqueue内部的d是从下标1开始的
    if (priQueue->dataFunc.freeFunc != NULL) {
        for (size_t i = 1; i < priQueue->pque->size; i++) {
            void *node = priQueue->pque->d[i];
            priQueue->dataFunc.freeFunc(node);
        }
    }

    pqueue_clear(priQueue->pque);
}

static inline void VOS_PriQueDestroy(VosPriQue *priQueue)
{
    if (priQueue == NULL) {
        VOS_PRINTF("[vos_priorityqueue] priority queue is NULL. File = %s, line = %d.", __FILE__, __LINE__);
        return;
    }
    VOS_PriQueClear(priQueue);

    pqueue_free(priQueue->pque);
    free(priQueue);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
