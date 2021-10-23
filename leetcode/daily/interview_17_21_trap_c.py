from typing import List

class Solution:
    # 单调栈
    # Time O(n)
    # Space O(n)
    def trap(self, height: List[int]) -> int:
        ans = 0
        stack = []
        n = len(height)

        for i, h in enumerate(height):
            # current height is higher than last one's
            while stack and height[i] > height[stack[-1]]:
                # print(i, stack)
                # pop low height
                top = stack.pop()
                # no left any more, pass it
                if not stack:
                    break
                left = stack[-1]
                curWidth = i - left - 1
                curHeight = min(height[left], height[i]) - height[top]
                ans += curHeight * curWidth
                # print(ans)
            stack.append(i)
        
        # print(stack)
        return ans

height = [0,1,0,2,1,0,1,3,2,1,2,1]
print(Solution().trap(height))
