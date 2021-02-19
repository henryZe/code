class Solution:
    def maxsumofSubarray(self , arr ):
        dp = []
        maxSum = 0
        dp[0] = arr[0]
        for i in range(1, len(arr)):
            if arr[i] > 0:
                dp[i] = dp[i-1] + arr[i]
            else:
                dp[i] = dp[i-1]
            maxSum = max(maxSum, dp[i])

        return arr


arr = [1, -2, 3, 5, -2, 6, -1]
print(Solution().maxsumofSubarray(arr))
