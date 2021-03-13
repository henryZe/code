#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// 链地址法, base 为质数
#define base 769

struct List {
    int val;
    struct List *next;
};

typedef struct {
    struct List *data;
} MyHashSet;

int hash(int key)
{
    return key % base;
}

bool listContains(struct List *head, int key)
{
    for (struct List *it = head; it->next; it = it->next) {
        // printf("it->val = %d key = %d\n", it->val, key);
        if (it->next->val == key)
            return true;
    }
    return false;
}

void listPush(struct List *head, int key)
{
    struct List *tmp = malloc(sizeof(struct List));
    tmp->val = key;
    tmp->next = head->next;
    head->next = tmp;
}

void listDelete(struct List *head, int key)
{
    struct List *tmp;

    for (struct List *it = head; it->next; it = it->next) {
        if (it->next->val == key) {
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

MyHashSet* myHashSetCreate(void)
{
    MyHashSet *ret = malloc(sizeof(MyHashSet));
    
    ret->data = malloc(sizeof(struct List) * base);
    for (int i = 0; i < base; i++) {
        ret->data[i].val = 0;
        ret->data[i].next = NULL;
    }

    return ret;
}

void myHashSetAdd(MyHashSet* obj, int key)
{
    int h = hash(key);
    if (!listContains(&(obj->data[h]), key))
        listPush(&(obj->data[h]), key);
}

void myHashSetRemove(MyHashSet* obj, int key)
{
    int h = hash(key);
    listDelete(&(obj->data[h]), key);
}

/** Returns true if this set contains the specified element */
bool myHashSetContains(MyHashSet* obj, int key)
{
    int h = hash(key);
    return listContains(&(obj->data[h]), key);
}

void myHashSetFree(MyHashSet* obj)
{
    for (int i = 0; i < base; i++)
        listFree(&(obj->data[i]));

    free(obj->data);
    free(obj);
}

int main(void)
{
    MyHashSet* obj = myHashSetCreate();

    myHashSetAdd(obj, 1);
    myHashSetAdd(obj, 2);
    printf("contain %d ? %s\n", 1, myHashSetContains(obj, 1) ? "True" : "False");
    printf("contain %d ? %s\n", 3, myHashSetContains(obj, 3) ? "True" : "False");
    
    myHashSetAdd(obj, 2);
    printf("contain %d ? %s\n", 2, myHashSetContains(obj, 2) ? "True" : "False");
    myHashSetRemove(obj, 2);
    printf("contain %d ? %s\n", 2, myHashSetContains(obj, 2) ? "True" : "False");

    myHashSetFree(obj);
    return 0;
}
