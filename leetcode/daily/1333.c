enum {
    ID,
    RATING,
    VEGAN,
    PRICE,
    DISTANCE,
};

int **r;

int compare(const void *a1, const void *a2)
{
    int a = *(int *)a1;
    int b = *(int *)a2;

    if (r[a][RATING] == r[b][RATING])
        return r[b][ID] - r[a][ID];

    return r[b][RATING] - r[a][RATING];
}

int filter(int *idx, int **restaurants, int restaurantsSize,
           int veganFriendly, int maxPrice, int maxDistance)
{
    int len = 0;

    for (int i = 0; i < restaurantsSize; i++) {
        if (veganFriendly && restaurants[i][VEGAN] == 0)
            continue;

        if (restaurants[i][PRICE] > maxPrice)
            continue;

        if (restaurants[i][DISTANCE] > maxDistance)
            continue;

        idx[len++] = i;
    }

    return len;
}

int* filterRestaurants(int** restaurants, int restaurantsSize, int* restaurantsColSize,
                       int veganFriendly, int maxPrice, int maxDistance,
                       int* returnSize)
{
    int index[restaurantsSize];
    int res_len = filter(index, restaurants, restaurantsSize,
                         veganFriendly, maxPrice, maxDistance);

    r = restaurants;
    qsort(index, res_len, sizeof(int), compare);

    int *res = malloc(sizeof(int) * res_len);
    for (int i = 0; i < res_len; i++)
        res[i] = restaurants[index[i]][0];

    *returnSize = res_len;
    return res;
}
