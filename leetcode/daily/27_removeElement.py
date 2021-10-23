from typing import List

class Solution:
    def removeElement(self, nums: List[int], val: int) -> int:
        cur = 0
        ret = 0
        for i in range(len(nums)):
            if nums[i] == val:
                continue
            nums[ret] = nums[i]
            ret += 1
        return ret

nums = [3,2,2,3]
val = 3
print(Solution().removeElement(nums, val))