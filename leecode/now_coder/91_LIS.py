import collections
from typing import List
import bisect

class Solution:
    def LIS(self , arr ):
        # write code here
        n = len(arr)
        dp = [1] * n
        lenth = 1
        array = [arr[0]]
        for i in range(1, n):
            if arr[i] > array[-1]:
                lenth += 1
                dp[i] = lenth
                array.append(arr[i])
            else:
                index = bisect.bisect(array, arr[i])
                dp[i] = index + 1
                array[index] = arr[i]
        res = []
        max_num = array[-1]
        max_num_index = arr.index(max_num)
        lenth = max(dp)
        for i in range(max_num_index, -1, -1):
            if res == [] or (arr[i] < res[-1] and dp[i] == lenth):
                res.append(arr[i])
                lenth -= 1
        return res[::-1]


obj = Solution()
nums = [10,9,2,5,3,7,101,18]
print(obj.LIS(nums))