from typing import List

class Solution:
    def plusOne(self, digits: List[int]) -> List[int]:
        digits[-1] += 1
        n = len(digits)

        for i in range(n - 1, -1, -1):
            if digits[i] > 9:
                digits[i] -= 10
                if i - 1 >= 0 :
                    digits[i - 1] += 1
                else:
                    digits.insert(0, 1)
                    break
        return digits

# digits = [1,2,3]
digits = [9,9,9]
print(Solution().plusOne(digits))
