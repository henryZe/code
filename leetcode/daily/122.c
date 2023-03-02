int maxProfit(int* prices, int pricesSize)
{
    // int *diff = malloc(sizeof(int) * pricesSize);
    int sum = 0;

    for (int i = 1; i < pricesSize; i++) {
        int diff = prices[i] - prices[i - 1];
        if (diff > 0)
            sum += diff;
    }

    return sum;
}
