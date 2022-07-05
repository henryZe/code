/*
 * @file vos_hash.h
 * Description: hash表头文件
 */

/**
 * @defgroup vos_hash 哈希表
 * @ingroup cstl
 */
#ifndef VOS_HASH_H
#define VOS_HASH_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "vos_common.h"
#include "securec.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup vos_hash
 * @brief hash表句柄
 */
typedef struct vosHash VosHash;

/**
 * @ingroup vos_hash
 * @brief hash表迭代器定义，指向hash节点
 */
//typedef struct tagHashNode *VosHashIterator;
// 根据评审意见修改:用户感知不到，把 VosHashIterator 定义成void*
typedef void *VosHashIterator;

/**
 * @ingroup vos_hash
 * @brief 根据输入的Key生成hash表索引。
 * @param key      [IN] hash key
 * @param bktSize  [IN] hash桶大小
 */
typedef size_t (*VosHashCodeCalcFunc)(uintptr_t key, size_t bktSize);

/**
 * @ingroup vos_hash
 * @brief 该函数把输入数据与Key进行匹配比较。如果不匹配，返回值为false。
 * @param key1     [IN] 哈希表中保存的key
 * @param key2     [IN] 待匹配的key
 * @retval #true key1和key2匹配。
 * @retval #false key1和key2不匹配。
 */
typedef bool (*VosHashMatchFunc)(uintptr_t key1, uintptr_t key2);

