# 计算复杂度 O(n^2)
# 空间复杂度 O(n^2)
class Solution:
    def minCut(self, s: str) -> int:
        n = len(s)
        f = []
        for _ in range(n):
            f.append([True] * n)

        for i in range(n - 1, -1, -1):
            for j in range(i + 1, n):
                f[i][j] = ((s[i] == s[j]) and f[i+1][j-1])

        count = [float("inf")] * n
        for i in range(n):
            if f[0][i]:
                count[i] = 0
            else:
                for j in range(i):
                    if f[j + 1][i]:
                        count[i] = min(count[i], count[j] + 1)

        return count[n - 1]


s = "ababababababababababababcbabababababababababababa"
print(Solution().minCut(s))
