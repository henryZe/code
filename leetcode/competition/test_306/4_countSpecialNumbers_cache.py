import functools

class Solution:
    def countSpecialNumbers(self, n: int) -> int:
        s = str(n)

        @functools.lru_cache(None)
        def dp(bit: int, mask: int, islimit: bool, isnum: bool) -> int:
            if bit == len(s):
                return int(isnum)

            res = 0
            # continue to be not isnum
            if isnum == False:
                res += dp(bit + 1, mask, False, False)

            if islimit:
                up = int(s[bit])
            else:
                up = 9
            if isnum:
                down = 0
            else:
                down = 1
            for i in range(down, up + 1):
                # not used
                if ((1 << i) & mask) == 0:
                    res += dp(bit + 1, mask | (1 << i), i == up and islimit, True)

            return res

        return dp(0, 0, True, False)

# n = 20
# n = 5
# n = 135
n = 10000000000
print(Solution().countSpecialNumbers(n))
