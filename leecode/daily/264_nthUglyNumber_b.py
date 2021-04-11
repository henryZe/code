import heapq

class Solution:
    # O(n * logn)
    def nthUglyNumber(self, n: int) -> int:
        factors = [2, 3, 5]
        heap = [1]
        setHeap = {1}

        for i in range(n - 1):
            cur = heapq.heappop(heap)
            for factor in factors:
                tmp = cur * factor
                if tmp not in setHeap:
                    heapq.heappush(heap, tmp)
                    setHeap.add(tmp)

        return heapq.heappop(heap)

n = 297
# n = 1
print(Solution().nthUglyNumber(n))