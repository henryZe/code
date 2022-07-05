/**
 * @defgroup vos_vector_impl
 */
#ifndef VOS_VECTOR_IMPL_H
#define VOS_VECTOR_IMPL_H


#ifdef __cplusplus
extern "C" {
#endif

static inline VosVector *VOS_VectorCreate(size_t itemSize)
{
    UT_icd icd = {itemSize, NULL, NULL, NULL};
    UT_array *array;
    utarray_new(array, &icd);
    return array;
}

static inline VosVector *VOS_VectorRawCreate(size_t itemSize, size_t itemCap, uint32_t delta)
{
    return NULL;
}

static inline uint32_t VOS_VectorPushBack(VosVector *vector, const void *data)
{
    utarray_push_back(vector, data);
    return VOS_OK;
}

static inline void *VOS_VectorAt(const VosVector *vector, size_t index)
{
    if (index >= VOS_VectorSize(vector)) { return NULL; }
    return utarray_eltptr(vector, index);
}

static inline size_t VOS_VectorSize(const VosVector *vector)
{
    return utarray_len(vector);
}

static inline uint32_t VOS_VectorErase(VosVector *vector, size_t index)
{
    utarray_erase(vector, index, 1);
    return VOS_OK;
}

static inline void VOS_VectorClear(VosVector *vector, VosFreeFunc freeFunc)
{
    utarray_clear(vector);
}

static inline void VOS_VectorSort(VosVector *vector, VosDataCmpFunc cmpFunc)
{
    if (VOS_VectorSize(vector) > 0) {
        utarray_sort(vector, cmpFunc);
    }
}

static inline void *VOS_VectorSearch(const VosVector *vector, const void *data, VosDataCmpFunc cmpFunc)
{
    if (VOS_VectorSize(vector) == 0) {
        return NULL;
    }
    return utarray_find(vector, data, cmpFunc);
}

static inline void VOS_VectorDestroy(VosVector *vector, VosFreeFunc freeFunc)
{
    utarray_free(vector);
}


#ifdef __cplusplus
}
#endif

#endif /* VOS_VECTOR_PRIVATE_H */
