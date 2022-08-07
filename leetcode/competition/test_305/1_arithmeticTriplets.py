from typing import List

def find_next_num(idx, nums, next_num):
    for i in range(idx + 1, len(nums)):
        if nums[i] == next_num:
            return i
        elif nums[i] > next_num:
            return -1

    return -1

class Solution:
    def arithmeticTriplets(self, nums: List[int], diff: int) -> int:
        count = 0
        for i in range(len(nums) - 2):

            ret = find_next_num(i, nums, nums[i] + diff)
            if ret < 0:
                continue

            ret = find_next_num(ret, nums, nums[i] + diff + diff)
            if ret < 0:
                continue

            count += 1

        return count

# nums = [0,1,4,6,7,10]
# diff = 3
nums = [4,5,6,7,8,9]
diff = 2
print(Solution().arithmeticTriplets(nums, diff))
