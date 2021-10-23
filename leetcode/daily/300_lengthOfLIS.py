from typing import List

class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        n = len(nums)
        dp = [nums[0]]

        for i in range(1, n):
            if nums[i] > dp[-1]:
                dp.append(nums[i])
            elif nums[i] == dp[-1]:
                continue
            else:
                l, r = 0, len(dp) - 1
                pos = r
                while l <= r:
                    mid = (l + r) // 2
                    if dp[mid] < nums[i]:
                        l = mid + 1
                    else:
                        pos = mid
                        r = mid - 1
                dp[pos] = nums[i]
            # print(dp)

        return len(dp)

nums = [10,9,2,5,3,7,101,18]
# nums = [0,1,0,3,2,3]
# nums = [7,7,7,7,7,7,7]
nums = [1,3,6,7,9,4,10,5,6]
print(Solution().lengthOfLIS(nums))
