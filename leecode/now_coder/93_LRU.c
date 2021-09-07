#include <stdlib.h>
#include <stdio.h>

struct node {
    int key;
    int value;
    struct node *prev;
    struct node *next;
};

struct cache_info {
    struct node head;
    int capacity;
    int size;
};

void list_insert(struct node *head, struct node *n)
{
    struct node *next = head->next;

    n->prev = head;
    n->next = next;
    next->prev = n;
    head->next = n;
}

struct node *list_del(struct node *n)
{
    n->prev->next = n->next;
    n->next->prev = n->prev;

    // return delete pointer
    return n;
}

void print_cache(struct cache_info *cache)
{
    struct node *n = cache->head.next;

    for (int i = 0; i < cache->size; i++) {
        printf("key %d value %d\n", n->key, n->value);
        n = n->next;
    }
}

void print_ret(int size, int *array)
{
    int i;

    printf("[");
    for (i = 0; i < size - 1; i++) {
        printf("%d,", array[i]);
    }
    printf("%d]\n", array[i]);
}

void put(struct cache_info *cache, int key, int value)
{
    int isExist = 0;
    struct node *n = cache->head.next;

    for (int i = 0; i < cache->size; i++) {
        if (n->key == key) {
            // match
            isExist = 1;
            break;
        }
        n = n->next;
    }

    if (!isExist) {
        n = list_del(cache->head.prev);
        if (cache->size < cache->capacity) {
            cache->size++;
        }
    } else {
        n = list_del(n);
    }

    n->key = key;
    n->value = value;
    list_insert(&cache->head, n);
}

int get(struct cache_info *cache, int key)
{
    int value = -1;
    struct node *n = cache->head.next;

    for (int i = 0; i < cache->size; i++) {
        if (n->key == key) {
            // match
            value = n->value;
            n = list_del(n);
            list_insert(&cache->head, n);
            break;
        }
        n = n->next;
    }

    return value;
}

int* LRU(int** operators, int operatorsRowLen, int* operatorsColLen, int k, int* returnSize )
{
    int *curRow;
    int *retArr = (int *)malloc(operatorsRowLen * sizeof(int));
    struct node *freeNode = (struct node *)malloc(k * sizeof(struct node));
    struct cache_info info;

    info.head.prev = &info.head;
    info.head.next = &info.head;

    for (int i = 0; i < k; i++) {
        list_insert(&info.head, freeNode + i);
    }

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
            retArr[(*returnSize)++] = get(&info, curRow[1]);
            // print_ret(*returnSize, retArr);
        }
        // print_cache(&info);
    }

    return retArr;
}

int main(void)
{
    int op_num = 0;
    scanf("%d\n", &op_num);

    int **operators = malloc(op_num * sizeof(int *));
    int op, key, value;
    for (int i = 0; i < op_num; i++) {
        operators[i] = malloc(3 * sizeof(int));
        scanf("[%d,", &op);
        if (op == 1) {
            scanf("%d,%d],", &key, &value);
            operators[i][0] = op;
            operators[i][1] = key;
            operators[i][2] = value;
        } else {
            scanf("%d],", &key);
            operators[i][0] = op;
            operators[i][1] = key;
        }
    }

    int k = 0;
    scanf("%d\n", &k);

    int retSize;
    print_ret(retSize, LRU(operators, op_num, NULL, k, &retSize));

    return 0;
}
