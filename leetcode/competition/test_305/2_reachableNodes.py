from typing import List

class Solution:
    def reachableNodes(self, n: int, edges: List[List[int]], restricted: List[int]) -> int:
        visited = [False] * n
        restricted = set(restricted)
        g = [[] for _ in range(n)]
        for v, w in edges:
            g[v].append(w)
            g[w].append(v)

        visited[0] = True
        count = 1
        q = [0]

        while q:
            v = q.pop(0)
            for w in g[v]:
                if not visited[w]:
                    visited[w] = True
                    if w in restricted:
                        continue
                    q.append(w)
                    count += 1

        return count

# n = 7
# edges = [[0,1],[1,2],[3,1],[4,0],[0,5],[5,6]]
# restricted = [4,5]

n = 7
edges = [[0,1],[0,2],[0,5],[0,4],[3,2],[6,5]]
restricted = [4,2,1]

print(Solution().reachableNodes(n, edges, restricted))
