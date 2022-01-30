class Solution:
    def longestValidParentheses(self, s: str) -> int:
        if not s:
            return 0

        stack = []
        n = len(s)
        dp = [0] * n

        for i in range(1, n):
            if s[i] == ')':
                if s[i - 1] == '(':
                    if i >= 2:
                        dp[i] = dp[i - 2] + 2

                    else:
                        dp[i] = 2

                else:
                    # s[i - 1] = ')'
                    if i - dp[i - 1] - 1 >= 0:
                        if s[i - dp[i - 1] - 1] == '(':
                            if i >= 2:
                                dp[i] = dp[i - 1] + dp[i - dp[i - 1] - 2] + 2
                            else:
                                dp[i] = dp[i - 1] + 2

        # print(dp)
        return max(dp)

# s = "(()"
# s = ")()())"
# s = ""
# s = "()(()"
# s = ")("
s = "(()))())("
print(Solution().longestValidParentheses(s))
