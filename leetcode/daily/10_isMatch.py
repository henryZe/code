class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        nx = len(s) + 1
        ny = len(p) + 1
        dp = []
        for _ in range(nx):
            dp.append([False] * ny)

        dp[0][0] = True

        for j in range(1, ny):
            if p[j - 1] == '*':
                dp[0][j] = dp[0][j - 2]

        def judge(dp, i, j):
            if p[j - 1] == '.':
                return dp[i - 1][j - 1]

            if p[j - 1] == '*':
                # no character
                if dp[i][j - 2]:
                    return True
                # at least one character
                elif s[i - 1] == p[j - 1 - 1] or p[j - 1 - 1] == '.':
                    return dp[i - 1][j]
                return False

            else:
                if s[i - 1] == p[j - 1]:
                    return dp[i - 1][j - 1]
                else:
                    return False

        for i in range(1, nx):
            for j in range(1, ny):
                dp[i][j] = judge(dp, i, j)

        # for dp_sub in dp:
        #     print(dp_sub)
        return dp[nx - 1][ny - 1]


# s = "aa"
# p = "a"
# s = "aa"
# p = "a*"
# s = "ab"
# p = ".*"
# s = "aab"
# p = "c*a*b"
# s = "mississippi"
# p = "mis*is*p*."
# s = "aaabcaab"
# p = "a*b.a*b"
# s = "ab"
# p = ".*c"
s = "a"
p = ".*..a*"
print(Solution().isMatch(s, p))
