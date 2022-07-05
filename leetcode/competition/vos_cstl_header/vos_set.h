/**
 * @defgroup vos_set Set表
 * @ingroup cstl
 */
#ifndef VOS_SET_H
#define VOS_SET_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "vos_common.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @ingroup vos_set
 * vos_set控制块
 */
typedef struct tagVosSet VosSet;

/**
 * @ingroup vos_set
 * set迭代器定义，指向用户数据（key）的起始地址
 */
typedef struct tagVosSetNode *VosSetIterator;

/**
 * @ingroup vos_set
 * @brief 创建set。
 * @par 描述：创建一个set，并返回其控制块指针。
 * @attention
 * 1.set存储的key为uintptr_t类型，该值可以为用户key，也可是指向用户key的地址。
 * 2.用户未注册keyCmpFunc函数时，将使用默认比较函数，key会被默认为uintptr_t型。
 * 3.当用户key为字符串或其他复杂类型时，应将其地址作为参数（需强转为uintptr_t类型），\n
    若该地址指向栈内存，建议注册keyFunc->dupFunc进行key的拷贝，返回对应的堆内存地址。
 * 4.若用户key为字符串或其他复杂类型，释放set表或擦除节点时，用户需自行释放资源或注册keyFunc->freeFunc。
 * @param  keyCmpFunc   [IN]  key的比较函数。
 * @param  keyFunc      [IN]  key拷贝函数及释放函数对。
 * @retval 指向set控制块的指针，NULL表示创建失败。
 * @par 依赖：无。
 * @li vos_set.h：该接口声明所在的文件。
 */
static inline VosSet *VOS_SetCreate(VosKeyCmpFunc keyCmpFunc, VosDupFreeFuncPair *keyFunc);

/**
 * @ingroup vos_set
 * @brief 插入set数据
 * @par 描述：插入用户数据
 * @attention
 * 1.不支持重复的key。
 * 2.key为int类型时，直接将值作为参数即可。
 * 3.当用户key为字符串或其他复杂类型时，应将其地址作为参数（需强转为uintptr_t类型），
     如char *key, 则入参应为(uintptr_t)key。
 * @param set       [IN] set句柄
 * @param key       [IN] key或指向key的地址
 * @retval VOS_OK 插入成员成功
 * @retval VOS_ERROR 插入成员失败
 * @par 依赖：无
 * <ul><li>vos_set.h：该接口声明所在的头文件。</li></ul>
 */
static inline uint32_t VOS_SetInsert(VosSet *set, uintptr_t key);

/**
 * @ingroup vos_set
 * @brief 检查Set是否为空
 * @param set    [IN] set控制块
 * @retval #true  1，Set为空。
 * @retval #false 0，Set不为空。
 * <ul><li>vos_set.h：该接口声明所在的头文件。</li></ul>
 */
static inline bool VOS_SetEmpty(const VosSet *set);

/**
 * @ingroup vos_set
 * @brief 获取set中成员个数
 * @param set  [IN] set控制块
 * @retval set成员个数
 * <ul><li>vos_set.h：该接口声明所在的头文件。</li></ul>
 */
static inline size_t VOS_SetSize(const VosSet *set);

/**
 * @ingroup vos_set
 * @brief 查找成员
 * @par 描述: 根据key查找并返回成员数据指针
 * @param set       [IN] set句柄
 * @param key       [IN] key或指向key的地址
 * @retval #key对应的迭代器，失败时返回VOS_SetIterEnd()
 * @par 依赖：无
 * <ul><li>vos_set.h：该接口声明所在的头文件。</li></ul>
 */
static inline VosSetIterator VOS_SetFind(const VosSet *set, uintptr_t key);

/**
 * @ingroup vos_set
 * @brief 从set中移除指定成员，并指向下一个节点迭代器。
 * @par 描述: 根据key查找到成员并删除（释放内存）
 * @param set      [IN] set句柄
 * @param key      [IN] 待移除的成员key。
 * @retval  下一个节点迭代器。如果被删除key为最后一个节点，则返回VOS_SetIterEnd()
 * @par 依赖：无
 * <ul><li>vos_set.h：该接口声明所在的头文件。</li></ul>
 */
static inline VosSetIterator VOS_SetErase(VosSet *set, uintptr_t key);

/**
 * @ingroup vos_set
 * @brief 获取set第一个成员迭代器。
 * @par 描述：获取set第一个成员迭代器。
 * @param set [IN] set句柄。
 * @retval #第一个迭代器。当set中无节点时，返回VOS_SetIterEnd()。
 * @par 依赖：无
 * <ul><li>vos_set.h：该接口声明所在的头文件。</li></ul>
 */
static inline VosSetIterator VOS_SetIterBegin(const VosSet *set);

/**
 * @ingroup vos_set
 * @brief 获取set下一个成员迭代器。
 * @par 描述：获取set下一个成员迭代器。
 * @attention
 * @param set  [IN]  set句柄。
 * @param it   [IN]  当前迭代器。
 * @retval #下一个成员迭代器。
 * @retval #VOS_SetIterEnd()，表示当前已是最后一个节点。
 * @par 依赖：无
 * <ul><li>vos_set.h：该接口声明所在的头文件。</li></ul>
 */
static inline VosSetIterator VOS_SetIterNext(const VosSet *set, VosSetIterator it);

/**
 * @ingroup vos_set
 * @brief 获取set最后一个节点之后预留的迭代器。
 * @par 描述：获取set最后一个节点之后预留的迭代器。
 * @param set  [IN]  set句柄。
 * @retval #最后一个节点之后预留的迭代器。
 * @par 依赖：无
 * <ul><li>vos_set.h：该接口声明所在的头文件。</li></ul>
 */
static inline VosSetIterator VOS_SetIterEnd(const VosSet *set);

/**
 * @ingroup vos_set
 * @brief 获取当前迭代器的key。
 * @par 描述：获取当前迭代器的key。
 * @param it  [IN]  当前迭代器。
 * @retval 迭代器对应的key。ki
 * @retval #0 it等于VOS_SetIterEnd()
 * @par 依赖：无
 * <ul><li>vos_set.h：该接口声明所在的头文件。</li></ul>
 */
static inline uintptr_t VOS_SetIterKey(const VosSet *set, VosSetIterator it);

/**
 * @ingroup vos_set
 * @brief 删除set所有成员
 * @attention
 *  1.该接口会删除set表中所有节点。
 *  2.若用户注册了key的资源释放函数，则会调用钩子进行用户资源释放。
 * @par 描述：删除所有成员（set还在，只是没有成员）
 * @param  set [IN] set句柄。
 * @retval 无。
 * @par 依赖：无
 * <ul><li>vos_set.h：该接口声明所在的头文件。</li></ul>
 */
static inline void VOS_SetClear(VosSet *set);

/**
 * @ingroup vos_set
 * @brief 删除set
 * @attention 
 *  1.该接口会删除set表中所有节点。
 *  2.若用户注册了key的资源释放函数，则会调用钩子进行用户资源释放。
 *  3.调用本接口后，set指针指向的内存被free，set表不可以再次访问。
 * @par 描述：删除set，如里面有成员先删除成员，再回收控制块内存。
 * @param  set [IN] set句柄。
 * @retval 无。
 * @par 依赖：无
 * <ul><li>vos_set.h：该接口声明所在的头文件。</li></ul>
 */
static inline void VOS_SetDestroy(VosSet *set);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#include "vos_set_impl.h"

#endif /* VOS_SET_H */

