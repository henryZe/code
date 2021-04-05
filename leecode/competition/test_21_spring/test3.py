from typing import List
import heapq

class Solution:
    # O(n * logn)
    def magicTower(self, nums: List[int]) -> int:
        if sum(nums) < 0:
            return -1

        cur = 1
        stack = []
        n = len(nums)
        ans = 0

        for i in range(n):
            if nums[i] < 0:
                heapq.heappush(stack, nums[i])
            cur += nums[i]
            while cur <= 0:
                cur -= heapq.heappop(stack)
                ans += 1

        return ans

# nums = [-200,-300,400,0]
nums = [100,100,100,-250,-60,-140,-50,-50,100,150]
print(Solution().magicTower(nums))