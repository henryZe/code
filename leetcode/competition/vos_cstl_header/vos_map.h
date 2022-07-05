/**
 * @defgroup vos_map Map表
 * @ingroup cstl
 */
#ifndef VOS_MAP_H
#define VOS_MAP_H

#include <stdbool.h>
#include "vos_common.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @ingroup vos_map
 * vos_map控制块
 */
typedef struct tagVosMap VosMap;

/**
 * @ingroup vos_map
 * vos_map迭代器
 */
typedef struct tagVosMapNode *VosMapIterator;

/**
 * @ingroup vos_map
 * @brief 创建map。
 * @par 描述：创建一个map，并返回其控制块指针。
 * @attention \n
 * 1.map存储的key和value均为uintptr_t类型。\n
 * 2.用户未注册keyCmpFunc函数时，将使用默认比较函数，key会被默认为整型。\n
 * 3.当用户key或value为字符串或其他复杂类型时，应将其地址作为参数（需强转为uintptr_t类型），
     若该地址指向栈内存，建议注册keyDupFunc或valueDupFunc进行key或数据的拷贝，返回对应的堆内存地址。\n
 * 4.若用户key或value为字符串或其他复杂类型，释放map表或擦除节点时，
     用户需自行释放资源或注册keyFunc->freeFunc、valueFunc->freeFunc。
 * @param  keyCmpFunc   [IN]  key的比较函数。
 * @param  keyFunc      [IN]  key拷贝及释放函数对。
 * @param  valueFunc    [IN]  data拷贝及释放函数对。
 * @retval 指向map控制块的指针，NULL表示创建失败。
 * @par 依赖：无。
 * @li vos_map.h：该接口声明所在的文件。
 */
static inline VosMap *VOS_MapCreate(VosKeyCmpFunc keyCmpFunc, VosDupFreeFuncPair *keyFunc, VosDupFreeFuncPair *valueFunc);

/**
 * @ingroup vos_map
 * @brief 向map表中插入一个(K,V)对。
 * @par 描述：用户数据插入后，会调用钩子keyCmpFunc完成排序。
 * @attention \n
 * 1.不支持重复的key。\n
 * 2.key或value为int类型时，直接将值作为参数即可。\n
 * 3.当用户key或value为字符串或其他复杂类型时，应将其地址作为参数（需强转为uintptr_t类型），\n
     如char *key, 则入参应为(uintptr_t)key。
 * @param map           [IN] map控制块。
 * @param key           [IN] key或保存key的地址。
 * @param value         [IN] value或保存value的地址。
 * @retval #VOS_OK      插入成功。
 * @retval #VOS_ERROR   插入失败。
 * @par 依赖：无
 * @li vos_map.h：该接口声明所在的文件。
*/
static inline uint32_t VOS_MapInsert(VosMap *map, uintptr_t key, uintptr_t value);

/**
 * @ingroup vos_map
 * @brief 向map表中插入一个(K,V)对或更新K对应的V。
 * @par 描述：该接口用于插入新节点或更新节点。
 * @attention \n
 * 1.支持重复的key。\n
 * 2.当key不存在时，新增节点。\n
 * 3.当key存在时，会更新key对应的value。\n
 * @param map           [IN] map控制块。
 * @param key           [IN] key或保存key的地址。
 * @param value         [IN] value或保存value的地址。
 * @retval #VOS_OK      插入或更新节点成功。
 * @retval #VOS_ERROR   插入或更新节点失败。
 * @par 依赖：无
 * @li vos_map.h：该接口声明所在的文件。
*/
static inline uint32_t VOS_MapPut(VosMap *map, uintptr_t key, uintptr_t value);

/**
 * @ingroup vos_map
 * @brief 删除一个数据，并释放节点内存。
 * @par 描述：删除map中key对应的数据，并释放节点内存。
 * @attention \n
 * 1.该接口用于从map表中删除key对应的节点。\n
 * 2.key对应的节点存在时，返回下一个节点的迭代器，
 *  若key不存在或对应节点为最后一个节点，则返回VOS_MapIterEnd()。
 * @param map       [IN] map控制块。
 * @param key       [IN] 待删除的key。
 * @retval #被删除节点的下一个节点迭代器，如果被删除key不存在或为最后一个节点，则返回VOS_MapIterEnd()。
 * @par 依赖：无
 * @li vos_map.h：该接口声明所在的文件。
 * @see #VOS_MapFind
 */
static inline VosMapIterator VOS_MapErase(VosMap *map, uintptr_t key);

/**
 * @ingroup vos_map
 * @brief 获取map中key对应的数据。
 * @param map           [IN]  map控制块。
 * @param key           [IN]  用户指定的key。
 * @param value         [OUT] 保存key对应的数据。
 * @retval #VOS_OK      获取成功。
 * @retval #VOS_ERROR   获取失败，map为空指针、value为空指针或对应的key不存在。
 * @par 依赖：无。
 * @li vos_map.h：该接口声明所在的文件。
 * @see #VOS_MapFind
 */
