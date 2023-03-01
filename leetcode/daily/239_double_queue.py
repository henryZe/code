from typing import List
import collections

class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        n = len(nums)
        # double dequeue
        q = collections.deque()

        ans = []
        for idx in range(n):
            while q and nums[q[-1]] < nums[idx]:
                q.pop()
            q.append(idx)

            # check left edge (idx - k + 1)
            while q[0] < idx - k + 1:
                q.popleft()

            # check right edge (idx)
            if idx >= k - 1:
                ans.append(nums[q[0]])

        return ans

# nums = [1,3,-1,-3,5,3,6,7]
# k = 3
nums = [1,-1]
k = 1
obj = Solution()
print(obj.maxSlidingWindow(nums, k))
