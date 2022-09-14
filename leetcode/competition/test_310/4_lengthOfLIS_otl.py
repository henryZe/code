from typing import List

class Solution:
    # O(n^2)
    def lengthOfLIS(self, nums: List[int], k: int) -> int:
        n = max(nums)
        l = [0] * (n + 1)
        for num in nums:
            l[num] = max(l[max(num - k, 0):num]) + 1
        return max(l)

nums = [4,2,1,4,3,4,5,8,15]
k = 3
# nums = [7,4,5,1,8,12,4,7]
# k = 5
# nums = [1,5]
# k = 1
print(Solution().lengthOfLIS(nums, k))
