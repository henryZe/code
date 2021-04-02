#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct heap {
    int *weight;
    int capacity;
    int size;
};

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

bool IsFull(struct heap *h)
{
    return h->capacity == h->size;
}

bool IsEmpty(struct heap *h)
{
    return h->size == 0;
}

int min_heap_push(struct heap *h, int x)
{
    int *d = h->weight;

    if (IsFull(h))
        return -1;

    d[++(h->size)] = x;

    for (int i = h->size; d[i] < d[i >> 1]; i >>= 1) {
        swap(&d[i], &d[i >> 1]);
    }

    return 0;
}

int min_heap_pop(struct heap *h)
{
    int *d = h->weight;
    int min = d[1];

    if (IsEmpty(h)) {
        return -1;
    }

    d[1] = d[h->size--];

    int parent, child;
    for (parent = 1, child = parent << 1; child <= h->size; parent = child) {
        if (child < h->size) {
            if (d[child] > d[child + 1]) {
                child++;
            }
        }

        if (d[child] >= d[parent]) {
            break;
        } 

        swap(d + child, d + parent);
        child <<= 1;
    }

    return min;
}

struct heap *create_min_heap(int *nums, int num)
{
    struct heap *h = malloc(sizeof(struct heap));

    h->weight = malloc(sizeof(int) * (num + 1));
    h->capacity = num;
    h->size = 0;

    h->weight[0] = INT_MIN;
    for (int i = 0; i < num; i++) {
        min_heap_push(h, nums[i]);
    }

    return h;
}

int create_huffman_tree(struct heap *h)
{
    int wpl = 0;
    int val1, val2;

    while (h->size > 1) {
        val1 = min_heap_pop(h);
        val2 = min_heap_pop(h);
        val1 += val2;
        min_heap_push(h, val1);
        wpl += val1;
    }

    return wpl;
}

char **codes = NULL;
int compare_strlen(const void *a, const void *b)
{
    int len1 = strlen(codes[*(int *)a]);
    int len2 = strlen(codes[*(int *)b]);

    if (len1 == len2)
        return 0;

    return len1 < len2 ? 1 : -1;
}

#define BRANCH 2
#define BASE '0'
struct trie {
    bool isEnd;
    struct trie *child[BRANCH];
};

struct trie *trieCreate(void) 
{
    struct trie *p = malloc(sizeof(struct trie));
    p->isEnd = false;
    memset(p->child, 0, BRANCH * sizeof(struct trie *));

    return p;
}

/** Inserts a word into the trie. */
void trieInsert(struct trie *obj, char *word)
{
    int i;
    int len = strlen(word);
    struct trie *p = obj;

    for (i = 0; i < len; i++) {
        int index = word[i] - BASE;
        if (!p->child[index]) {
            struct trie *node = trieCreate();
            p->child[index] = node;
        }
        p = p->child[index];
    }
    p->isEnd = true;
}

struct trie *searchPrefix(struct trie *obj, char *word)
{
    struct trie *p = obj;
    int i;
    int len = strlen(word);

    for (i = 0; i < len; i++) {
        int index = word[i] - BASE;
        if (p->child[index]) {
            p = p->child[index];
        } else {
            return NULL;
        }
    }
    return p;
}

/** Returns if the word is in the trie. */
bool trieSearch(struct trie *obj, char *word)
{
    struct trie *p = searchPrefix(obj, word);
    return p && p->isEnd;
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(struct trie *obj, char *prefix)
{
    struct trie *p = searchPrefix(obj, prefix);
    return p != NULL;
}

void trieFree(struct trie *obj)
{
    if (!obj)
        return;

    for (int i = 0; i < BRANCH; i++)
        trieFree(obj->child[i]);
    free(obj);
}

/*
 * min heap -> huffman tree -> sum of push values -> optimal WPL
 * 
 * whether is the optimal code:
 * 1. WPL (length of each code * frequency) = min WPL
 * 2. exist prefix code or not (by trie tree)
 */
int main(void)
{
    int num;
    scanf("%d\n", &num);

    char c;
    int frq;
    int *frqs = malloc(sizeof(int) * num);

    for (int i = 0; i < num; i++) {
        scanf("%c %d ", &c, &frq);
        frqs[i] = frq;
    }

    struct heap *min_heap = create_min_heap(frqs, num);

    int wpl_min = create_huffman_tree(min_heap);
    // printf("wpl_min = %d\n", wpl_min);

    int cases;
    scanf("%d\n", &cases);

    char str[64];

    int *index = malloc(sizeof(int) * num);
    codes = malloc(sizeof(char *) * num);
    for (int i = 0; i < num; i++) {
        codes[i] = malloc(sizeof(str));
        memset(codes[i], 0, sizeof(str));
    }

    for (int i = 0; i < cases; i++) {

        for (int j = 0; j < num; j++) {
            memset(str, 0, sizeof(str));
            scanf("%c %s \n", &c, str);
            strcpy(codes[j], str);
            index[j] = j;
        }

        int wpl = 0;
        for (int j = 0; j < num; j++) {
            wpl += strlen(codes[j]) * frqs[j];
        }
        // printf("wpl = %d\n", wpl);
        if (wpl_min != wpl) {
            printf("No\n");
            continue;
        }

        bool res;
        qsort(index, num, sizeof(int), compare_strlen);

        struct trie *obj = trieCreate();
        for (int j = 0; j < num; j++) {
            res = trieStartsWith(obj, codes[index[j]]);
            if (res)
                break;
            trieInsert(obj, codes[index[j]]);
        }
        trieFree(obj);

        if (res)
            printf("No\n");
        else
            printf("Yes\n");
    }

    return 0;
}
