#include "stdio.h"
#include "string.h"
#include "math.h"

int main(void)
{
    char s[500000];
    int size;

    while (scanf("%s", s) != EOF) {
        
        int origin_size = strlen(s);

        sprintf(s, "%s%s", s, s);
        size = strlen(s);


        int dp[size + 1][3];
        memset(dp, 0, sizeof(int) * (size) * 3);

        for (int i = 1; i < size; i++) {
            if (s[i] != 'o') {
                dp[i][0] = dp[i-1][0] + 1;
                dp[i][1] = dp[i-1][1] + 1;
                dp[i][2] = dp[i-1][2] + 1;
            } else {
                dp[i][0] = 0;
                dp[i][1] = dp[i-1][0] + 1;
                dp[i][2] = dp[i-1][1] + 1;
            }
        }

        int max = dp[0][2];
        for (int i = 1; i < size; i++) {
            max = fmax(dp[i][2], max);
        }

        printf("%d\n", (origin_size > max ? max : origin_size));
        memset(s, 0, sizeof(s));
    }

    return 0;
}