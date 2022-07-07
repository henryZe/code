/*
 * @file vos_list.h
 * Notes: 1、本头文件是在 vos_rawlist.h 基础上，借鉴C++面向对象抽象方法，从方便用户使用的角度出发，抽象提炼的接口。
 *           用户不需要看到链表节点，只关注自己的数据。
 *        2、关于 duplicate 函数
 *           a）duplicate 函数在初始化时注册；
 *           b）如果用户注册 duplicate 函数，则调用该函数进行数据拷贝，否则直接复制userData(uintptr_t)数据。
 *              用户的数据类型是int型，且长度 <= sizeof(uintptr_t)，如32位环境下uint32_t、64位环境下uint32_t、uint64_t等，
 *              可不注册；用户数据类型是指针，若不注册duplicate函数，由用户自己保障内存的分配、复制和释放。
 *        2、关于free函数
 *           a）若用户注册free函数，则调用该函数释放用户数据。
 *           b）如果用户数据是int型、且长度<=sizeof(uintptr_t)，则用户不需要注册资源释放函数；
 *           c）若用户数据为指针，不注册free函数，由用户自己保障私有数据privatedata的内存释放。
 *        4、链表处理内部无锁，如果用户需要支持多线程并发，则需要在外层加锁。
 *   +------------------------------------------------------------------------+
 *   | +-------------------------------------------------------------------+  |
 *   | |       head                                                        |  |
 *   | |   +----------+    +-------------------------+     +-----------+   |  |
 *   | +---|   prev   |<---| prev                    |<----| prev      |<--+  |
 *   +---->|   next   |--->| next                    |---->| next      |------+
 *         +----------+    +-------------------------+     +-----------+
 *         | count    |    | userData    int型且     |     | userData  |
 *         | freefunc |    | 长度<=sizeof(uintptr_t) |     | (pointer) |--------+  用户私有资源
 *         | dupfunc  |    +-------------------------+     +-----------+       \|/
 *         +----------+                                                  +-------------+
 *                                                                       | privatedata |
 *                                                                       +-------------+
 * 
 *    Example：
 *        
 */

/**
 * @defgroup vos_list 双向链表
 * @ingroup util
 */
#ifndef VOS_LIST_H
#define VOS_LIST_H

#include "vos_common.h"
#include "securec.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup vos_rawlist
 * 链表头
 */
typedef struct tagVosRawListNode {
    struct tagVosRawListNode *next;     /**< 指向下一个节点 */
    struct tagVosRawListNode *prev;     /**< 指向前一个节点 */
} VosRawListNode;

/**
 * @ingroup vos_list
 * 该结构被用来保存双向链表中节点的前向指针和后向指针，以及少量用户数据或指针。
 */
typedef struct {
    VosRawListNode rawNode;
    uintptr_t      userdata;
} VosListNode;

/**
 * @ingroup vos_list
 * 链表头
 */
typedef struct {
    VosRawListNode    head;     /**< 链表头 */
    size_t            count;    /**< 链表上的节点个数 */
    VosDupFreeFuncPair dataFunc;
} VosList;

/**
 * @ingroup vos_list
 * 链表迭代器定义
 */
typedef VosRawListNode *VosListIterator;

/**
 * @ingroup vos_list
 * @brief 初始化链表
 * @par 描述：初始化链表，按需注册用户数据dup函数和用户数据资源free函数。\n
 * dup 函数为NULL，表示链表中的用户数据类型是 int 型的，且长度 <= sizeof(uintptr_t)；其它情况，dup 函数都不能为空。\n
 * free 函数为NULL，表示链表中的用户数据类型是 int 型的，且长度 <= sizeof(uintptr_t)；其它情况，free 函数都不能为空。
 * @param list      [IN] 链表
 * @param dupFunc   [IN] 用户数据dup函数
 * @param freeFunc  [IN] 用户数据free函数
 */
static void VOS_ListInit(VosList *list, VosDupFreeFuncPair *dataFunc);

/**
 * @ingroup vos_list
 * @brief 链表去初始化
 * @par 描述：链表去初始化：删除所有节点，调用户注册的free函数释放用户资源，去注册钩子函数。
 * @param list        [IN]  链表
 */
static void VOS_ListDeinit(VosList *list);

/**
 * @ingroup vos_rawlist
 * @brief 检查链表是否为空
 * @param list    [IN] 待检查的链表
 * @retval #true  1，链表为空。
 * @retval #false 0，链表不为空。
 */
static bool VOS_ListEmpty(const VosList *list);

/**
 * @ingroup vos_rawlist
 * @brief 获取链表中节点个数
 * @param list  [IN] 链表
 * @retval 链表节点个数
 */
static size_t VOS_ListSize(const VosList *list);

