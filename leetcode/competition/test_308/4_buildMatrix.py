from typing import List

class Solution:
    def buildMatrix(self, k: int, rowConditions: List[List[int]], colConditions: List[List[int]]) -> List[List[int]]:
        def topo_sort(k, requisite):
            in_degree = [0] * (k + 1)
            in_degree[0] = -1
            g = {}
            for v, w in requisite:
                if v in g:
                    g[v].append(w)
                else:
                    g[v] = [w]
                in_degree[w] += 1

            q = []
            for w in range(1, k + 1):
                if in_degree[w] == 0:
                    q.append(w)

            res = []
            while q:
                v = q.pop(0)
                res.append(v)
                if v in g:
                    for w in g[v]:
                        in_degree[w] -= 1
                        if in_degree[w] == 0:
                            q.append(w)

            if len(res) != k:
                return None

            return res

        row = topo_sort(k, rowConditions)
        if row == None:
            return []

        col = topo_sort(k, colConditions)
        if col == None:
            return []

        ans = []
        for i in range(k):
            ans.append([0] * k)

        col_dict = {}
        for i, c in enumerate(col):
            col_dict[c] = i
        for i, r in enumerate(row):
            ans[i][col_dict[r]] = r
        return ans


k = 3
rowConditions = [[1,2],[3,2]]
colConditions = [[2,1],[3,2]]
print(Solution().buildMatrix(k, rowConditions, colConditions))
