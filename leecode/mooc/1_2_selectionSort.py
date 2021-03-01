from typing import List

def selectionSort(nums: List[int]):
    for i in range(len(nums)):
        j = nums.index(min(nums[i:len(nums)]))
        nums[i], nums[j] = nums[j], nums[i]
    return nums

print(selectionSort([5,6,2,7,3,8,9,1]))
