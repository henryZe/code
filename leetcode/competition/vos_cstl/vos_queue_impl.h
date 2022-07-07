#include "vos_common.h"
#include "vos_common_impl.h"
#include "securec.h"

#ifdef __cplusplus
extern "C" {
#endif

struct TagVosQueue {
    size_t      front;           /* 循环队列队首数组下标 */
    size_t      rear;            /* 循环队列队尾数组下标 */
    size_t      capacity;        /* 最大单元个数 */
    size_t      nodeCnt;         /* 记录当前队列元素个数，减少计算队列大小及满队列计算的开销 */
    VosDupFreeFuncPair dataFunc; /* 用户单元数据自定义拷贝函数 */
    uintptr_t *userdata;
};

static inline size_t VOS_QueueGetNextPos(VosQueue *que, size_t index)
{
    return ((index + 1) % que->capacity);
}

static inline VosQueue *VOS_QueueCreate(size_t capacity, VosDupFreeFuncPair *dataFunc)
{
    if ((capacity == 0) || IsAddOverflow(capacity, 1)) {
        return NULL;
    }

    if (IsMultiOverflow(sizeof(uintptr_t), capacity)) {
        return NULL;
    }
    
    VosQueue *que = (VosQueue*)calloc(1, sizeof(VosQueue));
    if (que == NULL) {
        return NULL;
    }
    que->userdata = (uintptr_t*)calloc(capacity, sizeof(uintptr_t));
    if (que->userdata == NULL) {
        free(que);
        return NULL;
    }

    que->capacity = capacity;

    if (dataFunc == NULL) {
        que->dataFunc.dupFunc = NULL;
        que->dataFunc.freeFunc = NULL;
    } else {
        que->dataFunc.dupFunc = dataFunc->dupFunc;
        que->dataFunc.freeFunc = dataFunc->freeFunc;
    }

    return que;
}

static inline bool VosQueEmpty(const VosQueue *que)
{
    return (que->nodeCnt == 0);
}

static inline bool VosQueFull(const VosQueue *que)
{
    return (que->nodeCnt == que->capacity);
}

static inline bool VOS_QueueEmpty(const VosQueue *que)
{
    if (que == NULL) {
        return true;
    }

    return VosQueEmpty((VosQueue*)que);
}

static inline size_t VOS_QueueSize(const VosQueue *que)
{
    if (que == NULL) {
        return 0;
    }

    return que->nodeCnt;
}

static inline uint32_t VOS_QueuePush(VosQueue *que, uintptr_t value)
{
    if ((que == NULL) || VosQueFull(que)) {
        return VOS_ERROR;
    }

    uintptr_t tmpValue = value;

    if (que->dataFunc.dupFunc != NULL) {
        tmpValue = (uintptr_t)que->dataFunc.dupFunc((void *)value);
    }
    que->userdata[que->rear] = tmpValue;
    que->nodeCnt++;
    que->rear = VOS_QueueGetNextPos(que, que->rear);

    return VOS_OK;
}

static inline uint32_t VOS_QueuePop(VosQueue *que)
{
    if ((que == NULL) || VosQueEmpty(que)) {
        return VOS_ERROR;
    }

    if (que->dataFunc.freeFunc != NULL) {
        uintptr_t data = que->userdata[que->front];
        VOS_PRINTF("free %p\n", data);
        que->dataFunc.freeFunc((void *)data);
    }
    que->front = VOS_QueueGetNextPos(que, que->front);
    que->nodeCnt--;
    return VOS_OK;
}

static inline uintptr_t VOS_QueueFront(VosQueue *que)
{
    if ((que == NULL) || VosQueEmpty((VosQueue*)que)) {
        return 0;
    }
    uintptr_t data = que->userdata[que->front];

    return data;
}

static inline uintptr_t VOS_QueueBack(VosQueue *que)
{
    if ((que == NULL) || VosQueEmpty(que)) {
        return 0;
    }
    size_t pos = que->rear;
    if (pos == 0) {
        pos = que->capacity - 1;
    } else {
        pos--;
    }
    uintptr_t data = que->userdata[pos];

    return data;
}

static inline void VOS_QueueClear(VosQueue *que)
{
    if (que == NULL) {
        return;
    }

    if ((que->dataFunc.freeFunc != NULL) && !VosQueEmpty(que)) {
        // 注意队列满的时候， front==rear==0, 所以这里不能通过判断 (que->front != que->rear)
        for (size_t i = 0; i < que->nodeCnt; ++i) {
            uintptr_t data = que->userdata[que->front];
            que->dataFunc.freeFunc((void *)data);
            que->front = VOS_QueueGetNextPos(que, que->front);
        }
    }
    (void)memset(que->userdata, 0, sizeof(uintptr_t) * que->capacity);
    que->nodeCnt = 0;
}

static inline void VOS_QueueDestroy(VosQueue *que)
{
    if (que == NULL) {
        return;
    }
    VOS_QueueClear(que);
    free(que->userdata);
    free(que);
}

#ifdef __cplusplus
}
#endif
