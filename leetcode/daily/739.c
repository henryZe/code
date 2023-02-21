/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize)
{
    int i;
    int *res = malloc(sizeof(int) * temperaturesSize);
    for (i = 0; i < temperaturesSize; i++) {
        res[i] = 0;
    }

    int stk_size = 0;
    int *stk = malloc(sizeof(int) * 2 * temperaturesSize);

    for (i = 0; i < temperaturesSize; i++) {
        while (stk_size != 0 && temperatures[stk[stk_size - 1]] < temperatures[i]) {
            res[stk[stk_size - 1]] = i - stk[stk_size - 1];
            stk_size--;
        }

        stk_size++;
        stk[stk_size - 1] = i;
    }

    *returnSize = temperaturesSize;
    return res;
}
