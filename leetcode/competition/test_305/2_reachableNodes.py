from typing import List

class Solution:
    def reachableNodes(self, n: int, edges: List[List[int]], restricted: List[int]) -> int:
        visited = [False] * n
        e_visited = [False] * (n - 1)

        visited[0] = True
        count = 1
        q = [0]

        while q:
            v = q.pop(0)
            for i in range(n - 1):
                if e_visited[i] == False:
                    if v in edges[i]:
                        e_visited[i] = True
                        w = edges[i][0] if edges[i][0] != v else edges[i][1]
                        if w in restricted:
                            continue

                        visited[w] = True
                        count += 1
                        q.append(w)

        return count

# n = 7
# edges = [[0,1],[1,2],[3,1],[4,0],[0,5],[5,6]]
# restricted = [4,5]

n = 7
edges = [[0,1],[0,2],[0,5],[0,4],[3,2],[6,5]]
restricted = [4,2,1]

print(Solution().reachableNodes(n, edges, restricted))
