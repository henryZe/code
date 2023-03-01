int lengthOfLongestSubstringTwoDistinct(char * s)
{
    int start = 0, end = 0;
    int res = 0;
    int len = strlen(s);
    int table[256];
    int i;
    int cur_diff = 0;
    int next_start;

    for (i = 0; i < 256; i++)
        table[i] = -1;

    while (end < len) {
        if (table[s[end]] == -1) {
            cur_diff++;
        }
        table[s[end]] = end;

        while (cur_diff > 2) {
            if (start == table[s[start]]) {
                cur_diff--;
                table[s[start]] = -1;
            }
            start++;
        }

        end++;
        res = (end - start) > res ? end - start : res;
    }

    return res;
}
