from typing import List

# 线段树
class NumArray:
    # O(n)
    def buildTree(self, nums: List[int]):
        n = len(nums)
        self.n = n
        j = 0
        # init leaf nodes
        for i in range(n, 2 * n):
            self.tree[i] = nums[j]
            j += 1

        # init parent nodes
        for i in range(n - 1, 0, -1):
            self.tree[i] = self.tree[i*2] + self.tree[i*2 + 1]

        return

    def __init__(self, nums: List[int]):
        n = len(nums)
        self.tree = [0] * (2 * n)
        self.buildTree(nums)
        return

    # O(log n)
    def update(self, index: int, val: int) -> None:
        pos = index + self.n
        self.tree[pos] = val

        while pos > 0:
            left = right = pos
            # self is left node
            if pos % 2 == 0:
                right = pos + 1
            # self is right node
            if pos % 2 == 1:
                left = pos - 1
        
            pos //= 2
            self.tree[pos] = self.tree[left] + self.tree[right]

        return

    # O(log n)
    def sumRange(self, left: int, right: int) -> int:
        left += self.n
        right += self.n
        sum = 0
        while left <= right:
            if left % 2 == 1:
                sum += self.tree[left]
                left += 1
            if right % 2 == 0:
                sum += self.tree[right]
                right -= 1
            left //= 2
            right //= 2

        return sum


nums = [1, 3, 5]
obj = NumArray(nums)
print(obj.sumRange(0, 2))
obj.update(1, 2)
print(obj.sumRange(0, 2))
