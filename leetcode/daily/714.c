#include <math.h>

int maxProfit(int* prices, int pricesSize, int fee)
{
    int i;
    int state[] = { -prices[0], 0 };

    for (i = 1; i < pricesSize; i++) {
        state[0] = fmax(state[0], state[1] - prices[i]);
        state[1] = fmax(state[1], state[0] + prices[i] - fee);
        // printf("day %d: %d %d\n", i, state[0], state[1]);
    }

    return state[1];
}
