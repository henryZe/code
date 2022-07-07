/**
 * @defgroup vos_hash key为字符串的哈希表
 * @ingroup hash
 */
#ifndef VOS_STR_HASH_H
#define VOS_STR_HASH_H

#include "vos_hash.h"
#include "vos_string.h"

#ifdef __cplusplus
extern "C" {
#endif

// StringHash
static inline VosHash *VOS_StrHashCreate(size_t bktSize)
{
    VosDupFreeFuncPair keyFunc;
    keyFunc.dupFunc = StrKeyDupFunc;
    keyFunc.freeFunc = free;

    VosHash *hash = VOS_HashCreate(bktSize, VOS_HashCodeCalcStr, VOS_HashMatchStr, &keyFunc, NULL);
    return hash;
}

static inline uint32_t VOS_StrHashInsert(VosHash *hash, const char *key, uintptr_t value)
{
    return VOS_HashInsert(hash, (uintptr_t)key, value);
}

static inline VosHashIterator VOS_StrHashFind(VosHash *hash, const char *key)
{
    VosHashIterator valuePtr = VOS_HashFind(hash, (uintptr_t)key);
    return valuePtr;
}

static inline VosHashIterator VOS_StrHashErase(VosHash *hash, const char *key)
{
    return VOS_HashErase(hash, (uintptr_t)key);
}

#ifdef __cplusplus
}
#endif

#endif
