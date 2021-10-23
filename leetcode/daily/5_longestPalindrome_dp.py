class Solution:
    # dynamic programming search
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        dp = [[False] * n for _ in range(n)]
        for i in range(n):
            dp[i][i] = True

        max_len = 1
        new = 0
        for j in range(1, n):
            for i in range(0, j):
                if s[i] == s[j]:
                    if j - i + 1 > 3 and dp[i + 1][j - 1] == False:
                        continue 

                    dp[i][j] = True
                    cur_len = j - i + 1
                    if max_len < cur_len:
                        max_len = cur_len
                        new = i

        return s[new:new + max_len]

print(Solution().longestPalindrome("babad"))
print(Solution().longestPalindrome("cbbd"))
