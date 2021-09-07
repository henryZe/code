
int maxsumofSubarray(int* arr, int arrLen )
{
    int dp[arrLen];

    dp[0] = arr[0];
    int max = dp[0];
    for (int i = 1; i < arrLen; i++) {
        if (dp[i - 1] < 0) {
            dp[i] = arr[i];
        } else {
            dp[i] = arr[i] + dp[i - 1];
        }
        max = max < dp[i] ? dp[i] : max;
    }

    return max;
}