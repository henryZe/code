from typing import List

class Solution:
    def maximumSum(self, nums: List[int]) -> int:
        nums.sort()
        d = {}
        for num in nums:
            s = 0
            p_num = num
            while p_num:
                s += p_num % 10
                p_num = p_num // 10
            if s not in d:
                d[s] = [num]
            else:
                d[s].append(num)

        # print(d)
        l = []
        for v in d.values():
            if len(v) < 2:
                continue
            s = v[-1] + v[-2]
            l.append(s)

        if len(l) == 0:
            return -1
        return max(l)


nums = [10,12,19,14]
# nums = [18,43,36,13,7]
print(Solution().maximumSum(nums))
