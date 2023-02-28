int delta(char c1, char c2)
{
    if (c1 > c2)
        return c1 - c2;
    return c2 - c1;
}

int equalSubstring(char * s, char * t, int maxCost)
{
    int i, start, end;
    int len = strlen(s);
    int *array = malloc(sizeof(int) * len);
    int res = 0;

    for (i = 0; i < len; i++) {
        array[i] = delta(s[i], t[i]);
        // printf("%d ", array[i]);
    }

    // O(n)
    int cur_cost = 0;

    start = end = 0;
    while (end < len) {
        cur_cost += array[end];

        while (cur_cost > maxCost) {
            cur_cost -= array[start];
            start++;
        }

        int cur = end - start + 1;
        res = cur > res ? cur : res;
        end++;
    }

    return res;
}
