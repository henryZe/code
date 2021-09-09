#include <string.h>
#include <stdio.h>

int getLongestPalindrome(char *A, int n)
{
    int dp[n][n];
    int maxlen = 1;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            dp[i][j] = 0;
        }
    }

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < j; i++) {
            if (A[i] == A[j]) {
                if (j - i + 1 > 3 && dp[i + 1][j - 1] == 0) {
                    continue;
                }
                dp[i][j] = 1;
                int curlen = j - i + 1;
                if (maxlen < curlen) {
                    maxlen = curlen;
                }
            }
        }
    }

    return maxlen;
}

int main(void)
{
    char *ref = "abc1234321ab";
    printf("%d\n", getLongestPalindrome(ref, strlen(ref)));
    return 0;
}
