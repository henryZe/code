import heapq

class SmallestInfiniteSet:
    def __init__(self):
        self.cur = 0
        self.heap = []
        return

    def popSmallest(self) -> int:
        if len(self.heap):
            return heapq.heappop(self.heap)

        self.cur += 1
        return self.cur

    def addBack(self, num: int) -> None:
        if num > 0 and num <= self.cur:
            if num not in self.heap:
                heapq.heappush(self.heap, num)
        return
