/**
 * @defgroup vos_string 字符串辅助函数
 * @ingroup string
 */
#ifndef VOS_STRING_H
#define VOS_STRING_H
#include <string.h>
#include "securec.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline void* StrKeyDupFunc(void *ptr)
{
    char *origKey = (char*)ptr;
    size_t len = strlen(origKey);
    char *key = (char*)malloc(len + 1);
    if (key == NULL) {
        return NULL;
    }
    strncpy(key, origKey, len + 1);
    key[len] = 0;
    return key;
}

#ifdef __cplusplus
}
#endif

#endif

