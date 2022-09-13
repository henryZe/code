from typing import List

class BookMyShow:
    def __init__(self, n: int, m: int):
        self.n = n
        self.m = m
        self.min = [0] * (4 * n)
        self.sum = [0] * (4 * n)
        return

    # fill row with val
    # O(log n)
    def add(self, idx: int, left: int, right: int, row: int, val: int):
        if left == right:
            self.min[idx] += val
            self.sum[idx] += val
            return

        mid = (left + right) // 2
        if row <= mid:
            self.add(idx * 2, left, mid, row, val)
        else:
            self.add(idx * 2 + 1, mid + 1, right, row, val)

        self.min[idx] = min(self.min[idx * 2], self.min[idx * 2 + 1])
        self.sum[idx] = self.sum[idx * 2] + self.sum[idx * 2 + 1]
        return

    # return the sum of [range_l, range_r]
    # O(log n)
    def query_sum(self, idx: int, left: int, right: int, range_l: int, range_r: int) -> int:
        if range_l <= left and right <= range_r:
            return self.sum[idx]

        sum = 0
        mid = (left + right) // 2
        if range_l <= mid:
            sum += self.query_sum(idx * 2, left, mid, range_l, range_r)
        if range_r > mid:
            sum += self.query_sum(idx * 2 + 1, mid + 1, right, range_l, range_r)
        return sum

    # return the row of first continual block which meets val
    # O(log n)
    def row(self, idx: int, left: int, right: int, range_r: int, val: int) -> int:
        if self.min[idx] > val:
            # return failed
            return 0

        if left == right:
            return left

        mid = (left + right) // 2
        # left part meets val
        if self.min[idx * 2] <= val:
            return self.row(idx * 2, left, mid, range_r, val)

        if mid + 1 > range_r:
            # return failed
            return 0

        return self.row(idx * 2 + 1, mid + 1, right, range_r, val)

    # O(logN + logN + logN)
    def gather(self, k: int, maxRow: int) -> List[int]:
        row = self.row(1, 1, self.n, maxRow + 1, self.m - k)
        if row == 0:
            return []

        added = self.query_sum(1, 1, self.n, row, row)
        self.add(1, 1, self.n, row, k)

        # return [row, column]
        return [row - 1, added]

    # O(logN + logN + op * (logN + logN))
    def scatter(self, k: int, maxRow: int) -> bool:
        if (maxRow + 1) * self.m - self.query_sum(1, 1, self.n, 1, maxRow + 1) < k:
            return False

        row = self.row(1, 1, self.n, maxRow + 1, self.m - 1)
        while k > 0:
            left = self.m - self.query_sum(1, 1, self.n, row, row)
            if k <= left:
                self.add(1, 1, self.n, row, k)
                return True

            k -= left
            self.add(1, 1, self.n, row, left)
            row += 1
        return True

obj = BookMyShow(2, 5)
print(obj.gather(4, 0))
print(obj.gather(2, 0))
print(obj.scatter(5, 1))
print(obj.scatter(5, 1))
