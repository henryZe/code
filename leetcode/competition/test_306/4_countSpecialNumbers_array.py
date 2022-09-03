class Solution:
    def countSpecialNumbers(self, n: int) -> int:
        s = str(n)

        cache = []
        for i in range(len(s)):
            # only !islimit and isnum, use cache
            # Reason:
            # 1. (bit, mask) pair only appears once
            # 2. only when !islimit and isnum, cache the result
            cache.append([-1] * (1 << 10))

        def dp(bit: int, mask: int, islimit: bool, isnum: bool) -> int:
            if bit == len(s):
                return int(isnum)

            if not islimit and isnum and cache[bit][mask] >= 0:
                # return cache
                return cache[bit][mask]

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

            # cache result
            if not islimit and isnum:
                cache[bit][mask] = res
            return res

        return dp(0, 0, True, False)

# n = 20
# n = 5
# n = 135
n = 10000000000
print(Solution().countSpecialNumbers(n))
