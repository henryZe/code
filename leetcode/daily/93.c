#include <stdbool.h>
#include <string.h>

#define debug printf
// #define debug(...)

char **res;
int res_len;

bool judge(char *number, int s_len, int start_pos, int length)
{
    char tmp[4] = {};

    if ((start_pos + length) > s_len)
        return false;

    memcpy(tmp, number + start_pos, length);

    if (tmp[0] == '0' && length > 1)
        return false;

    if (atoi(tmp) > 255)
        return false;

    return true;
}

void dfs(char *s, int s_len, int start_pos, int idx, char *cur, int cur_len)
{
    if (idx == 4) {
        if (cur_len - 4 != strlen(s))
            return;

        // reset '.' as end_of_string
        cur[cur_len - 1] = 0;
        sprintf(res[res_len], "%s", cur);
        debug("catch %s\n", res[res_len]);

        res_len++;
        return;
    }

    for (int i = 1; i < 4; i++) {
        if (judge(s, s_len, start_pos, i) == false)
            continue;

        memcpy(cur + cur_len, s + start_pos, i);
        cur[cur_len + i] = '.';

        cur[cur_len + i + 1] = 0;
        debug("cur %s cur_len %d i %d\n", cur, cur_len + i + 1, i);

        dfs(s, s_len, start_pos + i, idx + 1, cur, cur_len + i + 1);
        debug(".");
    }
    debug("!");
}

char ** restoreIpAddresses(char * s, int* returnSize)
{
    int i;

    res = malloc(sizeof(char *) * 81);
    for (i = 0; i < 81; i++) {
        res[i] = malloc(16);
    }

    char cur[20] = {};

    res_len = 0;
    dfs(s, strlen(s), 0, 0, cur, 0);

    debug("return %d\n", res_len);

    *returnSize = res_len;
    return res;
}
