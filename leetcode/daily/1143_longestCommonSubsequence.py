class Solution:
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        str1 = text1
        str2 = text2

        m = len(str1)
        n = len(str2)

        if not m or not n:
            return 0

        dp = []
        for i in range(m + 1):
            dp.append([0] * (n + 1))
        
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if str1[i - 1] == str2[j - 1]:
                    dp[i][j] = dp[i - 1][j - 1] + 1
                else:
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

        return dp[m][n]

# text1 = "abcde"
# text2 = "ace"
# text1 = "abc"
# text2 = "abc"
text1 = "abc"
text2 = "def"
print(Solution().longestCommonSubsequence(text1, text2))