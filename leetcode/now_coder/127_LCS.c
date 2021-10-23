#include "stdio.h"
#include "string.h"
#include "stdlib.h"

/**
 * longest common substring
 * @param str1 string字符串 the string
 * @param str2 string字符串 the string
 * @return string字符串
 */
char* LCS(char* str1, char* str2 )
{
    int m = strlen(str1);
    int n = strlen(str2);
    int dp[m+1][n+1];
    int i, j;
    int maxlen = 0;
    int end = 0;

    if ((m == 0) || (n == 0)) {
        return (char *)"-1";
    }

    for (i = 0; i < m + 1; i++) { dp[i][0] = 0; }
    for (j = 0; j < n + 1; j++) { dp[0][j] = 0; }

    for (i = 1; i < m + 1; i++) {
        for (j = 1; j < n + 1; j++) {
            if (str1[i-1] == str2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = 0;
            }

            if (dp[i][j] > maxlen) {
                maxlen = dp[i][j];
                end = j;
            }
        }
    }
    
    if (maxlen == 0) {
        return (char *)"-1";
    }

    char *str = (char *)malloc(maxlen + 1);
    memset(str, 0, maxlen + 1);
    memcpy(str, str2 + end - maxlen, maxlen);

    return str;
}

int main(void)
{
    char *str = LCS("1AB2345CD12345EF", "12345EF");
    printf("%s\n", str);
    return 0;
}
