from typing import List

class Solution:
    # 双指针
    # Time O(n)
    # Space O(1)
    def trap(self, height: List[int]) -> int:
        if not height:
            return 0

        n = len(height)

        res = 0
        left = 0
        right = n - 1
        leftMax, rightMax = 0, 0
        while left < right:
            # print(left, right)
            leftMax = max(height[left], leftMax)
            rightMax = max(height[right], rightMax)
            if height[left] > height[right]:
                res += rightMax - height[right]
                right -= 1
            else:
                res += leftMax - height[left]
                left += 1
            # print("res", res)
        return res

height = [0,1,0,2,1,0,1,3,2,1,2,1]
print(Solution().trap(height))
