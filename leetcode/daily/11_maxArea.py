from typing import List

class Solution:
    def maxArea(self, height: List[int]) -> int:
        l, r = 0, len(height) - 1
        res = 0
        while l < r:
            capacity = min(height[l], height[r]) * (r - l)
            res = max(res, capacity)
            if height[l] < height[r]:
                l += 1
            else:
                r -= 1

        return res

# height = [1,8,6,2,5,4,8,3,7]
height = [4,3,2,1,4]
print(Solution().maxArea(height))
