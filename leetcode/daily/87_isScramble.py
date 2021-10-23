from typing import Counter
from functools import lru_cache

class Solution:
    def isScramble(self, s1: str, s2: str) -> bool:
        # 记忆化搜索
        # make sure cache maxsize more than currsize, which improve program's performance
        @lru_cache(maxsize=2048, typed=False)
        def dfs(i1: int, i2: int, length: int) -> bool:
            # 判断两个子串是否相等
            if s1[i1:i1+length] == s2[i2:i2+length]:
                return True

            # 判断是否存在字符 c 在两个子串中出现的次数不同
            if Counter(s1[i1:i1+length]) != Counter(s2[i2:i2+length]):
                return False

            # 枚举分割位置
            for i in range(1, length):
                # no switch case:
                if dfs(i1, i2, i) and dfs(i1 + i, i2 + i, length - i):
                    return True
                # switch case:
                if dfs(i1, i2 + length - i, i) and dfs(i1 + i, i2, length - i):
                    return True

            return False

        ans = dfs(0, 0, len(s1))
        print(dfs.cache_info())
        dfs.cache_clear()
        return ans

# s1 = "great"
# s2 = "rgeat"
# s1 = "abcde"
# s2 = "caebd"
# s1 = "a"
# s2 = "a"
# s1 = "abb"
# s2 = "bba"
s1 = "eebaacbcbcadaaedceaaacadccd"
s2 = "eadcaacabaddaceacbceaabeccd"
print(Solution().isScramble(s1, s2))