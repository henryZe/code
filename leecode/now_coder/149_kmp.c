#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int kmp(char *pattern, char *string)
{
    int n = strlen(string);
    int m = strlen(pattern);
    int s, p, *match;

    if (n < m)
        return 0;

    match = (int *)malloc(sizeof(int) * m);

    BuildMatch(pattern, match);

    int times = 0;
    s = p = 0;
    while (1) {
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

        if (s == n) {
            // check end
            break;
        }

        if (p == m) {
            // match!
            times++;
            p = match[p - 1] + 1;
        }
    }

    return times;
}

int main(void)
{
    printf("%d\n", kmp("ababab", "abababab"));
    return 0;
}
