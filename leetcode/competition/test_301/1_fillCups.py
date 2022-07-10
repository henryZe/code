from itertools import count
from typing import List
import heapq

class Solution:
    def fillCups(self, amount: List[int]) -> int:
        assert(len(amount) == 3)

        count = 0
        heap = []
        for i in amount:
            # min heap -> max heap
            if i:
                heapq.heappush(heap, -i)

        while len(heap):
            count += 1
            flag = False

            a = heapq.heappop(heap)
            a += 1
            if len(heap):
                flag = True
                b = heapq.heappop(heap)
                b += 1

            if a < 0:
                heapq.heappush(heap, a)
            if flag and b < 0:
                heapq.heappush(heap, b)

        return count

# amount = [1,4,2]
# amount = [5,4,4]
amount = [5,0,0]
print(Solution().fillCups(amount))
