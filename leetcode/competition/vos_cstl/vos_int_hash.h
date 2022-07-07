/**
 * @defgroup vos_hash key为int的哈希表
 * @ingroup hash
 */
#ifndef VOS_INT_HASH_H
#define VOS_INT_HASH_H

#include "vos_hash.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline VosHash *VOS_IntHashCreate(size_t bktSize)
{
    VosHash *hash = VOS_HashCreate(bktSize, VOS_HashCodeCalcInt, VOS_HashMatchInt, NULL, NULL);
    return hash;
}

static inline uint32_t VOS_IntHashInsert(VosHash *hash, int key, uintptr_t value)
{
    uintptr_t intKey = (uintptr_t)key;
    return VOS_HashInsert(hash, intKey, value);
}

static inline VosHashIterator VOS_IntHashFind(VosHash *hash, int key)
{
    uintptr_t intKey = (uintptr_t)key;
    VosHashIterator valuePtr = VOS_HashFind(hash, intKey);
    return valuePtr;
}

static inline VosHashIterator VOS_IntHashErase(VosHash *hash, int key)
{
    uintptr_t intKey = (uintptr_t)key;
    return VOS_HashErase(hash, intKey);
}

#ifdef __cplusplus
}
#endif

#endif
