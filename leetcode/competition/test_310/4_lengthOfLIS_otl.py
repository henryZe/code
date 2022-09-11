from typing import List

class Solution:
    def lengthOfLIS(self, nums: List[int], k: int) -> int:
        l = []
        h = {}

        for num in nums[::-1]:
            if not l:
                l.append(1)
                h[1] = [num]
                continue

            find = False
            cur_long = 0
            for long in l[::-1]:
                cur_long = long

                for value in h[cur_long]:
                    if num < value and num + k >= value:
                        cur_long += 1
                        if cur_long in h:
                            h[cur_long].append(num)
                        else:
                            h[cur_long] = [num]
                        if cur_long > l[-1]:
                            l.append(cur_long)
                        find = True
                        break

                if find == True:
                    break

            if find == False:
                h[1].append(num)
                continue

        return l[-1]

# nums = [4,2,1,4,3,4,5,8,15]
# k = 3
# nums = [7,4,5,1,8,12,4,7]
# k = 5
nums = [1,5]
k = 1
print(Solution().lengthOfLIS(nums, k))
