from turtle import update
from typing import List

class segment_tree:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (4 * n)
        return

    # O(logN)
    def update(self, idx, l, r, num, val):
        if l == r:
            self.tree[idx] = val
            return

        mid = (l + r) // 2
        if num <= mid:
            self.update(idx * 2, l, mid, num, val)
        else:
            self.update(idx * 2 + 1, mid + 1, r, num, val)

        self.tree[idx] = max(self.tree[idx * 2], self.tree[idx * 2 + 1])
        return

    # O(logN)
    def query(self, idx, l, r, range_l, range_r):
        if range_l <= l and r <= range_r:
            return self.tree[idx]

        res = 0
        mid = (l + r) // 2
        if range_l <= mid:
            res = max(res, self.query(idx * 2, l, mid, range_l, range_r))
        if mid < range_r:
            res = max(res, self.query(idx * 2 + 1, mid + 1, r, range_l, range_r))
        return res

class Solution:
    def lengthOfLIS(self, nums: List[int], k: int) -> int:
        n = max(nums)
        seg = segment_tree(n)

        # O(N * logN)
        for num in nums:
            if num == 1:
                seg.update(1, 1, n, 1, 1)
                continue

            range_l = max(num - k, 1)
            val = seg.query(1, 1, n, range_l, num - 1) + 1
            seg.update(1, 1, n, num, val)

        return seg.tree[1]

# nums = [4,2,1,4,3,4,5,8,15]
# k = 3
# nums = [7,4,5,1,8,12,4,7]
# k = 5
nums = [1,5]
k = 1
print(Solution().lengthOfLIS(nums, k))
