from typing import List

class Solution:
    def canJump(self, nums: List[int]) -> bool:
        reach = 0
        size = len(nums)

        for i in range(size):
            if i > reach:
                return False
            reach = max(reach, i + nums[i])
            if reach >= size - 1:
                return True

        return True

obj = Solution()
l = [3,2,1,0,4]
print(obj.canJump(l))
