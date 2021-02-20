class Solution:
    def maxsumofSubarray(self , arr ):
        dp = [0] * len(arr)
        dp[0] = arr[0]
        maxSum = dp[0]

        for i in range(1, len(arr)):
            if dp[i-1] > 0:
                dp[i] = dp[i-1] + arr[i]
            else:
                dp[i] = arr[i]
            maxSum = max(maxSum, dp[i])

        return maxSum


arr = [1, -2, 3, 5, -2, 6, -1]
print(Solution().maxsumofSubarray(arr))
