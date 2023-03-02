// O(N^2)
int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize,
                        int n, int* returnSize)
{
    int i, j;
    int *res = malloc(sizeof(int) * n);

    for (i = 0; i < n; i++) {
        res[i] = 0;
    }

    for (i = 0; i < bookingsSize; i++) {
        for (j = bookings[i][0] - 1; j < bookings[i][1]; j++) {
            res[j] += bookings[i][2];
        }
    }

    *returnSize = n;
    return res;
}
