from typing import List

class Solution:
    def goodIndices(self, nums: List[int], k: int) -> List[int]:
        n = len(nums)
        a = [1] * n
        b = [1] * n

        for i in range(1, n):
            if nums[i] <= nums[i - 1]:
                a[i] += a[i - 1]
        for i in range(n - 2, -1, -1):
            if nums[i] <= nums[i + 1]:
                b[i] += b[i + 1]

        res = []
        for i in range(k, n - k):
            if a[i - 1] >= k and b[i + 1] >= k:
                res.append(i)

        return res

# nums = [2,1,1,1,3,4,1]
# k = 2
# nums = [2,1,1,2]
# k = 2
nums = [878724,201541,179099,98437,35765,327555,475851,598885,849470,943442]
k = 4
print(Solution().goodIndices(nums, k))
