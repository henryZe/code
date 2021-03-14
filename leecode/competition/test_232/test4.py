from typing import List

class Solution:
    def maximumScore(self, nums: List[int], k: int) -> int:
        n = len(nums)
        ret = 0
        for i in range(0, k + 1):
            minNum = nums[i]
            for j in range(i, n):
                minNum = min(minNum, nums[j])
                if i <= k <= j:
                    cur = minNum * (j + 1 - i)
                    ret = max(cur, ret)
        return ret

# nums = [5,5,4,5,4,1,1,1]
# k = 0
nums = [1,4,3,7,4,5]
k = 3

print(Solution().maximumScore(nums, k))