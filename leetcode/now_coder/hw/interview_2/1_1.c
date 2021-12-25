#include <stdbool.h>

char *longestP(char *str)
{
    int n = strlen(str);
    int max_len = 1;
    int new = 0;
    int start, end;
    bool res;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (str[i] == str[j]) {
                start = i;
                end = j;
                res = true;

                while (start < end) {
                    start++;
                    end--;
                    if (str[start] != str[end]) {
                        res = false;
                        break;
                    }
                }

                if (res) {
                    int len = j - i + 1;
                    if (max_len < len) {
                        max_len = len;
                        new = i;
                    }
                }
            }
        }
    }

    char *new_str = malloc(max_len + 1);
    memcpy(new_str, str + new, max_len);
    new_str[max_len] = 0;

    return new_str;
}