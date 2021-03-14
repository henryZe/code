from typing import List
import heapq

class fenwickTree:
    def __init__(self, size: int):
        self.size = size
        self.tree = [0 for _ in range(size + 1)]

    def __str__(self):
        return "size: {} arr: {}".format(self.size, self.tree)

    def lowbit(self, x: int) -> int:
        return x & (-x)

    def update(self, index: int, delta: int):
        while index <= self.size:
            self.tree[index] += delta
            index += self.lowbit(index)

    def query(self, index: int) -> int:
        res = 0
        while index:
            res += self.tree[index]
            index -= self.lowbit(index)
        return res

# O(n * logn)
# 离散化数组 + 树状数组
class Solution:
    def countSmaller(self, nums: List[int]) -> List[int]:
        if not nums:
            return []

        num_set = list(set(nums))
        heapq.heapify(num_set)
        num_dict = {}
        rank = 1
        for i in range(len(num_set)):
            # 离散化数组，缩小数据规模
            num = heapq.heappop(num_set)
            num_dict[num] = rank
            rank += 1
        
        tree = fenwickTree(len(num_dict))
        res = [0 for _ in range(len(nums))]
        for i in range(len(nums) - 1, -1, -1):
            rank = num_dict[nums[i]]
            res[i] = tree.query(rank - 1)
            tree.update(rank, 1)

        return res


nums = [5,2,6,1]
# nums = [-1,-1]
print(Solution().countSmaller(nums))
