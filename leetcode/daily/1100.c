int numKLenSubstrNoRepeats(char * s, int k)
{
    int i;
    int res = 0;
    int len = strlen(s);
    int start = 0, end = 0;
    int table[256] = {};

    for (i = 0; i < 256; i++)
        table[i] = -1;

    while (end < len) {
        if (table[s[end]] != -1) {
            // clear table
            while (start <= table[s[end]]) {
                table[s[start]] = -1;
                start++;
            }
            // printf("move s: %d\n", start);
        }

        table[s[end]] = end;
        end++;
        if ((end - start) >= k) {
            // printf("s: %d e: %d\n", start, end);
            res++;
        }
    }

    return res;
}