/**
 * @ingroup vos_list
 * @brief 在链表头插入用户数据。
 * @param list      [IN] 链表
 * @param userData  [IN] 待插入的数据或指向用户私有数据的指针
 * @retval VOS_OK       插入数据成功
 * @retval VOS_ERROR    插入数据失败（内存可能分配失败）
 */
static uint32_t VOS_ListPushFront(VosList *list, uintptr_t userData);

/**
 * @ingroup vos_list
 * @brief 在链表尾插入用户数据
 * @param list      [IN] 链表
 * @param userData  [IN] 待插入的数据或指向用户私有数据的指针
 * @retval VOS_OK       插入数据成功
 * @retval VOS_ERROR    插入数据失败（内存可能分配失败）
 */
static uint32_t VOS_ListPushBack(VosList *list, uintptr_t userData);

/**
 * @ingroup vos_list
 * @brief 从链表头部POP一个节点
 * @par 描述：从链表中移除头节点，同时释放节点内存。如果在初始化时注册了free函数，还会调该钩子函数释放用户私有资源。\n
 * 如果链表为空，则不做任何事情。
 * @param list [IN]  链表
 */
static void VOS_ListPopFront(VosList *list);

/**
 * @ingroup vos_list
 * @brief 从链表尾部POP一个节点。
 * @par 描述：从链表中移除尾节点，同时释放节点内存。如果在初始化时注册了free函数，还会调该钩子函数释放用户私有资源。\n
 * 如果链表为空，则不做任何事情。
 * @param list [IN]  链表
 */
static void VOS_ListPopBack(VosList *list);

/**
 * @ingroup vos_list
 * @brief 访问链表头节点，返回头节点的用户数据。
 * @par 描述：访问链表头节点，返回头节点的用户数据
 * @attention 注意：如果链表为空，则不能区分是因为链表为空返回0，还是返回的真实数据就是0。\n
 * 因此用户在调用本函数前必须先判链表是否为空。
 * @param list [IN] 链表
 * @retval 头节点的用户数据/指针。如果链表为空，则返回0。
 */
static uintptr_t VOS_ListFront(VosList *list);

/**
 * @ingroup vos_list
 * @brief 访问链表尾节点，返回尾节点的用户数据。
 * @attention 注意：如果链表为空，则不能区分是因为链表为空返回0，还是返回的真实数据就是0。\n
 * 因此用户在调用本函数前必须先判链表是否为空。
 * @param list  [IN] 链表
 * @retval 尾节点的用户数据/指针。如果链表为空，则返回0。
 */
static uintptr_t VOS_ListBack(VosList *list);

/**
 * @ingroup vos_list
 * @brief 获取链表头节点迭代器。
 * @param list [IN] 链表
 * @retval 链表头节点迭代器。如果链表为空，则指向链表头。
 */
static VosListIterator VOS_ListIterBegin(VosList *list);

/**
 * @ingroup vos_list
 * @brief 获取链表尾节点的下一个节点迭代器
 * @param list  [IN] 链表
 * @retval 链表尾节点的下一个节点迭代器（指向链表头）。
 */
static VosListIterator VOS_ListIterEnd(VosList *list);

/**
 * @ingroup vos_list
 * @brief 获取下一个节点迭代器
 * @param list [IN] 链表
 * @param it   [IN] 迭代器
 * @retval 下一个节点迭代器。
 */
static VosListIterator VOS_ListIterNext(VosList *list, VosListIterator it);

/**
 * @ingroup vos_list
 * @brief 在指定迭代器指向的节点前插入数据。
 * @param list      [IN] 链表
 * @param it        [IN] 当前迭代器位置
 * @param userData  [IN] 待插入的数据或指向用户私有数据的指针
 * @retval  0  插入数据成功
 * @retval  1  插入数据失败（内存可能分配失败）
 */
static uint32_t VOS_ListInsert(VosList *list, VosListIterator it, uintptr_t userData);

/**
 * @ingroup vos_list
 * @brief 删除链表中指定节点，同时释放节点内存。
 * @par 描述：从链表中删除指定节点，同时释放节点内存。\n
 * 如果在初始化时注册了free函数，还会调该钩子函数释放用户数据中的句柄、指针等私有资源。
 * @param list [IN] 链表
 * @param it   [IN] 待删除的节点迭代器
 * @retval 被删除节点的下一个节点迭代器，如果被删除节点是尾节点，则返回的迭代器指向链表头
 */
static VosListIterator VOS_ListIterErase(VosList *list, VosListIterator it);

/**
 * @ingroup vos_list
 * @brief 获取用户数据
 * @attention 注意：调用者必须保证参数的合法性。如果入参非法，则返回0，调用者不能区分是正常数据，还有由于参数非法返回的0。
 * @param it [IN] 链表迭代器
 * @retval 用户数据
 */
static uintptr_t VOS_ListIterData(VosListIterator it);

#ifdef __cplusplus
}
#endif

#include "vos_list_impl.h"

#endif /* VOS_LIST_H */
