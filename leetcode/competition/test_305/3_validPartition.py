from typing import List

def dfs(idx, n, nums):
    if idx == n:
        return True

    if idx == n - 1:
        return False

    if nums[idx] == nums[idx + 1]:
        res = dfs(idx + 2, n, nums)
        if res == True:
            return True

    if idx <= n - 3:
        if (nums[idx] == nums[idx + 1] and nums[idx + 1] == nums[idx + 2]) or \
            (nums[idx] + 1 == nums[idx + 1] and nums[idx + 1] + 1 == nums[idx + 2]):
            res = dfs(idx + 3, n, nums)
            if res == True:
                return True

    return False

class Solution:
    def validPartition(self, nums: List[int]) -> bool:
        return dfs(0, len(nums), nums)
                    
# nums = [4,4,4,5,6]
nums = [1,1,1,2]
print(Solution().validPartition(nums))
