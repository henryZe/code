/**
 * @defgroup vos_stack 栈
 * @ingroup cstl
 */
#ifndef VOS_STACK_H
#define VOS_STACK_H

#include <stdint.h>
#include <stdbool.h>
#include "vos_vector.h"
#include "vos_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup vos_stack
 * vos_stack控制块
 */
typedef struct tagVosStack VosStack;

/**
 * @ingroup vos_stack
 * @brief 创建堆栈。
 * @par 描述：创建一个堆栈并返回其控制块。
 * @attention 注意：堆栈支持动态扩展
 * @param  dataFunc    [IN]  用户资源拷贝、释放函数对
 * @retval 非NULL 指向堆栈控制块的指针。
 * @retval NULL   创建失败。
 * @par 依赖：无
 * @li vos_stack.h：该接口声明所在的文件。
*/
static inline VosStack *VOS_StackCreate(VosDupFreeFuncPair *dataFunc);

/**
 * @ingroup vos_stack
 * @brief 检查Stack是否为空
 * @param stack   [IN] stack控制块
 * @retval #true  1，Stack为空。
 * @retval #false 0，Stack不为空。
 * <ul><li>vos_stack.h：该接口声明所在的头文件。</li></ul>
 */
static inline bool VOS_StackEmpty(const VosStack *stack);

/**
 * @ingroup vos_stack
 * @brief 获取stack中成员个数
 * @param stack  [IN] stack控制块
 * @retval stack成员个数
 * <ul><li>vos_stack.h：该接口声明所在的头文件。</li></ul>
 */
static inline size_t VOS_StackSize(const VosStack *stack);

/**
 * @ingroup vos_stack
 * @brief 本接口将输入的数据压入到指定堆栈，并移动栈顶指针到新的栈顶。
 * @par 描述：本接口将输入的数据压入到指定堆栈，并移动栈顶指针到新的栈顶。如果满，则push失败。
 * @param stack    [IN] stack控制块。
 * @param data     [IN] 用户数据。
 * @retval #VOS_OK    插入数据成功。
 * @retval #VOS_ERROR 插入数据失败。
 * @par 依赖：无
 * @li vos_stack.h：该接口声明所在的文件。
*/
static inline uint32_t VOS_StackPush(VosStack *stack, uintptr_t data);

/**
 * @ingroup vos_stack
 * @brief 移除栈顶元素，并移动栈顶指针到新的栈顶。
 * @par 描述：移除栈顶元素，并移动栈顶指针到新的栈顶。如果空，则pop失败。
 * @param stack          [IN] stack控制块。
 * @retval #VOS_OK       弹出数据成功。
 * @retval #VOS_ERROR    弹出数据失败。
 * @par 依赖：无
 * @li vos_stack.h：该接口声明所在的文件。
 */
static inline uint32_t VOS_StackPop(VosStack *stack);

/**
 * @ingroup vos_stack
 * @brief 获取当前栈顶元素，而不移动栈顶指针。
 * @attention 注意：如果stack为空，则返回0。用户不能区分是空返回的0，还是真实数据就是0，因此需要提前识别stack空的场景。\n
 * 本接口仅用于获取栈顶元素后，但该元素礽位于栈中，请不要对其进行释放。
 * @param stack    [IN]    stack控制块。
 * @retval stack栈顶数据。
 * @par 依赖：无
 * @li vos_stack.h：该接口声明所在的文件。
 */
static inline uintptr_t VOS_StackTop(const VosStack *stack);

/**
 * @ingroup vos_stack
 * @brief 清空堆栈。
 * @par 描述：清空并释放资源，但是保留栈控制块。
 * @param stack    [IN]    stack控制块。
 * @retval 无。
 * @par 依赖：无
 * @li vos_stack.h：该接口声明所在的文件。
 */
static inline void VOS_StackClear(VosStack *stack);

/**
 * @ingroup vos_stack
 * @brief 删除堆栈。
 * @par 描述：删除堆栈并释放所有资源。
 * @retval 无。
 * @par 依赖：无
 * @li vos_stack.h：该接口声明所在的文件。
 */
static inline void VOS_StackDestroy(VosStack *stack);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#include "vos_stack_impl.h"

#endif /* VOS_STACK_H */

