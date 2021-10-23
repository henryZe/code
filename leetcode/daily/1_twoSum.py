from typing import List

class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        n = len(nums)
        dict = {}
        for i in range(n):
            if nums[i] not in dict.keys():
                dict[target - nums[i]] = i
            else:
                return [dict[nums[i]], i]

        return []

nums = [2,7,11,15]
target = 9
print(Solution().twoSum(nums, target))
