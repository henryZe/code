from typing import List

class Solution:
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        a = 0
        b = len(numbers) - 1
        while a < b:
            res = numbers[a] + numbers[b]
            if res == target:
                break

            if res < target:
                a += 1
            else:
                b -= 1

        return [a + 1, b + 1]


# numbers = [2,7,11,15]
# target = 9
# numbers = [2,3,4]
# target = 6
numbers = [-1,0]
target = -1
print(Solution().twoSum(numbers, target))