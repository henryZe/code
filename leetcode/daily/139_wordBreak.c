#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))

#define BRANCH 26
#define BASE 'a'

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

struct trie *create_tries(char ** wordDict, int wordDictSize)
{
    struct trie *ret = trieCreate();

    for (int i = 0; i < wordDictSize; i++) {
        trieInsert(ret, wordDict[i]);
    }
    return ret;
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

bool wordBreak(char * s, char ** wordDict, int wordDictSize)
{
    int n = strlen(s);
    struct trie *dict = create_tries(wordDict, wordDictSize);

    bool *dp = (bool *)malloc((n + 1) * sizeof(bool));
    for (int i = 1; i < n + 1; i++)
        dp[i] = false;
    dp[0] = true;

    char *str_cp = (char *)malloc(n + 1);

    for (int right = 1; right <= n; right++) {
        for (int left = 0; left < right; left++) {

            memcpy(str_cp, s + left, right - left);
            str_cp[right - left] = 0;

            if (dp[left] && trieSearch(dict, str_cp)) {
                dp[right] = true;
                break;
            }
            // printf("j = %d %s dp[%d] = %s\n",
            //         j, str_cp, i, dp[i] ? "true" : "false");
        }
    }

    return dp[n];
}

int main(void)
{
    char *wordDict0 = "apple";
    char *wordDict1 = "pen";
    char *wordDict[] = {wordDict0, wordDict1};
    char *s = "applepenapple";

    bool res = wordBreak(s, wordDict, ARRAYSIZE(wordDict));
    printf("%s\n", res ? "true" : "false");
    return 0;
}