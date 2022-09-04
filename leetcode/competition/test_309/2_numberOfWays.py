class Solution:
    def numberOfWays(self, startPos: int, endPos: int, k: int) -> int:
        dp = []
        for i in range(startPos - k, startPos + k + 1):
            dp.append([-1] * (k + 1))

        def f(pos, step):
            if step == 0:
                if pos == endPos:
                    return 1
                else:
                    return 0

            # print(pos, step)
            if dp[pos - startPos][step] >= 0:
                return dp[pos - startPos][step]

            res = 0
            res = f(pos - 1, step - 1) + f(pos + 1, step - 1)
            dp[pos - startPos][step] = res
            return res

        return f(startPos, k) % (10**9 + 7)


# startPos = 1
# endPos = 2
# k = 3
startPos = 272
endPos = 270
k = 6
print(Solution().numberOfWays(startPos, endPos, k))
