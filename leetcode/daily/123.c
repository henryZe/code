int compare(const void *a, const void *b)
{
    int arg1 = *(int *)a, arg2 = *(int *)b;
    return arg2 - arg1;
}

#include <math.h>

int maxProfit(int* prices, int pricesSize)
{
    int i;
    int buy1, buy2;
    int sell1, sell2;

    // because no buy is max benefit, so exclude it
    buy1 = buy2 = -prices[0];
    sell1 = sell2 = 0;

    for (i = 1; i < pricesSize; i++) {
        buy1 = fmax(buy1, 0 - prices[i]);
        sell1 = fmax(sell1, buy1 + prices[i]);
        buy2 = fmax(buy2, sell1 - prices[i]);
        sell2 = fmax(sell2, buy2 + prices[i]);
    }

    return sell2;
}
