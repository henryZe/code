from typing import List

class Solution:
    def numberOfWeakCharacters(self, properties: List[List[int]]) -> int:
        # main key is x[0], second key is -x[1] ('-' means reverse)
        # O(n * logn)
        properties.sort(key = lambda x: (x[0], -x[1]))

        res = 0
        right = [-1, -1]
        # O(n)
        for item in properties[::-1]:
            # only compare x[1]
            if right[0] > item[0] and right[1] > item[1]:
                res += 1
            elif right[1] < item[1]:
                right = item
        return res

nums = [
    # [[5,5],[6,3],[3,6]],
    # [[2,2],[3,3]],
    # [[1,5],[10,4],[4,3]],
    [[7,7],[1,2],[9,7],[7,3],[3,10],[9,8],[8,10],[4,3],[1,5],[1,5]],
]
for i in nums:
    print(Solution().numberOfWeakCharacters(i))