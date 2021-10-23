from typing import List

# O(n * logn)
# 归并排序 + 索引数组(比较的是 nums，操作的是 索引数组)
class Solution:
    def countSmaller(self, nums: List[int]) -> List[int]:
        if not nums:
            return []

        n = len(nums)
        indexes = list(range(n))
        self.temp = [0] * n
        res = [0] * n

        self.mergeOrder(nums, 0, n - 1, indexes, res)
        return res

    def mergeOrder(self, nums: List[int], l: int, r: int, indexes: List[int], res: List[int]):
        if l >= r:
            return
        
        mid = (l + r)//2
        self.mergeOrder(nums, l, mid, indexes, res)
        self.mergeOrder(nums, mid + 1, r, indexes, res)
        
        if nums[indexes[mid]] <= nums[indexes[mid + 1]]:
            return
        self.sortCountSmaller(nums, l, r, mid, indexes, res)
        return

    def sortCountSmaller(self, nums: List[int], l: int, r: int, mid: int, indexes: List[int], res: List[int]):
        # [left,mid] 前有序数组
        # [mid+1,right] 后有序数组

        self.temp[l: r + 1] = indexes[l: r + 1]
        
        i, j = l, mid + 1
        for k in range(l, r + 1):
            # former ordered array is end
            if i > mid:
                indexes[k] = self.temp[j]
                j += 1
            # latter ordered array is end
            elif j > r:
                indexes[k] = self.temp[i]
                i += 1
                res[indexes[k]] += r - mid
            
            # 严格小于
            elif nums[self.temp[i]] <= nums[self.temp[j]]:
                indexes[k] = self.temp[i]
                i += 1
                res[indexes[k]] += j - 1 - mid
            else:
                indexes[k] = self.temp[j]
                j += 1
        return


if __name__ == '__main__':
    # nums = [5,2,6,1]
    nums = [2,2,2,2]
    # nums = [-1,-1]
    print(Solution().countSmaller(nums))
