from typing import List

class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        if 0:
            size = len(nums)
            if size == 0:
                return 0

            dp = []
            for i in range(size):
                dp.append(1)
                print("dp[{}] = {}".format(i, dp[i]))
                for j in range(i):
                    if nums[i] > nums[j]:
                        dp[i] = max(dp[i], dp[j] + 1)
                        print("dp[{}] = {}".format(i, dp[i]))

            return max(dp)
        if 1:
            d = []
            for n in nums:
                if len(d) == 0 or n > d[-1]:
                    d.append(n)
                else:
                    l, r = 0, len(d) - 1
                    cur = r
                    while l <= r:
                        mid = (l + r) // 2
                        if d[mid] >= n:
                            r = mid - 1
                            cur = mid
                        else:
                            l = mid + 1
                    d[cur] = n
            
            return len(d)

obj = Solution()
nums = [10,9,2,5,3,7,101,18]
print(obj.lengthOfLIS(nums))
