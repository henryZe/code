#include <stdio.h>
#include <stdlib.h>

#define base 769

struct List {
    int key;
    int item;
    struct List *next;
};

typedef struct {
    struct List *data;
} MyHashMap;

int hash(int key)
{
    return key % base;
}

struct List *listFind(struct List *head, int key)
{
    for (struct List *it = head; it->next; it = it->next) {
        if (it->next->key == key)
            return it->next;
    }
    return NULL;
}

void listPush(struct List *head, int key, int item)
{
    struct List *tmp = malloc(sizeof(struct List));
    tmp->key = key;
    tmp->item = item;
    tmp->next = head->next;
    head->next = tmp;
}

void listDelete(struct List *head, int key)
{
    struct List *tmp;

    for (struct List *it = head; it->next; it = it->next) {
        if (it->next->key == key) {
            tmp = it->next;
            it->next = tmp->next;
            free(tmp);
            break;
        }
    }
}

void listFree(struct List *head)
{
    struct List *tmp;

    while (head->next) {
        tmp = head->next;
        head->next = tmp->next;
        free(tmp);        
    }
}

MyHashMap* myHashMapCreate(void)
{
    MyHashMap *obj = malloc(sizeof(MyHashMap));

    obj->data = malloc(sizeof(struct List) * base);
    for (int i = 0; i < base; i++)
        obj->data[i].next = NULL;

    return obj;
}

/** value will always be non-negative. */
void myHashMapPut(MyHashMap* obj, int key, int value)
{
    int k = hash(key);
    struct List *node = listFind(&(obj->data[k]), key);

    if (node)
        node->item = value;
    else
        listPush(&(obj->data[k]), key, value);
}

/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
int myHashMapGet(MyHashMap* obj, int key)
{
    int k = hash(key);
    struct List *node = listFind(&(obj->data[k]), key);

    if (!node)
        return -1;

    return node->item;
}

/** Removes the mapping of the specified value key if this map contains a mapping for the key */
void myHashMapRemove(MyHashMap* obj, int key)
{
    int k = hash(key);
    listDelete(&(obj->data[k]), key);
}

void myHashMapFree(MyHashMap* obj)
{
    for (int i = 0; i < base; i++)
        listFree(&(obj->data[i]));

    free(obj->data);
    free(obj);
}

int main(void)
{
    MyHashMap* obj = myHashMapCreate();

    myHashMapPut(obj, 1, 1);
    myHashMapPut(obj, 2, 2);
    printf("get key: %d item: %d\n", 1, myHashMapGet(obj, 1));
    printf("get key: %d item: %d\n", 3, myHashMapGet(obj, 3));

    myHashMapPut(obj, 2, 1);
    printf("get key: %d item: %d\n", 2, myHashMapGet(obj, 2));

    myHashMapRemove(obj, 2);
    printf("get key: %d item: %d\n", 2, myHashMapGet(obj, 2));

    myHashMapFree(obj);
    return 0;
}
