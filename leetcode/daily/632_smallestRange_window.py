from typing import List

def update_interval(new_interval, interval):
    if new_interval[1] - new_interval[0] < interval[1] - interval[0]:
        return new_interval
    return interval

class Solution:
    # hash + 滑动窗口
    # O(N)
    def smallestRange(self, nums: List[List[int]]) -> List[int]:
        d = dict()
        min_all = nums[0][0]
        max_all = nums[0][0]
        for i, num in enumerate(nums):
            for n in num:
                if n not in d:
                    d[n] = [i]
                else:
                    d[n].append(i)
                min_all = min(min_all, n)
                max_all = max(max_all, n)

        interval = [min_all, max_all]
        left = min_all
        right = left - 1
        arr_size = len(nums)
        frq = [0] * arr_size
        include = 0

        while right < max_all:
            right += 1
            if right not in d:
                continue

            for x in d[right]:
                frq[x] += 1
                if frq[x] == 1:
                    include += 1

                while include == arr_size:
                    if left in d:
                        interval = update_interval([left, right], interval)
                        for y in d[left]:
                            frq[y] -= 1
                            if frq[y] == 0:
                                include -= 1
                    left += 1
                    if left > right:
                        # optimization
                        return [right, right]

        return interval

nums = [[-1,1,2,3], [1,2], [1,3]]
# nums = [[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
# nums = [[1,2,3],[1,2,3],[1,2,3]]
print(Solution().smallestRange(nums))
