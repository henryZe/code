#include <stdlib.h>
#include <stdio.h>

struct node {
    int key;
    int value;
    struct node *prev;
    struct node *next;
};

struct cache_info {
    struct node cache;
    int capacity;
    int size;
};

struct node *list_insert_head(struct node *head, struct node *n)
{
    n->prev = head->prev;
    n->next = head;
    head->prev->next = n;
    head->prev = n;

    // return new head pointer
    return n;
}

struct node *list_del(struct node *n)
{
    n->prev->next = n->next;
    n->next->prev = n->prev;

    // return delete pointer
    return n;
}

struct node *list_del_tail(struct node *head)
{
    struct node *tail = head->prev;
    list_del(tail);
    // return delete pointer
    return tail;
}

void put(struct cache_info *cache, int key, int value)
{
    int isExist = 0;
    struct node *n = cache->cache;

    for (int i = 0; i < cache->size; i++) {
        if (n->key == key) {
            // match
            isExist = 1;
            break;
        }
        n = n->next;
    }

    if (!isExist) {
        n = list_del_tail(cache->cache);
        if (cache->size < cache->capacity) {
            cache->size++;
        }
    } else {
        list_del(n);
    }

    n->key = key;
    n->value = value;
    cache->cache = list_insert_head(cache->cache, n);
}

int get(struct cache_info *cache, int key)
{
    int value = -1;
    struct node *n = cache->cache;

    for (int i = 0; i < cache->size; i++) {
        if (n->key == key) {
            // match
            value = n->value;
            n = list_del(n);
            cache->cache = list_insert_head(cache->cache, n);
            break;
        }
        n = n->next;
    }

    return value;
}

/**
 * lru design
 * @param operators int整型二维数组 the ops
 * @param operatorsRowLen int operators数组行数
 * @param operatorsColLen int* operators数组列数
 * @param k int整型 the k
 * @return int整型一维数组
 * @return int* returnSize 返回数组行数
 */
int* LRU(int** operators, int operatorsRowLen, int* operatorsColLen, int k, int* returnSize )
{
    int *curRow;
    int *retArr = (int *)malloc(operatorsRowLen * sizeof(int));
    struct node *freeNode = (struct node *)malloc(k * sizeof(struct node));
    struct node *cache;
    struct cache_info info;

    cache = freeNode;
    cache->next = cache->prev = cache;
    for (int i = 1; i < k; i++) {
        cache = list_insert_head(cache, freeNode + i);
    }

    info.cache = cache;
    info.capacity = k;
    info.size = 0;

    *returnSize = 0;
    for (int i = 0; i < operatorsRowLen; i++) {
        curRow = operators[i];
        if (curRow[0] == 1) {
            // put
            put(&info, curRow[1], curRow[2]);
        } else {
            // get
            retArr[*returnSize++] = get(&info, curRow[1]);
        }
    }

    return retArr;
}

int main(void)
{
    return 0;
}