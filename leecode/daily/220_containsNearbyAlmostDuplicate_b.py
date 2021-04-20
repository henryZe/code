from typing import List
from sortedcontainers import SortedList

class Solution:
    # 滑动窗口 + 有序集合
    # 如果当前有序集合中存在相同元素，那么此时程序将直接返回true。因此本题中的有序集合无需处理相同元素的情况。
    # 
    # time O(n*log(min(n,k)))
    # space O(min(n, k))
    def containsNearbyAlmostDuplicate(self, nums: List[int], k: int, t: int) -> bool:
        windown = SortedList()
        for i in range(len(nums)):
            if nums[i] - t in windown:
                return True

            index = windown.bisect_right(nums[i] - t)
            if index in range(len(windown)):
                # print(windown, index, windown[index], nums[i])
                if windown[index] <= nums[i] + t:
                    return True

            windown.add(nums[i])
            if i >= k:
                windown.remove(nums[i - k])

        return False


# nums = [1,2,3,1]
# k = 3
# t = 0
# nums = [1,0,1,1]
# k = 1
# t = 2
nums = [1,5,9,1,5,9]
k = 2
t = 3
print(Solution().containsNearbyAlmostDuplicate(nums, k, t))