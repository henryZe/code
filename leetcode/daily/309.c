#include <math.h>

int maxProfit(int* prices, int pricesSize)
{
    int i;
    int state[] = { -prices[0], 0, 0 };

    for (i = 1; i < pricesSize; i++) {
        // can not buy & sell & frozen on the same day
        int tmp0 = fmax(state[0], state[2] - prices[i]);
        int tmp1 = fmax(state[1], state[0] + prices[i]);
        int tmp2 = fmax(state[2], state[1]);
        state[0] = tmp0;
        state[1] = tmp1;
        state[2] = tmp2;
        // printf("day %d: %d %d %d\n", i, tmp0, tmp1, tmp2);
    }

    return fmax(state[1], state[2]);
}
