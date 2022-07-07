#ifndef __VOS_COMMON_IMPL__
#define __VOS_COMMON_IMPL__
#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "securec.h"

#ifdef __cplusplus
extern "C" {
#endif

#define WORD_LEN_32                 4

/*
* @brief �ж���������ڵ�ǰϵͳ�»�����
*/
static inline bool IsMultiOverflow(size_t x, size_t y)
{
    if (x == 0 || y == 0) {
        return false;
    }

    if (sizeof(size_t) == WORD_LEN_32) {
        if (UINT_MAX / x < y) {
            return true;
        }
    } else {
        if (ULLONG_MAX / x < y) {
            return true;
        }
    }
    
    return false;
}

/*
* @brief �ж���������ڵ�ǰϵͳ�»�����
*/
static inline bool IsAddOverflow(size_t x, size_t y)
{
    size_t add = x + y;
    
    return ((add < x) || (add < y));
}

/**
 * @ingroup vos_set
 * vos_setĬ�ϱȽϺ���
 */
static inline int32_t VOS_IntCmpFunc(uintptr_t data1, uintptr_t data2)
{
    return (int32_t)(data1 - data2); 
}

static inline int32_t VOS_StrCmpFunc(uintptr_t data1, uintptr_t data2)
{
    char *tmpData1 = (char *)data1;
    char *tmpData2 = (char *)data2;

    return strcmp(tmpData1, tmpData2); 
}

#ifdef __cplusplus
}
#endif

#endif  /* __VOS_COMMON_IMPL__ */
