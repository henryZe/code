from typing import List

class Solution:
    # def countDistinctIntegers(self, nums: List[int]) -> int:
    #     s_nums = set(nums)
    #     n = len(s_nums)
    #     for num in s_nums:
    #         num_rev = 0
    #         while num:
    #             num_rev = num_rev * 10 + num % 10
    #             num //= 10
    #         # "1000"'s and "100"'s revert number are all the "1".
    #         if num_rev not in s_nums:
    #             n += 1
    #     return n
    def countDistinctIntegers(self, nums: List[int]) -> int:
        s = set()
        for num in nums:
            s.add(num)
            num_rev = 0
            while num:
                num_rev = num_rev * 10 + num % 10
                num //= 10
            s.add(num_rev)
        return len(s)

# nums = [1,13,10,12,31]
nums = [2,2,2]
print(Solution().countDistinctIntegers(nums))
