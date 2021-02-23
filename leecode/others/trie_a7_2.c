#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#define R 26

typedef struct trie {
    bool isEnd;
    struct trie *child[R];
} Trie;

/** Initialize your data structure here. */

Trie* trieCreate(void) 
{
    Trie *p = (void *)malloc(sizeof(Trie));
    p->isEnd = false;
    memset(p->child, 0, R * sizeof(Trie *));

    return p;
}

/** Inserts a word into the trie. */
void trieInsert(Trie* obj, char * word)
{
    Trie *p = obj;
    int i;
    int len = strlen(word);

    for (i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (!p->child[index]) {
            Trie *node = trieCreate();
            p->child[index] = node;
        }
        p = p->child[index];
    }
    p->isEnd = true;
}

Trie *searchPrefix(Trie* obj, char *word)
{
    Trie *p = obj;
    int i;
    int len = strlen(word);

    for (i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (p->child[index]) {
            p = p->child[index];
        } else {
            return NULL;
        }
    }
    return p;
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie* obj, char * word)
{
    Trie *p = searchPrefix(obj, word);
    return p && p->isEnd;
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie* obj, char * prefix)
{
    Trie *p = searchPrefix(obj, prefix);
    return p != NULL;
}

void trieFree(Trie* obj)
{
    if (!obj)
        return;

    for (int i = 0; i < R; i++)
        trieFree(obj->child[i]);
    free(obj);
}

int main(void)
{
    Trie* obj = trieCreate();
    char *word = "helloworld";
    char *prefix = "hello";

    trieInsert(obj, word);
    bool param_2 = trieSearch(obj, word);
    bool param_3 = trieStartsWith(obj, prefix);
    trieFree(obj);

    printf("%d %d\n", param_2, param_3);
    return 0;
}
