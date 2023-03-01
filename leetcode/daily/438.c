int* findAnagrams(char * s, char * p, int* returnSize)
{
    int start = 0, end = 0;
    int i;
    int len_p = strlen(p);
    int len_s = strlen(s);
    int table[256] = {};
    int *res = malloc(sizeof(int) * len_s);
    int res_len = 0;

    // 1. generate p character table
    for (i = 0; i < len_p; i++) {
        table[p[i]]++;
    }

    while (1) {
        while (end < len_s && table[s[end]] == 0) {
            // 2. the char end pointing not meet
            if (start == end) {
                // no this char, skip it
                end++;
                start++;
                continue;
            }

            // move start pointer
            table[s[start]]++;
            start++;
        }

        if (end >= len_s)
            // s is over
            break;

        // 3. walk end pointer
        // if (table[s[end]] <= 0)
        //     printf("end = %d\n", end);
        table[s[end]]--;
        end++;

        // 4. if cur_len == len_p, mark the substring
        if ((end - start) == len_p) {
            res[res_len] = start;
            res_len++;
        }
    }

    *returnSize = res_len;
    return res;
}
