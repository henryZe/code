#include <string.h>
#include <stdbool.h>

char * longestPalindrome(char * s)
{
    int i, j, k;
    int len = strlen(s);

    if (len < 2)
        return s;

    int max_len = 1;
    int max_idx = 0;

    for (i = 0; i < len; i++) {
        for (j = i + max_len; j < len; j++) {
            bool chk = true;
            int cur_len = j - i + 1;

            for (k = 0; k < cur_len / 2; k++) {
                if (s[i + k] != s[j - k]) {
                    chk = false;
                    break;
                }
            }

            if (chk && cur_len > max_len) {
                max_idx = i;
                max_len = cur_len;
                // printf("i %d len %d\n", i, cur_len);
            }
        }
    }

    char *res = malloc(max_len + 1);
    memcpy(res, s + max_idx, max_len);
    res[max_len] = 0;

    return res;
}