static inline uint32_t VOS_MapAt(const VosMap *map, uintptr_t key, uintptr_t *value);

/**
 * @ingroup vos_map
 * @brief 获取map中key对应的数据。
 * @param map       [IN] map控制块。
 * @param key       [IN] 待获取的key。
 * @retval #返回key对应的迭代器。如果key不存在，则返回VOS_MapIterEnd()。
 * @par 依赖：无。
 * @li vos_map.h：该接口声明所在的文件。
 */
static inline VosMapIterator VOS_MapFind(const VosMap *map, uintptr_t key);

/**
 * @ingroup vos_map
 * @brief 获取map中成员个数
 * @param map  [IN] map控制块。
 * @retval #map成员个数
 * @retval #0，map为空指针。
 * @par 依赖：无
 * @li vos_map.h：该接口声明所在的头文件。
 */
static inline size_t VOS_MapSize(const VosMap *map);

/**
 * @ingroup vos_map
 * @brief 判断map是否为空
 * @param map       [IN] map控制块。
 * @retval #true，  表示map为空或map为NULL指针
 * @retval #false， 表示map为非空。
 * @par 依赖：无
 * @li vos_map.h：该接口声明所在的头文件。
 */
static inline bool VOS_MapEmpty(const VosMap *map);

/**
 * @ingroup vos_map
 * @brief 获取map表中的第一个节点的迭代器。
 * @param map  [IN] map控制块。
 * @retval #第一个迭代器。当map中无节点时，返回VOS_MapIterEnd()。
 * @par 依赖：无
 * @li vos_map.h：该接口声明所在的头文件。
 */
static inline VosMapIterator VOS_MapIterBegin(const VosMap *map);

/**
 * @ingroup vos_map
 * @brief 获取map表中的下一个节点的迭代器。
 * @param map  [IN] map控制块。
 * @retval #下一个迭代器。当前迭代器已是最后一个节点时，返回#VOS_MapIterEnd()。
 * @par 依赖：无
 * @li vos_map.h：该接口声明所在的头文件。
 */
static inline VosMapIterator VOS_MapIterNext(const VosMap *map, VosMapIterator it);

/**
 * @ingroup vos_map
 * @brief 获取map表中最后一个节点之后预留的迭代器。
 * @param map  [IN] map控制块。
 * @retval 最后一个map节点之后预留的迭代器。
 * @par 依赖：无
 * @li vos_map.h：该接口声明所在的头文件。
 */
static inline VosMapIterator VOS_MapIterEnd(const VosMap *map);

/**
 * @ingroup vos_map
 * @brief 获取迭代器的key。
 * @par 描述：获取map表中迭代器当前key。
 * @attention \n
 *  1.当map为空指针或it等于#VOS_MapIterEnd()时，接口返回0，该接口无法区分是错误码还是用户数据，
 *    用户调用该接口时必须保证map为合法指针，并且it不等于#VOS_MapIterEnd()
 * @param map   [IN]  map控制块。
 * @param it    [IN]  当前迭代器。禁止传入非法指针。
 * @retval #迭代器对应的key。
 * @retval #0 it等于VOS_MapIterEnd()
 * @par 依赖：无
 * <ul><li>vos_map.h：该接口声明所在的头文件。</li></ul>
 */
static inline uintptr_t VOS_MapIterKey(const VosMap *map, VosMapIterator it);

/**
 * @ingroup vos_map
 * @brief 获取迭代器的value。
 * @par 描述：获取map表中迭代器当前key。
 * @attention \n
 *  1.当map为空指针或it等于#VOS_MapIterEnd()时，接口返回0，该接口无法区分是错误码还是用户数据，
 *    用户调用该接口时必须保证map为合法指针，并且it不等于#VOS_MapIterEnd()
 * @param hashTbl  [IN]  map表的句柄。
 * @param it       [IN]  当前迭代器。禁止传入非法指针。
 * @retval #迭代器对应的value。
 * @retval #0 it等于VOS_MapIterEnd()
 * @par 依赖：无
 * <ul><li>vos_map.h：该接口声明所在的头文件。</li></ul>
 */
static inline uintptr_t VOS_MapIterValue(const VosMap *map, VosMapIterator it);

static inline void VOS_MapClear(VosMap *map);

/**
 * @ingroup vos_map
 * @brief 删除map
 * @par 描述：删除map，如里面有成员先删除成员，再回收控制块内存。
 * @attention  \n
 *  1.该接口会删除map表中所有节点。\n
 *  2.若用户注册了key或data的资源释放函数，则会调用钩子进行用户资源释放。\n
 *  3.调用本接口后，map指针指向的内存被free，map表不可以再次访问。\n
 * @param  map [IN] map句柄。
 * @retval 无。
 * @par 依赖：无
 * <ul><li>vos_map.h：该接口声明所在的头文件。</li></ul>
 */
static inline void VOS_MapDestroy(VosMap *map);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#include "vos_map_impl.h"

#endif /* VOS_MAP_H */
