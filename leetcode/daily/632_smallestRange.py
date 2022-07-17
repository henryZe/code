from typing import List
import heapq

def update_interval(new_interval, interval):
    if new_interval[1] - new_interval[0] < interval[1] - interval[0]:
        return new_interval
    return interval

class Solution:
    # 贪心 + heap optimize
    # O(N * logN)
    def smallestRange(self, nums: List[List[int]]) -> List[int]:
        idx = [0] * len(nums)
        heap = []
        for i, l in enumerate(nums):
            heap.append([l[0], i])
        heapq.heapify(heap)

        heap_max = max(heap)
        heap_min = heapq.heappop(heap)
        interval = [heap_min[0], heap_max[0]]

        while True:
            min_idx = heap_min[1]
            idx[min_idx] += 1
            if idx[min_idx] == len(nums[min_idx]):
                break

            min_val = [nums[min_idx][idx[min_idx]], min_idx]
            heap_max = max(heap_max, min_val)
            heapq.heappush(heap, min_val)
            heap_min = heapq.heappop(heap)
            interval = update_interval([heap_min[0], heap_max[0]], interval)

        return interval


# nums = [[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
# nums = [[1,2,3],[1,2,3],[1,2,3]]
print(Solution().smallestRange(nums))
