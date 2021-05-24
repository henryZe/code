#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_LEN 1000001
#define MAX_PATTERN_LEN 100001

void BuildMatch(char *pattern, int *match)
{
    int i, j;
    int m = strlen(pattern);

    match[0] = -1;
    for (j = 1; j < m; j++) {
        i = match[j - 1];
        while ((i >= 0) && (pattern[i + 1] != pattern[j]))
            // turn back
            i = match[i];
        if (pattern[i + 1] == pattern[j])
            // fit!
            match[j] = i + 1;
        else
            // not fits any more
            match[j] = -1;
    }
}

char *KMP(char *string, char *pattern)
{
    int n = strlen(string);
    int m = strlen(pattern);
    int s, p, *match;

    if (n < m)
        return NULL;

    match = (int *)malloc(sizeof(int) * m);

    BuildMatch(pattern, match);

    s = p = 0;
    while (s < n && p < m) {
        if (string[s] == pattern[p]) {
            s++;
            p++;
        } else if (p > 0) {
            // turn back
            p = match[p - 1] + 1;
        } else {
            // no fits any more
            s++;
        }
    }

    return (p == m) ? string + (s - m) : NULL;
}

char string[MAX_STRING_LEN] = {0};
char pattern[MAX_PATTERN_LEN] = {0};

int main(void)
{
    scanf("%s\n", string);

    int num;
    scanf("%d\n", &num);

    for (int i = 0; i < num; i++) {
        scanf("%s\n", pattern);
        // char *p = strstr(string, pattern);
        char *p = KMP(string, pattern);

        if (!p)
            printf("Not Found\n");
        else
            printf("%s\n", p);
    }

    return 0;
}