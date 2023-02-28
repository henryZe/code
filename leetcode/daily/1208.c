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

    for (start = 0; start < len; start++) {
        int cur_cost = 0;

        for (end = start; end < len; end++) {
            cur_cost += array[end];
            // printf("cur_cost %d\n", cur_cost);

            if (cur_cost > maxCost)
                break;
        }

        i = end - start;
        res = i > res ? i : res;
    }

    return res;
}