/**
 * @ingroup vos_hash
 * @brief 默认整型哈希函数。
 * @par 默认整型哈希函数。
 * @attention \n
 *  1.key为用户调用其他接口时的入参。\n
 *  2.若key为整型，用户可在创建hash时将该函数作为hashFunc参数。\n
 * @param key      [IN] 待计算的key。
 * @param bktSize  [IN] 哈希桶大小。
 * @retval #哈希值 根据用户key计算出的哈希值。
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline size_t VOS_HashCodeCalcInt(uintptr_t key, size_t bktSize);

/**
 * @ingroup vos_hash
 * @brief 默认字符串哈希函数。
 * @par 默认字符串哈希函数。
 * @attention \n
 *  1.key为用户调用其他接口时的入参，用户必须保证传入的key为合法的字符串首地址。\n
 *  2.若key为字符串，用户可在创建hash时将该函数作为hashFunc参数。\n
 * @param key      [IN] 待计算的key。
 * @param bktSize  [IN] 哈希桶大小。
 * @retval #哈希值 根据用户key计算出的哈希值。
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline size_t VOS_HashCodeCalcStr(uintptr_t key, size_t bktSize);

/**
 * @ingroup vos_hash
 * @brief 默认整型匹配函数。
 * @par 默认整型匹配函数。
 * @attention \n
 *  1.key为用户调用其他接口时的入参。\n
 *  2.若key为整型，用户可在创建hash时将该函数作为matchFunc参数。\n
 * @param key1      [IN] 待匹配的key。
 * @param key2      [IN] 待匹配的key。
 * @retval #true    key1和key2匹配。
 * @retval #false   key1和key2不匹配。
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline bool VOS_HashMatchInt(uintptr_t key1, uintptr_t key2);

/**
 * @ingroup vos_hash
 * @brief 默认字符串匹配函数。
 * @par 默认字符串匹配函数。
 * @attention \n
 *  1.key1为用户调用其他接口时的入参，用户必须保证传入的key1为合法的字符串首地址。\n
 *  2.若key为字符串，用户可在创建hash时将该函数作为matchFunc参数。\n
 * @param key1      [IN] 待匹配的key。
 * @param key2      [IN] 待匹配的key。
 * @retval #true    key1和key2匹配。
 * @retval #false   key1和key2不匹配。
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline bool VOS_HashMatchStr(uintptr_t key1, uintptr_t key2);

/**
 * @ingroup vos_hash
 * @brief 创建一个Hash表，返回Hash表的句柄
 * @attention \n
 * 1、关于key和data的拷贝函数：\n
 * 如下场景不需要注册拷贝函数：如果是int型数据，且长度<=sizeof(uintptr_t)。\n
 * 其它场景必须注册拷贝函数：\n
 * a）是int型数据，但长度 >sizeof(uintptr_t)；\n
 * b）字符串；\n
 * c）用户自定义数据结构；\n
 * 2、关于free函数：简单来说，如果注册了duplicate函数，就必须注册相应的free函数。 \n
 * 3、提供默认的整型、字符串哈希函数：#VOS_HashCodeCalcInt、#VOS_HashCodeCalcStr。 \n
 * 4、提供默认的整型、字符串匹配函数：#VOS_HashMatchInt、#VOS_HashMatchStr。 \n
 * @param bktSize       [IN] hash桶的个数
 * @param hashCalcFunc  [IN] hash值计算函数。如果为NULL，则默认key为整型，使用#VOS_HashCodeCalcInt。
 * @param matchFunc     [IN] hash key匹配函数。如为NULL，则默认key为整型，使用#VOS_HashMatchInt。
 * @param keyFunc       [IN] hash key拷贝及释放函数对，如果用户未注册keyFunc->dupFunc，则默认为key为整型。
 * @param valueFunc      [IN] hash data拷贝及释放函数对。如果用户未注册valueFunc->dupFunc，则默认为data为整型。
 * @retval hash表句柄。NULL表示创建失败。
 * @par 依赖：无
 * @see #VOS_HashCodeCalcInt、#VOS_HashCodeCalcStr、#VOS_HashMatchInt、#VOS_HashMatchStr。
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline VosHash *VOS_HashCreate(size_t bktSize, 
                        VosHashCodeCalcFunc hashCalcFunc, 
                        VosHashMatchFunc matchFunc, 
                        VosDupFreeFuncPair *keyFunc, 
                        VosDupFreeFuncPair *valueFunc);

/**
 * @ingroup vos_hash
 * @brief 插入hash数据
 * @par 描述：创建节点，把数据(key、value)插入hash表
 * @attention
 *  1.不支持重复key。\n
 *  2.key和value为整型值或指向用户key或value的地址。\n
 *  3.如果扩展数据的生命周期小于节点的生命周期，则需要在创建哈希表时注册拷贝函数及释放函数。\n
 * @param hash          [IN] hash表的句柄。
 * @param key           [IN] key或保存key的地址。
 * @param value         [IN] value或保存value的地址。
 * @retval #VOS_OK      插入节点成功。
 * @retval #VOS_ERROR   插入节点失败。
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline uint32_t VOS_HashInsert(VosHash *hash, uintptr_t key, uintptr_t value);

/**
 * @ingroup vos_hash
 * @brief 插入或更新hash数据
 * @par 描述：该接口用于将不存在的key插入到哈希表或更新已存在的key对应的value。
 * @attention
 *  1.支持重复key。\n
 *  2.当key不存在时，该接口的使用与#VOS_HashInsert保持一致。\n
 *  3.当key存在时，该接口会更新value。\n
 * @param hash          [IN] hash表的句柄。
 * @param key           [IN] key或保存key的地址。
 * @param value         [IN] value或保存value的地址。
 * @retval #VOS_OK      插入或更新节点成功。
 * @retval #VOS_ERROR   插入或更新节点失败。
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline uint32_t VOS_HashPut(VosHash *hash, uintptr_t key, uintptr_t value);

/**
 * @ingroup vos_hash
 * @brief 查找节点，返回节点数据。
 * @par 描述: 根据key查找并返回节点数据。
 * @param hash          [IN]  hash表的句柄。
 * @param key           [IN]  key或保存key的地址。
 * @param value         [OUT] 查到的数据。
 * @retval #VOS_OK      查找成功。
 * @retval #VOS_ERROR   查找失败。
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline uint32_t VOS_HashAt(const VosHash *hash, uintptr_t key, uintptr_t *value);

/**
 * @ingroup vos_hash
 * @brief 查找key所在迭代器。
 * @par 描述: 根据key查找并返回key所在的迭代器。
 * @param hash   [IN] hash表的句柄。
 * @param key    [IN] key或保存key的地址。
 * @retval key存在时，返回key所在迭代器（指向Node所在地址）,其他情况返回#VOS_HashIterEnd()。
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline VosHashIterator VOS_HashFind(const VosHash *hash, uintptr_t key);

/**
 * @ingroup vos_hash
 * @brief 判断当前HASH表是否为空。
 * @par 描述: 判断当前HASH表是否为空，为空返回true，否则返回false。
 * @param  hash [IN] hash表句柄。取值范围为有效指针。
 * @retval #true， 表示HASH表为空。
 * @retval #false，表示HASH表非空。
 * @see #VOS_HashSize
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline bool VOS_HashEmpty(const VosHash *hash);

/**
 * @ingroup vos_hash
 * @brief 获取HASH表的节点数量。
 * @par 描述: 用于获取HASH表的节点数量，返回节点个数。
 * @param  hash [IN] hash表句柄。取值范围为有效指针。
 * @retval hash节点数。
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline size_t VOS_HashSize(const VosHash *hash);

/**
 * @ingroup vos_hash
 * @brief 从hash表中移除指定结点。
 * @par 描述: 根据key查找到节点并删除（释放内存），同时释放相应的节点内存。
 * @param hash [IN] hash表句柄。取值范围为有效指针。
 * @param key   [IN] 移除节点key。
 * @retval key存在时，返回key所在迭代器的下一个迭代器（指向Node所在地址）,其他则返回#VOS_HashIterEnd()。
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline VosHashIterator VOS_HashErase(VosHash *hash, uintptr_t key);

/**
 * @ingroup vos_hash
 * @brief 删除hash表所有节点。
 * @par 描述：删除所有节点，回收节点内存（hash表还在，只是没有成员）。
 * @attention 注意：如果用户数据中有私有资源，则需要在创建时注册free钩子函数。
 * @param  hash [IN] hash表句柄。
 * @retval 无。
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline void VOS_HashClear(VosHash *hash);

/**
 * @ingroup vos_hash
 * @brief 删除hash表
 * @par 描述：删除hash表，如里面有节点先删除节点，回收内存。
 * @attention 注意：如果用户数据中有私有资源，则需要在创建时注册free钩子函数。
 * @param  hash [IN] hash表句柄。
 * @retval 无。
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline void VOS_HashDestroy(VosHash *hash);

/**
 * @ingroup vos_hash
 * @brief 获取hash表中的第一个节点的迭代器。
 * @par 描述：获取hash表中的第一个节点所在的迭代器。
 * @param hash  [IN]  hash表的句柄。
 * @retval 第一个节点迭代器，若hash为空则返回#VOS_HashIterEnd()。
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline VosHashIterator VOS_HashIterBegin(const VosHash *hash);

/**
 * @ingroup vos_hash
 * @brief 获取hash表中最后一个节点之后预留的迭代器。
 * @par 描述：获取hash表中的最后一个节点之后预留的迭代器。该节点指向最后保留的hash桶，该桶没有任何成员。
 * @param hash  [IN]  hash表的句柄。
 * @retval 最后一个节点之后预留的迭代器。
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline VosHashIterator VOS_HashIterEnd(const VosHash *hash);

/**
 * @ingroup vos_hash
 * @brief 获取hash表的下一个节点迭代器。
 * @par 描述：获取hash表下一个节点迭代器。
 * @param hash     [IN]  hash表的句柄。
 * @param it       [IN]  当前迭代器。
 * @retval 下一个节点迭代器。若当前节点已是最后一个迭代器则返回#VOS_HashIterEnd()。
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline VosHashIterator VOS_HashIterNext(const VosHash *hash, VosHashIterator it);

/**
 * @ingroup vos_hash
 * @brief 获取迭代器的key。
 * @par 描述：获取hash表中迭代器当前key。
 * @attention \n
 *  1.当hash为空指针或it等于#VOS_HashIterEnd()时，接口返回0，该接口无法区分是错误码还是用户数据，
 *    用户调用该接口时必须保证hash为合法指针，并且it不等于#VOS_HashIterEnd()
 * @param hash     [IN]  hash表的句柄。
 * @param it       [IN]  当前迭代器。
 * @retval 迭代器对应的key。it等于#VOS_HashIterEnd()时则返回0。
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline uintptr_t VOS_HashIterKey(const VosHash *hash, VosHashIterator it);

/**
 * @ingroup vos_hash
 * @brief 获取迭代器的value。
 * @par 描述：获取hash表中迭代器当前key。
 * @attention \n
 *  1.当hash为空指针或it等于#VOS_HashIterEnd()时，接口返回0，该接口无法区分是错误码还是用户数据，
 *    用户调用该接口时必须保证hash为合法指针，并且it不等于#VOS_HashIterEnd()
 * @param hash     [IN]  hash表的句柄。
 * @param it       [IN]  当前迭代器。
 * @retval 迭代器对应的value。it等于#VOS_HashIterEnd()时则返回0。
 * @par 依赖：无
 * <ul><li>vos_hash.h：该接口声明所在的头文件。</li></ul>
 */
static inline uintptr_t VOS_HashIterValue(const VosHash *hash, VosHashIterator it);

#ifdef __cplusplus
}
#endif
#include "vos_hash_impl.h"

#endif /* VOS_HASH_H */

