from typing import List

class Solution:
    def partition(self, s: str) -> List[List[str]]:
        n = len(s)
        f = []
        for _ in range(len(s)):
            f.append([True] * n)

        for i in range(n - 1, -1, -1):
            for j in range(i + 1, n):
                f[i][j] = ((s[i] == s[j]) and f[i+1][j-1])

        ret = []
        ans = []
        def dfs(i: int):
            if i == n:
                # ret.append(ans) just append the pointer
                ret.append(ans[:])
                return

            for j in range(i, n):
                if f[i][j]:
                    # caution: append string's content
                    ans.append(s[i:j+1])
                    dfs(j+1)
                    ans.pop()

        dfs(0)
        # print("ret", ret)
        return ret

s = "aab"
# s = "a"
print(Solution().partition(s))
