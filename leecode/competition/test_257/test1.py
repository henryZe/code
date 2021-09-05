from typing import List

class Solution:
    def countQuadruplets(self, nums: List[int]) -> int:
        n = len(nums)
        # nums.sort()
        count = 0
        # print(nums)
        for i in range(0, n):
            for j in range(i + 1, n):
                for k in range(j + 1, n):
                    for l in range(k + 1, n):
                        sum_v = nums[i] + nums[j] + nums[k]
                        if nums[l] == sum_v:
                            # print(i, j, k, l)
                            count += 1
                        # elif nums[l] > sum_v:
                        #     break

        return count

nums = [
    [1,2,3,6],
    [3,3,6,4,5],
    [1,1,1,3,5],
    [28,8,49,85,37,90,20,8],
]
for i in nums:
    print(Solution().countQuadruplets(i))
