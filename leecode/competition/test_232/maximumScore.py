from typing import List

class Solution:
    # 暴力解法
    # O(n ^ 2)
    # def maximumScore(self, nums: List[int], k: int) -> int:
    #     n = len(nums)
    #     ret = 0
    #     for i in range(0, k + 1):
    #         minNum = nums[i]
    #         for j in range(i, n):
    #             minNum = min(minNum, nums[j])
    #             if i <= k <= j:
    #                 cur = minNum * (j + 1 - i)
    #                 ret = max(cur, ret)
    #     return ret

    # 单调栈
    # O(n)
    def maximumScore(self, nums: List[int], k: int) -> int:
        stack = []
        n = len(nums)
        ans = 0
        
        def update(idx: int, l: int, r: int):
            if l <= k <= r:
                nonlocal ans
                ans = max(ans, nums[idx] * (r + 1 - l))
            return

        for i, num in enumerate(nums):
            while stack and num < nums[stack[-1]]:
                # idx is the min index during nums[l:r + 1]
                idx = stack.pop()
                l = 0 if not stack else stack[-1] + 1
                r = i - 1
                update(idx, l, r)
            stack.append(i)

        # nums is over
        while stack:
            idx = stack.pop()
            l = 0 if not stack else stack[-1] + 1
            r = n - 1
            update(idx, l, r)

        return ans

# nums = [5,5,4,5,4,1,1,1]
# k = 0
# nums = [1,4,3,7,4,5]
# k = 3
nums = [6569,9667,3148,7698,1622,2194,793,9041,1670,1872]
k = 5

print(Solution().maximumScore(nums, k))