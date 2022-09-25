from typing import List

class Solution:
    def numberOfGoodPaths(self, vals: List[int], edges: List[List[int]]) -> int:
        n = len(vals)

        # graph of the tree
        g = [[] for _ in range(n)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)

        # size of how many of values == vals[x]
        size = [1] * n
        # Union-Find Set
        f = list(range(n))

        # find set
        # find root of set
        def find(x):
            if f[x] != x:
                f[x] = find(f[x])
            return f[x]

        ans = n
        for vx, x in sorted(zip(vals, range(n))):
            # print("vx, x", vx, x)
            fx = find(x)
            for y in g[x]:
                fy = find(y)
                # already in union or x can't reach set of y
                if fy == fx or vals[fy] > vx:
                    # print("out", x, y)
                    continue
                # x reaches y and vals[x] == vals[root of y]
                if vals[fy] == vx:
                    # print(x, y)
                    ans += size[fx] * size[fy]
                    size[fx] += size[fy]
                # print("f[%d] = %d" % (y, fx))
                # when vals[fy] <= vals[x]
                # union set of y to x
                f[fy] = fx

        return ans

# vals = [1,3,2,1,3]
# edges = [[0,1],[0,2],[2,3],[2,4]]
# vals = [1,1,2,2,3]
# edges = [[0,1],[1,2],[2,3],[2,4]]
# vals = [1]
# edges = []
vals = [1,3,2,1,3]
edges = [[0,1],[0,2],[2,3],[2,4]]
print(Solution().numberOfGoodPaths(vals, edges))
