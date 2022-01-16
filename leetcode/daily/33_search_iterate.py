from typing import List

class Solution:
    def search(self, nums: List[int], target: int) -> int:
        for i, num in enumerate(nums):
            if num == target:
                return i
        return -1

# nums = [4,5,6,7,0,1,2]
# target = 0
nums = [4,5,6,7,0,1,2]
target = 3
# nums = [1]
# target = 0
print(Solution().search(nums, target))
