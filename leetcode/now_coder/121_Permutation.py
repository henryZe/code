# -*- coding:utf-8 -*-
class Solution:
    def Permutation(self, ss):
        n = len(ss)
        ss_set = set(ss)
        n_set = len(ss_set)
        ss_dict = {}
        for s in ss:
            if s not in ss_dict:
                ss_dict[s] = 1
            else:
                ss_dict[s] += 1
        res = []

        def dfs(res, cur, pos):
            if pos == n:
                res.append("".join(cur))
                return

            for c in ss_set:
                if ss_dict[c] != 0:
                    ss_dict[c] -= 1
                    newStr = cur[:]
                    newStr.append(c)
                    dfs(res, newStr, pos + 1)
                    ss_dict[c] += 1

        dfs(res, [], 0)
        return res

res = Solution().Permutation("abc")
print(res)