#include "securec.h"
#include "vos_list.h"

#ifdef __cplusplus
#ifdef __cplusplus
extern "C" {
#endif
#endif

struct tagVosStack {
    VosList listObj; /* 栈内部由链表构成 */
};

static inline VosStack *VOS_StackCreate(VosDupFreeFuncPair *dataFunc)
{
    VosStack *stack = (VosStack *)malloc(sizeof(VosStack));
    if (stack == NULL) {
        return NULL;
    }
    VOS_ListInit(&stack->listObj, dataFunc);

    return stack;
}

static inline bool VOS_StackEmpty(const VosStack *stack)
{
    return ((stack == NULL) || VOS_ListEmpty(&stack->listObj));
}

static inline size_t VOS_StackSize(const VosStack *stack)
{
    if (stack == NULL) {
        return 0;
    }
    return VOS_ListSize(&stack->listObj);
}

static inline uint32_t VOS_StackPush(VosStack *stack, uintptr_t data)
{
    if (stack == NULL) {
        return VOS_ERROR;
    }
    return VOS_ListPushFront(&stack->listObj, data);
}

static inline uint32_t VOS_StackPop(VosStack *stack)
{
    if (stack == NULL) {
        return VOS_ERROR;
    }
    if (VOS_StackSize(stack) == 0) {
        return VOS_ERROR;
    }    
    VOS_ListPopFront(&stack->listObj);
    return VOS_OK;
}

static inline uintptr_t VOS_StackTop(const VosStack *stack)
{
    if (stack == NULL) {
        return VOS_ERROR;
    }
    return VOS_ListFront((VosList*)&stack->listObj);
}

static inline void VOS_StackClear(VosStack *stack)
{
    if (stack == NULL) {
        return;
    }
    VosDupFreeFuncPair dataFunc = stack->listObj.dataFunc;
    VOS_ListDeinit(&stack->listObj);
    stack->listObj.dataFunc = dataFunc;
}

static inline void VOS_StackDestroy(VosStack *stack)
{
    if (stack == NULL) {
        return;
    }
    VOS_StackClear(stack);
    free(stack);
}

#ifdef __cplusplus
#ifdef __cplusplus
}
#endif
#endif
