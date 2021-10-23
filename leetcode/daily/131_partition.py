from typing import List
import functools

# 计算复杂度 O(n * 2^n)
# 空间复杂度 O(n^2)
# class Solution:
#     def partition(self, s: str) -> List[List[str]]:
#         n = len(s)
#         f = []
#         for _ in range(len(s)):
#             f.append([True] * n)
# 
#         for i in range(n - 1, -1, -1):
#             for j in range(i + 1, n):
#                 f[i][j] = ((s[i] == s[j]) and f[i+1][j-1])
# 
#         ret = []
#         ans = []
#         def dfs(i: int):
#             if i == n:
#                 # ret.append(ans) just append the pointer
#                 ret.append(ans[:])
#                 return
# 
#             for j in range(i, n):
#                 if f[i][j]:
#                     # caution: append string's content
#                     ans.append(s[i:j+1])
#                     dfs(j+1)
#                     ans.pop()
# 
#         dfs(0)
#         return ret

class Solution:
    def partition(self, s: str) -> List[List[str]]:
        n = len(s)
        ret = []
        ans = []

        @functools.lru_cache
        def isPalindrome(i: int, j: int) -> bool:
            if i >= j:
                return True
            return isPalindrome(i + 1, j - 1) and (s[i] == s[j])

        def dfs(i: int):
            if i == n:
                ret.append(ans[:])
                return

            for j in range(i, n):
                if isPalindrome(i, j):
                    ans.append(s[i:j+1])
                    dfs(j + 1)
                    ans.pop()
            return

        dfs(0)
        return ret

s = "aab"
# s = "a"
print(Solution().partition(s))
