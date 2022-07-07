/**
 * @defgroup vos_priorityqueue 优先队列
 * @ingroup cstl
 */

#ifndef VOS_PRIORITY_QUEUE_H
#define VOS_PRIORITY_QUEUE_H

#include <stdbool.h>
#include "vos_common.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @ingroup vos_priorityqueue
 * @brief 比较函数原型
 * @par 描述：比较函数原型，用于排序场景。
 * @attention \n
 *  1.这里只定义了比较函数原型，由于不知道数据类型和长度，因此钩子函数需要业务自己实现。\n
 *  2.对于data1和data2，比较函数不区分是整型数还是指针，用户应自己区分。\n
 *  3.用户返回(data1 - data2)的时候为大顶堆，反之为小顶堆。
 * @param data1    [IN] 数据1
 * @param data2    [IN] 数据2
 * @retval 大于0, 等于0, 小于0; <0就表示 data1 < data2
 * @par 依赖：无
 * @li vos_priorityqueue.h：该接口声明所在的文件。
 */
typedef int32_t (*VosPriQueCmpFunc)(uintptr_t data1, uintptr_t data2);

/**
 * @ingroup vos_priorityqueue
 * vos_priorityqueue 控制块
 */
typedef struct tagVosPriQue VosPriQue;

/**
 * @ingroup vos_priorityqueue
 * @brief 创建priority queue。
 * @par 描述：创建一个priority queue，并返回其控制块指针。
 * @attention \n
 *  1.提供默认的整型及字符串型比较函数#VOS_IntCmpFunc、#VOS_StrCmpFunc，用户需要在创建队列时作为参数传入。\n
 *  2.默认比较函数均为大顶堆，用户需要小顶堆需要自定义比较函数。\n
 *  3.如果扩展数据的生命周期小于节点的生命周期，则需要在创建队列时注册dataFunc->dupFunc。\n
 *  4.用户使用# VOS_PriQuePushBatch添加数据时，优先队列无法感知用户数据类型，必须注册注册dataFunc->dupFunc。
 * @param  cmpFunc      [IN] 比较函数。
 * @param  dataFun      [IN] 用户数据拷贝及释放函数对。
 * @retval #指向priority queue控制块的指针 创建成功。
 * @retval #NULL 创建失败。
 * @par 依赖：无。
 * @li vos_priorityqueue.h：该接口声明所在的文件。
 */
static inline VosPriQue *VOS_PriQueCreate(VosPriQueCmpFunc cmpFunc, VosDupFreeFuncPair *dataFunc);

/**
 * @ingroup vos_priorityqueue
 * @brief 插入一个数据到priority queue。
 * @par 描述：用户数据插入后，调用钩子cmpFunc完成优先队列转换。
 * @attention \n
 *  1.用户数据。用户应清晰的知道value是整型数还是地址。\n
 *  2.当用户存储的数据长度不大于sizeof(uintptr_t)时，直接存储数据即可，无需申请内存。\n
 *  3.当用户存储的数据长度大于sizeof(uintptr_t)时，用户需要传入数据的地址。\n
 *  4.如果扩展数据的生命周期小于节点的生命周期，则需要在创建队列时注册dataFunc->dupFunc。\n
 * @param priQueue       [IN] priority queue控制块。
 * @param value          [IN] 用户保存的数据
 * @retval #VOS_OK       成功。
 * @retval #VOS_ERROR    失败。
 * @par 依赖：无
 * @li vos_priorityqueue.h：该接口声明所在的文件。
 */
static inline uint32_t VOS_PriQuePush(VosPriQue *priQueue, uintptr_t value);

/**
 * @ingroup vos_priorityqueue
 * @brief 插入一组数据到priority queue。
 * @par 描述：插入一组数据到priority queue，并转换成优先队列。
 * @attention \n
 *  1.从起始地址startAddr，按照单个数据长度为itemSize进行读取，共读取itemNum个。\n
 *  2.用户必须在创建队列时注册拷贝函数(dataFunc.dupFunc)进行内容拷贝，并返回指向保存用户数据的地址。\n
 *  3.若用户保存的数据类型为整型，可以在拷贝函数(dataFunc.dupFunc)中返回该整型值。\n
 *  4.用户数据插入后，会调用钩子cmpFunc完成排序。\n
 * @param priQueue       [IN] priority queue控制块。
 * @param beginItemAddr  [IN] 指向用户数据的起始地址。
 * @param itemNum        [IN] 待插入的数据个数。
 * @param itemSize       [IN] 单个数据的大小。
 * @retval #VOS_OK       成功。
 * @retval #VOS_ERROR    失败。
 * @par 依赖：无
 * @li vos_priorityqueue.h：该接口声明所在的文件。
 */
