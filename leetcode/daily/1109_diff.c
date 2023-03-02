// O(N)
int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize,
                        int n, int* returnSize)
{
    int i, j;
    int *diff = malloc(sizeof(int) * n);

    for (i = 0; i < n; i++) {
        diff[i] = 0;
    }

    for (i = 0; i < bookingsSize; i++) {
        int seats = bookings[i][2];
        int left = bookings[i][0] - 1;
        int right = bookings[i][1];

        diff[left] += seats;
        if (right < n)
            diff[right] -= seats;
    }

    for (i = 1; i < n; i++) {
        diff[i] += diff[i - 1];
    }

    *returnSize = n;
    return diff;
}
