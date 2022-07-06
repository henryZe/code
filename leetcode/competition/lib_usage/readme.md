# CSTL 编程心得

## 1 hash

IntHash 常用函数：
~~~ C
VosHash *VOS_IntHashCreate(size_t bktSize);                                 // return VosHash *hash
uint32_t VOS_IntHashInsert(VosHash *hash, int key, uintptr_t value);        // return VOS_OK

VosHashIterator VOS_IntHashFind(VosHash *hash, int key);
VosHashIterator VOS_HashIterBegin(const VosHash *hash);
VosHashIterator VOS_HashIterEnd(const VosHash *hash);
VosHashIterator VOS_HashIterNext(const VosHash *hash, VosHashIterator it);
VosHashIterator VOS_IntHashErase(VosHash *hash, int key);

uintptr_t VOS_HashIterKey(const VosHash *hash, VosHashIterator it);
uintptr_t VOS_HashIterValue(const VosHash *hash, VosHashIterator it);

uint32_t VOS_HashAt(const VosHash *hash, uintptr_t key, uintptr_t *value);  // return VOS_OK
uint32_t VOS_HashPut(VosHash *hash, uintptr_t key, uintptr_t value);        // return VOS_OK

size_t VOS_HashSize(const VosHash *hash);

void VOS_HashClear(VosHash *hash);
void VOS_HashDestroy(VosHash *hash);
~~~

StrHash 常用函数：
~~~ C
VOS_StrHashCreate
VOS_StrHashInsert

VOS_StrHashFind

VOS_StrHashErase
~~~

## 2 map

~~~ C
VosMap *VOS_MapCreate(VosKeyCmpFunc keyCmpFunc, VosDupFreeFuncPair *keyFunc, VosDupFreeFuncPair *valueFunc);

bool VOS_MapEmpty(const VosMap *map);
size_t VOS_MapSize(const VosMap *map);

uint32_t VOS_MapInsert(VosMap *map, uintptr_t key, uintptr_t value);

VosMapIterator VOS_MapFind(const VosMap *map, uintptr_t key);
VosMapIterator VOS_MapIterEnd(const VosMap *map);
VosMapIterator VOS_MapIterNext(const VosMap *map, VosMapIterator it);

uintptr_t VOS_MapIterKey(const VosMap *map, VosMapIterator it);
uintptr_t VOS_MapIterValue(const VosMap *map, VosMapIterator it);

uint32_t VOS_MapAt(const VosMap *map, uintptr_t key, uintptr_t *value);
uint32_t VOS_MapPut(VosMap *map, uintptr_t key, uintptr_t value);

void VOS_MapDestroy(VosMap *map);
~~~

其中，`VOS_MapCreate`参数为：
~~~ C
VosDupFreeFuncPair keyFunc = {StrKeyDupFunc, free};
VosDupFreeFuncPair dataFunc = {dataDupFunc, free};
VosMap *map = VOS_MapCreate(VOS_StrCmpFunc, &keyFunc, &dataFunc);

void *dataDupFunc(void *src)
{
    UserData *tmpSrc = (UserData *)src;
    UserData *data = (UserData *)malloc(sizeof(UserData));
    memcpy(data, tmpSrc, sizeof(UserData));
    return data;
}
~~~

## 3 priority queue

~~~ C
VOS_PriQueCreate

VOS_PriQueEmpty
VOS_PriQueSize

VOS_PriQuePush
VOS_PriQueTop
VOS_PriQuePop

VOS_PriQuePushBatch

VOS_PriQueDestroy
~~~

其中，小顶堆：
~~~ C
VosPriQue *priQueue = VOS_PriQueCreate(cmpFunc2, NULL);
int32_t cmpFunc2(uintptr_t data1, uintptr_t data2)
{
    return (int32_t)(data2 - data1);
}
~~~

大顶堆则为，
~~~ C
VosPriQue *priQueue = VOS_PriQueCreate(VOS_IntCmpFunc, NULL);
~~~

## 4 queue

~~~ C
VOS_QueueCreate
VOS_QueueDestroy

VOS_QueueEmpty
VOS_QueueSize

VOS_QueuePush
VOS_QueuePop

VOS_QueueFront
VOS_QueueBack
~~~

## 5 set

~~~ C
VOS_SetCreate
VOS_SetInsert

VOS_SetEmpty
VOS_SetSize

VOS_SetErase

VOS_SetFind
VOS_SetIterBegin
VOS_SetIterEnd
VOS_SetIterNext

VOS_SetIterKey

VOS_SetClear
VOS_SetDestroy
~~~

## 6 list

~~~ C
VOS_ListInit

VOS_ListPushBack
VOS_ListPushFront

VOS_ListPopFront
VOS_ListPopBack

VOS_ListIterBegin
VOS_ListIterEnd
VOS_ListIterNext
VOS_ListIterData

VOS_ListIterErase

VOS_ListDeinit
~~~

## 7 stack

~~~ C
VOS_StackCreate

VOS_StackEmpty
VOS_StackSize

VOS_StackPush
VOS_StackPop
VOS_StackTop

VOS_StackClear
VOS_StackDestroy
~~~

## 8 vector

~~~ C
VOS_VectorCreate
VOS_VectorDestroy

VOS_VectorSize

VOS_VectorSort

VOS_VectorSearch
VOS_VectorAt

VOS_VectorPushBack
VOS_VectorErase
~~~

## 9 C standard lib

### 9.1 qsort

### 9.2 bsearch

### 9.3 strtok

### 9.4 regex
