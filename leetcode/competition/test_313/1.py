from math import gcd

class Solution:
    def commonFactors(self, a: int, b: int) -> int:
        c = gcd(a, b)
        i = 1
        ans = 0
        while i * i < c:
            if c % i == 0:
                ans += 2
            i += 1
        if i * i == c:
            ans += 1
        return ans

a = 12
b = 6
print(Solution().commonFactors(a, b))
