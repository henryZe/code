#include "stdbool.h"
#include "stdio.h"
#include "string.h"

struct Trie {
    int ch[26];
    bool isEnd;
} trie[10001];

int size;
char** ans[1001];
int ansSize[1001];




char ** wordBreak(char * s, char ** wordDict, int wordDictSize, int* returnSize)
{
    memset(ans, 0, sizeof(ans));
    size = 0;
    memset(trie[0].ch, 0, sizeof(trie[0].ch));
    trie[0].isEnd = false;

    for (int i = 0; i < wordDictSize; i++) {
        insert(wordDict[i], strlen(wordDict[i]));
    }

    backtrack(s, strlen(s), 0);
    *returnSize = ansSize[0];
    return ans[0];
}






