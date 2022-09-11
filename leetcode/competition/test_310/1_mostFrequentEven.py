from typing import List

class Solution:
    def mostFrequentEven(self, nums: List[int]) -> int:
        h = {}
        s = set(nums)
        l = list(s)
        l.sort()
        for num in nums:
            if num % 2:
                continue

            if num in h:
                h[num] += 1
            else:
                h[num] = 1

        if not h.keys():
            return -1

        max_time = max(h.values())
        for num in l:
            if num not in h:
                continue
            if h[num] == max_time:
                return num

        return 0

nums = [0,1,2,2,4,4,1]
# nums = [4,4,4,9,2,4]
# nums = [29,47,21,41,13,37,25,7]
print(Solution().mostFrequentEven(nums))
