from typing import List

class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        a = 0
        n = len(nums)
        for i in range(n):
            if nums[i]:
                nums[a] = nums[i]
                a += 1
        
        for i in range(a, n):
            nums[i] = 0
        
        return

nums = [0,1,0,3,12]
Solution().moveZeroes(nums)
print(nums)