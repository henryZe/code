/*
 * @file vos_queue.h
 * uintptr_t 
 *                          循环队列
 *       -------------<--------<-------<-------------|
 *       |    _____________________________________  |
 *       |   |   |   |   |   |   |   |   |   |   |   |
 *       |-->|   |   |   |   |   |   |   |   |   |-->|
 *           |___|___|___|___|___|___|___|___|___|
 *          head |                    |          tail
 *               |                    |
 *               | uintptr_t          |uintptr_t
 *               |--------->_______   |---------->_______  
 *                           |     |               |     |  
 *                           |data1|               |data2|
 *                           |_____|               |_____|
 *
 */

/**
 * @defgroup vos_queue
 * @ingroup util
 */
#ifndef VOS_QUEUE_H
#define VOS_QUEUE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "vos_common.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @ingroup vos_queue
 * vos_queue控制块
 */
typedef struct TagVosQueue VosQueue;

/**
 * @ingroup vos_queue
 * @brief 创建queue。
 * @par 描述：创建一个queue并返回其控制块。
 * @attention 注意：queue不支持动态伸缩
 * @param  itemCap    [IN]  queue成员容量
 * @param  dataFunc   [IN]  data拷贝及释放函数对。
 * @retval 指向queue控制块的指针，NULL表示创建失败。
 * @par 依赖：无
 * @li vos_queue.h：该接口声明所在的文件。
*/
static inline VosQueue *VOS_QueueCreate(size_t itemCap, VosDupFreeFuncPair *dataFunc);

/**
 * @ingroup vos_queue
 * @brief 检查queue是否为空
 * @param que   [IN] queue控制块
 * @retval #true  1，queue为空。
 * @retval #false 0，queue不为空。
 * <ul><li>vos_queue.h：该接口声明所在的头文件。</li></ul>
 */
static inline bool VOS_QueueEmpty(const VosQueue *que);

/**
 * @ingroup vos_queue
 * @brief 获取queue中成员个数
 * @param que  [IN] queue控制块
 * @retval queue成员个数
 * <ul><li>vos_queue.h：该接口声明所在的头文件。</li></ul>
 */
static inline size_t VOS_QueueSize(const VosQueue *que);

/**
 * @ingroup vos_queue
 * @brief 把数据插入到queue尾。
 * @par 描述：把数据插入到queue尾。如果que满，则插入失败。
 * @param que      [IN] queue控制块。
 * @param data     [IN] 用户数据。
 * @retval #VOS_OK      插入数据成功。
 * @retval #VOS_ERROR   插入数据失败。
 * @par 依赖：无
 * @li vos_queue.h：该接口声明所在的文件。
*/
static inline uint32_t VOS_QueuePush(VosQueue *que, uintptr_t data);

/**
 * @ingroup vos_queue
 * @brief 从queue头移除数据。
 * @par 描述：删除queue头数据，并移动que头到下一个用户数据位置。如果在初始化时注册了free函数，还会调该钩子函数释放用户资源。
 * @param que      [IN]    queue控制块。
 * @retval #VOS_OK      弹出数据成功。
 * @retval #VOS_ERROR   弹出数据失败。
 * @par 依赖：无
 * @li vos_queue.h：该接口声明所在的文件。
 */
static inline uint32_t VOS_QueuePop(VosQueue *que);

/**
 * @ingroup vos_queue
 * @brief 访问queue头节点，返回头节点的用户数据。用户使用前需要对队列判空，无法识别0是用户数据还是queue为空。
 * @param que [IN] queue控制块
 * @retval 头节点的用户数据。如果queue为空，则返回0。
 * <ul><li>vos_queue.h：该接口声明所在的头文件。</li></ul>
 */
static inline uintptr_t VOS_QueueFront(VosQueue *que);

/**
 * @ingroup vos_queue
 * @brief 访问queue尾节点，返回尾节点的用户数据。用户使用前需要对队列判空，无法识别0是用户数据还是queue为空。
 * @param que  [IN] queue控制块
 * @retval 尾节点的用户数据。如果queue为空，则返回0。
 * <ul><li>vos_queue.h：该接口声明所在的头文件。</li></ul>
 */
static inline uintptr_t VOS_QueueBack(VosQueue *que);

/**
 * @ingroup vos_queue
 * @brief 删除que。
 * @par 描述：删除que并释放所有资源。如果在初始化时注册了free函数，还会调该钩子函数释放用户资源。
 * @retval 无。
 * @li vos_queue.h：该接口声明所在的文件。
 */
static inline void VOS_QueueDestroy(VosQueue *que);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#include "vos_queue_impl.h"

#endif /* VOS_QUEUE_H */

