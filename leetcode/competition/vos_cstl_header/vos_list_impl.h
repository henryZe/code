#ifndef VOS_LIST_IMPL_H
#define VOS_LIST_IMPL_H

#ifdef __cplusplus
extern "C" {
#endif


static inline void VOS_ListInit(VosList *list, VosDupFreeFuncPair *dataFunc)
{
    list->count = 0;
    list->head.next = &list->head;
    list->head.prev = &list->head;
    if (dataFunc != NULL) {
        list->dataFunc.freeFunc = dataFunc->freeFunc;
        list->dataFunc.dupFunc = dataFunc->dupFunc;
    } else {
        list->dataFunc.freeFunc = NULL;
        list->dataFunc.dupFunc = NULL;
    }
}

static inline bool VOS_ListEmpty(const VosList *list)
{
    return list->head.next == &list->head;
}

static inline size_t VOS_ListSize(const VosList *list)
{
    return list->count;
}

static inline uint32_t DupUserData(VosDupFunc dupFunc, VosListNode* entry, uintptr_t userData)
{
    if (dupFunc == NULL) {
        entry->userdata = userData;
        return VOS_OK;
    }

    uintptr_t data = (uintptr_t)(dupFunc((void*)userData));
    if (data == (uintptr_t)NULL) { return VOS_ERROR; }
    entry->userdata = data;

    return VOS_OK;
}

static inline void VOS_RawListInsert(VosList *list, VosRawListNode *curNode, VosRawListNode *newNode)
{
    newNode->prev = curNode->prev;
    newNode->next = curNode;
    newNode->prev->next = newNode;
    newNode->next->prev = newNode;
    list->count++;
}

inline uint32_t VOS_ListPushFront(VosList *list, uintptr_t userData)
{
    VosListNode *entry = (VosListNode*)malloc(sizeof(VosListNode));
    if (entry == NULL) {
        return VOS_ERROR;
    }

    if (DupUserData(list->dataFunc.dupFunc, entry, userData) == VOS_ERROR) {
        free(entry);
        return VOS_ERROR;
    }

    VOS_RawListInsert(list, list->head.next, &entry->rawNode);

    return VOS_OK;
}

inline uint32_t VOS_ListPushBack(VosList *list, uintptr_t userData)
{
    VosListNode *entry = (VosListNode*)malloc(sizeof(VosListNode));
    if (entry == NULL) {
        return VOS_ERROR;
    }
    
    if (DupUserData(list->dataFunc.dupFunc, entry, userData) == VOS_ERROR) {
        free(entry);
        return VOS_ERROR;
    }

    VOS_RawListInsert(list, &list->head, &entry->rawNode);

    return VOS_OK;
}

inline uintptr_t VOS_ListFront(VosList *list)
{
    if (VOS_ListEmpty(list)) {
        return 0; // 无法区分是值为零，还是链表为空
    }
    VosListNode *node = (VosListNode*)list->head.next;

    return node->userdata;
}

inline uintptr_t VOS_ListBack(VosList *list)
{
    if (VOS_ListEmpty(list)) {
        return 0; // 无法区分是值为零，还是链表为空
    }
    VosListNode *node = (VosListNode*)list->head.prev;

    return node->userdata;
}

inline uintptr_t VOS_ListIterData(VosListIterator it)
{
    return ((VosListNode*)it)->userdata;
}

inline VosListIterator VOS_ListIterErase(VosList *list, VosListIterator it)
{
    uintptr_t data = VOS_ListIterData(it);
    if (list->dataFunc.freeFunc != NULL) {
        list->dataFunc.freeFunc((void*)data);
    }

    VosListIterator tmp = it->next;
    it->prev->next = it->next;
    it->next->prev = it->prev;
    list->count--;
    free(it);

    return tmp;
}

inline void VOS_ListPopFront(VosList *list)
{
    if (VOS_ListEmpty(list)) {
        return;
    }

    (void)VOS_ListIterErase(list, list->head.next);
}

inline void VOS_ListPopBack(VosList *list)
{
    if (VOS_ListEmpty(list)) {
        return;
    }

    (void)VOS_ListIterErase(list, list->head.prev);
}

inline VosListIterator VOS_ListIterBegin(VosList *list)
{
    if (VOS_ListEmpty(list)) {
        return &list->head;
    }    
    return list->head.next;
}

inline VosListIterator VOS_ListIterEnd(VosList *list)
{
    return &list->head;
}

inline VosListIterator VOS_ListIterNext(VosList *list, VosListIterator it)
{
    if (it == &list->head) {
        return it;
    }
    return it->next;
}

inline uint32_t VOS_ListInsert(VosList *list, VosListIterator it, uintptr_t userData)
{
    VosListNode *entry = (VosListNode*)malloc(sizeof(VosListNode));
    if (entry == NULL) {
        return VOS_ERROR;
    }

    if (DupUserData(list->dataFunc.dupFunc, entry, userData) == VOS_ERROR) {
        free(entry);
        return VOS_ERROR;
    }

    VOS_RawListInsert(list, it, &entry->rawNode);

    return VOS_OK;
}

inline void VOS_ListDeinit(VosList *list)
{
    if (VOS_ListEmpty(list)) {
        return;
    }

    for (VosListIterator it = VOS_ListIterBegin(list); it != VOS_ListIterEnd(list); it = VOS_ListIterErase(list, it)) {}

    list->dataFunc.dupFunc = NULL;
    list->dataFunc.freeFunc = NULL;
}

#ifdef __cplusplus
}
#endif

#endif /* VOS_LIST_PRIVATE_H */
