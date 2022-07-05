/*
 * @file vos_common.h
 * Description: 通用定义头文件。
 */

#ifndef VOS_COMMON_H
#define VOS_COMMON_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "securec.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cpluscplus */

/* ******************************************************************************** */
/* 公共错误码定义                                                                   */
/* ******************************************************************************** */
/**
* @ingroup vos_common
* 0x0 正确。
*/
#define VOS_OK     0u

/**
* @ingroup vos_common
* 0x1 错误。
*/
#define VOS_ERROR  1u

#ifdef VOS_DEBUG
    #define VOS_STATIC
    #ifndef VOS_PRINTF
        #define VOS_PRINTF printf
    #endif
#else
    #define VOS_STATIC static
    #ifndef VOS_PRINTF
        #define VOS_PRINTF(format, ...)
    #endif
#endif

/* ******************************************************************************** */
/* 公共钩子函数原型定义                                                             */
/* ******************************************************************************** */
/**
 * @ingroup vos_common
 * @brief 比较函数原型
 * @par 描述：比较函数原型，用于排序场景。
 * @attention 注意：这里只定义了比较函数原型，由于不知道数据类型和长度，因此钩子函数需要业务自己实现。
 * @param data1    [IN] 数据1
 * @param data2    [IN] 数据2
 * @retval >0 升序排序
 * @retval =0 不做交换
 * @retval <0 降序排序
 */
typedef int32_t (*VosDataCmpFunc)(const void *data1, const void *data2);

/**
 * @ingroup vos_common
 * @brief 比较函数原型
 * @par 描述：比较函数原型，用于排序场景。
 * @attention 注意：这里只定义了比较函数原型，由于不知道数据类型和长度，因此钩子函数需要业务自己实现。
 * @param key1    [IN] key1
 * @param key2    [IN] key2
 * @retval >0 升序排序
 * @retval =0 不做交换
 * @retval <0 降序排序
 */
typedef int32_t (*VosKeyCmpFunc)(uintptr_t key1, uintptr_t key2);

/**
 * @ingroup vos_common
 * 默认整型比较函数
 * @retval #(data1 - data2)
 */
static inline int32_t VOS_IntCmpFunc(uintptr_t data1, uintptr_t data2);

/**
 * @ingroup vos_common
 * 默认字符串比较函数
 * @retval #(strcmp((char *)addr1, (char *)addr2))
 */
static inline int32_t VOS_StrCmpFunc(uintptr_t addr1, uintptr_t addr2);

/**
 * @ingroup vos_common
 * @brief 用户数据拷贝函数原型
 * @attention 注意：源缓冲区长度需要调用者获取，由于不知道数据类型和长度，因此钩子函数需要业务自己实现。
 * @param src     [IN]  源缓冲区
 * @retval 目标缓冲区，NULL表示失败。
 */
typedef void *(*VosDupFunc)(void *ptr);

/**
 * @ingroup vos_common
 * @brief 用户内存释放函数原型
 * @par 描述：资源释放函数原型，一般用于机制批量free内存时，内存中可能含有用户私有资源，这是需要用户自行释放
 * @param ptr    [IN] 指向用户数据的指针
 * @retval 无
 */
typedef void (*VosFreeFunc)(void *ptr);

/**
 * @ingroup vos_common
 * @brief key和value函数原型对
 * @par 描述：key和value的拷贝及释放函数成对出现。
 */
typedef struct {
    VosDupFunc dupFunc;
    VosFreeFunc freeFunc;
} VosDupFreeFuncPair;

/**
 * @ingroup vos_common
 * @brief 该API通过结构的某个成员变量，得到这个结构的起始地址。
 *
 * @par 描述:
 * 该API通过结构的某个成员变量，得到这个结构的起始地址。该API是一个特殊的宏，输入参数取决于宏的实现。
 * @attention
 * @param ptr [IN]  该参数表示结点某成员的地址。取值范围为数据类型。
 * @param type [IN]  该参数表示传入的成员所属的结点类型结构。取值范围为数据类型。
 * @param member [IN]  该参数表示结构中成员变量的名字。取值范围为数据类型。
 *
 * @retval 与入参类型相同结构的地址。
 * @see 无。
*/
#define VOS_CONTAINER_OF(ptr, type, member) \
    ((type *)((char *)(ptr) - (uintptr_t)(&((type *)0)->member)))

static inline const char* VOS_CstlVersion(void)
{
    return "2.3(2021-09-13)";
}

#ifdef __cplusplus
}
#endif /* __cpluscplus */

#include "vos_common_impl.h"

#endif /* VOS_COMMON_H */

