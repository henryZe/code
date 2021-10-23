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
    for (int parent = 1, child = parent << 1; child <= h->size; parent = child, child <<= 1) {
        // there is right child or not
        if (child < h->size) {
            // choose smaller one
            if (d[child] > d[child + 1]) {
                child++;
            }
        }

        // stop search
        if (d[child] >= d[parent]) {
            break;
        }

        swap(d + child, d + parent);
    }

    return min;
}

struct heap *create_min_heap(int num)
{
    struct heap *h = malloc(sizeof(struct heap));

    h->weight = malloc(sizeof(int) * (num + 1));
    h->capacity = num;
    h->size = 0;

    h->weight[0] = INT_MIN;
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
    char *char_index = malloc(sizeof(char) * num);
    int frqs[128];

    for (int i = 0; i < num; i++) {
        scanf("%c %d ", &c, &frq);
        char_index[i] = c;
        frqs[c] = frq;
    }

    // create min heap
    struct heap *min_heap = create_min_heap(num);
    for (int i = 0; i < num; i++) {
        min_heap_push(min_heap, frqs[char_index[i]]);
    }

    // calculate optimal wpl
    int wpl_min = create_huffman_tree(min_heap);
    // printf("wpl_min = %d\n", wpl_min);

    int cases;
    scanf("%d\n", &cases);

    char str[64];

    // initialize codes
    codes = malloc(sizeof(char *) * num);
    for (int i = 0; i < num; i++) {
        codes[i] = malloc(sizeof(str));
    }

    // initialize index array
    int *index = malloc(sizeof(int) * num);

    for (int i = 0; i < cases; i++) {

        // calculate case's wpl
        int wpl = 0;
        for (int j = 0; j < num; j++) {
            memset(str, 0, sizeof(str));
            scanf("%c %s \n", &c, str);
            memcpy(codes[j], str, sizeof(str));

            // printf("%s len = %ld\n", codes[j], strlen(codes[j]));
            wpl += strlen(codes[j]) * frqs[c];
        }
        // printf("wpl = %d\n", wpl);
        if (wpl_min != wpl) {
            printf("No\n");
            continue;
        }

        bool res = false;
        // initialize index array
        for (int j = 0; j < num; j++) {
            index[j] = j;
        }
        // sort index array by codes' length
        qsort(index, num, sizeof(int), compare_strlen);

        // judge prefix code by trie tree
        struct trie *obj = trieCreate();
        for (int j = 0; j < num; j++) {
            // printf("%ld %s\n", strlen(codes[index[j]]), codes[index[j]]);
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
