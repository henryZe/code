from typing import List

class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        def backtrack(nums: List[int], pos: int):
            n = len(nums)
            if pos == n:
                res.append(nums[:])
                return

            for i in range(pos, n):
                nums[pos], nums[i] = nums[i], nums[pos]
                backtrack(nums, pos + 1)
                nums[pos], nums[i] = nums[i], nums[pos]

            return

        res = []
        backtrack(nums, 0)
        return res

nums = [1,2,3]
print(Solution().permute(nums))
