from typing import List

class Solution:
    def edgeScore(self, edges: List[int]) -> int:
        h = {}
        max_score = 0
        max_idx = float("inf")

        for i, edge in enumerate(edges):
                if edge not in h:
                        h[edge] = i
                else:
                        h[edge] += i
                if h[edge] > max_score:
                        max_score = h[edge]
                        max_idx = edge
                elif h[edge] == max_score:
                        max_idx = min(edge, max_idx)

        return max_idx

edges = [1,0,0,0,0,7,7,5]
edges = [2,0,0,2]
edges = [3,3,3,0]
print(Solution().edgeScore(edges))
