/**
 * @defgroup vos_vector 
 */
#ifndef VOS_VECTOR_H
#define VOS_VECTOR_H

#include "vos_common.h"
#include "utarray.h"
#include "securec.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @ingroup vos_vector
* vector资源控制块
*/
typedef UT_array VosVector;



/**
 * @ingroup vos_vector
 * @brief vector创建
 * @par 描述: 创建一个vector实例
 * @attention
 * 创建一个新的vector，用户只需制定成员大小
 * @param  itemSize         [IN]  vector中单个元素的大小
 * @retval 返回vector控制块地址，创建成功
 * @retval NULL, 创建失败
 */
static VosVector *VOS_VectorCreate(size_t itemSize);

/**
 * @ingroup vos_vector
 * @brief vector创建
 * @par 描述: 创建一个vector实例（暂不支持）
 * @attention
 * 创建一个新的vector，用户只需制定成员大小，默认成员容量为2（即可以容纳两个成员），2倍递增
 * @param  itemSize   [IN]  vector中单个元素的大小
 * @param  itemCap    [IN]  vector中初始成员容量
 * @param  delta      [IN]  vector成员伸缩变化率
 * @retval 返回vector控制块地址，创建成功
 * @retval NULL, 创建失败
 */
static VosVector *VOS_VectorRawCreate(size_t itemSize, size_t itemCap, uint32_t delta);

/**
 * @ingroup vos_vector
 * @brief vector尾部添加元素
 * @par 描述: 在vector末尾插入节点
 * @attention
 * 把data指针指向的内容拷贝到最后一个成员位置；如容量已满，则动态扩展（内存申请可能失败）后再拷贝。
 * @param  vector        [IN]  vector控制块
 * @param  data          [IN]  待插入节点数据（数据拷贝vector尾部）
 * @retval 0，插入成功
 * @retval 1，插入失败。
 */
static uint32_t VOS_VectorPushBack(VosVector *vector, const void *data);

/**
 * @ingroup vos_vector
 * @brief 访问指定节点
 * @par 描述: 根据索引号，返回指定索引的节点指针
 * @attention 待访问元素的索引需要小于Vector的Size
 * @param  vector        [IN]  vector控制块
 * @param  index         [IN]  待访问的节点索引
 * @retval 返回索引为index的节点指针
 * @retval NULL 查找失败
 */
static void *VOS_VectorAt(const VosVector *vector, size_t index);

/**
 * @ingroup vos_vector
 * @brief 查询vector元素个数
 * @par 描述: 查询一个vector中已经存储的元素的个数
 * @attention 无
 * @param  vector  [IN]  vector控制块
 * @retval  元素个数
 * @par 依赖：无
 * <ul><li>vos_vector.h：该接口声明所在的头文件。</li></ul>
 */
static size_t VOS_VectorSize(const VosVector *vector);


/**
 * @ingroup vos_vector
 * @brief vector删除元素
 * @par 描述：删除实例中的一个元素，后面的数据会往前搬移，不会导致数据空洞
 * @attention 待删除元素的索引需要小于Vector的Size
 * @param  vector         [IN]  需要被删除元素的实例
 * @param  index          [IN]  待删除的元素所在的索引
 * @retval 0 删除成功
 * @retval 1 删除失败
 * @par 依赖：无
 * <ul><li>vos_vector.h：该接口声明所在的头文件。</li></ul>
 */
static uint32_t VOS_VectorErase(VosVector *vector, size_t index);

/**
 * @ingroup vos_vector
 * @brief 清除vector所有元素
 * @par 描述: 清除vector中的所有的元素，同时vector容量恢复到默认值。
 * @attention
 * 如果用户数据中有指针或其它资源，用户必须先行释放这些资源。
 * @param  vector  [IN]  待清除的vector实例
 * @param  freeFunc     [IN]  资源释放方法
 * @retval 无
 * @par 依赖：无
 * <ul><li>vos_vector.h：该接口声明所在的头文件。</li></ul>
 */
static void VOS_VectorClear(VosVector *vector, VosFreeFunc freeFunc);

/**
 * @ingroup vos_vector
 * @brief 将vector中的元素进行排序
 * @par 描述: 对vector中的元素进行排序
 * @attention 无
 * @param  vector             [IN]  被排序的vector
 * @param  compareFun         [IN]  排序方法
 * @retval 无
 * @par 依赖：无
 * <ul><li>vos_vector.h：该接口声明所在的头文件。</li></ul>
 */
static void VOS_VectorSort(VosVector *vector, VosDataCmpFunc cmpFunc);

/**
 * @ingroup vos_vector
 * @brief 在vector内查找目标数据，返回其所在的指针。
 * @par 描述: 在vector内查找目标数据，返回其所在的指针
 * @attention 注意：在调本函数进行search前，用户必须先调 VOS_VectorSort 进行排序，否则返回的结果没任何意义。
 * @param  vector      [IN]  被查找的vector
 * @param  data        [IN]  查找索引
 * @param  cmpFunc     [IN]  查找方法
 * @retval vector实例中目标元素所在的地址。如未找到，则返回NULL。
 * @par 依赖：无
 * <ul><li>vos_vector.h：该接口声明所在的头文件。</li></ul>
 */
static void *VOS_VectorSearch(const VosVector *vector, const void *data, VosDataCmpFunc cmpFunc);

/**
 * @ingroup vos_vector
 * @brief vector销毁
 * @par 描述: 销毁vector实例
 * @attention 
 * 本接口不仅删除所有成员，还把控制块一并删除。如果用户数据中有指针或其它资源，用户必须先行释放这些资源。
 * @param  vector       [IN]  被销毁的实例
 * @param  freeFunc     [IN]  资源释放方法
 * @retval 无
 * @par 依赖：无
 * <ul><li>vos_vector.h：该接口声明所在的头文件。</li></ul>
 */
static void VOS_VectorDestroy(VosVector *vector, VosFreeFunc freeFunc);

#ifdef __cplusplus
}
#endif

#include "vos_vector_impl.h"

#endif /* VOS_VECTOR_H */
