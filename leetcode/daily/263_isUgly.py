class Solution:
    elements = [2, 3, 5]

    def isUgly(self, n: int) -> bool:
        if n == 0:
            return False

        if n == 1:
            return True

        for i in self.elements:
            if n % i == 0:
                res = self.isUgly(n // i)
                if res:
                    return res

        return False


n = 6
n = 8
n = 14
n = 1
n = 0
print(Solution().isUgly(n))