static inline uint32_t VOS_PriQuePushBatch(VosPriQue *priQueue, void *beginItemAddr, size_t itemNum, size_t itemSize);

/**
 * @ingroup vos_priorityqueue
 * @brief 弹出头部数据。
 * @par 描述：弹出头部数据，并释放资源。
 * @attention \n
 *  1.如果用户在创建队列时注册了dataFunc->freeFunc，则会调用该钩子释放用户资源。\n
 *  2.建议用户dataFunc->dupFunc与dataFunc->freeFunc函数成对注册。\n
 * @param priQueue    [IN]    priority queue控制块。
 * @retval 无。
 * @par 依赖：无。
 * @li vos_priorityqueue.h：该接口声明所在的文件。
 */
static inline void VOS_PriQuePop(VosPriQue *priQueue);

/**
 * @ingroup vos_priorityqueue
 * @brief 读取头数据。
 * @par 返回堆顶的数据。
 * @attention \n
 *  1.返回的数据是最大值还是最小值，由用户创建优先队列时注册的比较函数决定。\n
 *  2.当队列为空时，接口返回0，该接口无法识别返回的值是错误码还是用户数据，
      用户使用前必须进行#VOS_PriQueEmpty判断是否为空。\n
 * @param priQueue    [IN]    priority queue控制块。
 * @retval 用户数据。
 * @par 依赖：无
 * @li vos_priorityqueue.h：该接口声明所在的文件。
 */
static inline uintptr_t VOS_PriQueTop(const VosPriQue *priQueue);

/**
 * @ingroup vos_priorityqueue
 * @brief 判断priority queue是否为空
 * @param priQueue  [IN] priority queue控制块。
 * @retval #true，  表示priority queue为空
 * @retval #false， 表示priority queue为非空
 * @par 依赖：无
 * @li vos_priorityqueue.h：该接口声明所在的头文件。
 */
static inline bool VOS_PriQueEmpty(const VosPriQue *priQueue);

/**
 * @ingroup vos_priorityqueue
 * @brief 获取priority queue中成员个数
 * @param priQueue  [IN] priority queue控制块。
 * @retval priority queue成员个数
 * @par 依赖：无
 * @li vos_priorityqueue.h：该接口声明所在的头文件。
 */
static inline size_t VOS_PriQueSize(const VosPriQue *priQueue);

/**
 * @ingroup vos_priorityqueue
 * @brief 删除priority queue所有成员，保留控制块
 * @par 描述：该接口调用后，控制块可以继续使用。
 * @attention \n
 *  1.调用该接口后priQueue指向的内存被释放。\n
 *  2.如果用户注册了释放函数，会调用该函数进行用户资源释放。\n
 * @param  priQueue [IN] priority queue控制块。
 * @retval 无。
 * @par 依赖：无
 * <ul><li>vos_priorityqueue.h：该接口声明所在的头文件。</li></ul>
 */
static inline void VOS_PriQueClear(VosPriQue *priQueue);

/**
 * @ingroup vos_priorityqueue
 * @brief 删除priority queue所有成员及控制块
 * @par 描述：销毁priority queue。
 * @attention \n
 *  1.调用该接口后priQueue指向的内存被释放。\n
 *  2.如果用户注册了释放函数，会调用该函数进行用户资源释放。\n
 *  3.该接口调用后句柄被释放，不允许再次使用。
 * @param  priQueue [IN] priority queue控制块。
 * @retval 无。
 * @par 依赖：无
 * <ul><li>vos_priorityqueue.h：该接口声明所在的头文件。</li></ul>
 */
static inline void VOS_PriQueDestroy(VosPriQue *priQueue);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#include "vos_priorityqueue_impl.h"
#endif /* VOS_PRIORITY_QUEUE_H */
