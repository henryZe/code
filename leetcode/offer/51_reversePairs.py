from typing import List

class Solution:
    def mergeSort(self, nums: List[int], tmp: List[int], l: int, r: int) -> int:
        if l >= r:
            return 0

        mid = (l + r)//2
        inv_count = self.mergeSort(nums, tmp, l, mid) + self.mergeSort(nums, tmp, mid + 1, r)
        i, j = l, mid + 1
        pos = l
        while i <= mid and j <= r:
            if nums[i] <= nums[j]:
                tmp[pos] = nums[i]
                i += 1
                inv_count += j - 1 - mid
            else:
                tmp[pos] = nums[j]
                j += 1
                # inv_count += mid + 1 - i
            pos += 1

        for k in range(i, mid + 1):
            tmp[pos] = nums[k]
            pos += 1
            inv_count += r - mid
            # inv_count += r + 1 - j

        for k in range(j, r + 1):
            tmp[pos] = nums[k]
            pos += 1

        # print("left:", l, "right:", r)
        # print("nums", nums)
        # print("tmp", tmp)
        nums[l:r + 1] = tmp[l:r + 1]
        # print("nums", nums)
        # print(inv_count)
        return inv_count

    def reversePairs(self, nums: List[int]) -> int:
        n = len(nums)
        tmp = [0] * n
        return self.mergeSort(nums, tmp, 0, n - 1)


# nums = [7,5,6,4]
nums = [1,3,2,3,1]
print(Solution().reversePairs(nums))
