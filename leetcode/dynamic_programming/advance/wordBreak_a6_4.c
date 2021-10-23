#include "stdbool.h"
#include "stdio.h"
#include "string.h"

unsigned long long Hash(char* s, int begin, int end) {
    unsigned long long value = 0;
    int i;

    for (i = begin; i < end; i++) {
        value = value * 2333ULL;
        value += s[i] - 'a' + 1;
    }
    return value;
}

bool query(unsigned long long* dict, int len_dict, unsigned long long x)
{
    int i;
    for (i = 0; i < len_dict; i++) {
        if (dict[i] == x) {
            return true;
        }
    }
    return false;
}

bool wordBreak(char * s, char ** wordDict, int wordDictSize)
{
    int i, j;
    int len_s = strlen(s);

    if (!wordDictSize)
        return false;

    unsigned long long dict[wordDictSize];
    for (i = 0; i < wordDictSize; i++) {
        dict[i] = Hash(wordDict[i], 0, strlen(wordDict[i]));
    }

    bool dp[len_s + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = true;

    for (i = 1; i < len_s + 1; i++) {
        for (j = 0; j < i; j++) {
            if (dp[j] && query(dict, wordDictSize, Hash(s, j, i))) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[len_s];
}

int main(void)
{
    char *s = "applepenapple";
    char *wordDict[2] = {"apple", "pen"};
    
    printf("%d\n", wordBreak(s, wordDict, 2));
    return 0;
}
