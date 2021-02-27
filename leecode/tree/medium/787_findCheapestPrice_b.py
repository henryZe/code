from typing import List

# Dijkstra 算法
# 在 Dijkstra 算法中，借助优先级队列持续搜索花费最低的下一个城市。
# 如果查找到某个城市，它原本的路线成本更低或者中转次数过多，则无需再搜索它。
# 否则，如果搜索到目的城市，那么当前花费就是最低成本，因为每次最先搜索的就是最低成本航线。
# 如果从某城市出发的航线花费更低，则将该节点加入到优先级队列用于搜索。

class Solution:
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, K: int) -> int:
        graph = {}
        for s, d, w in flights:
            graph[s][d] = w
        

        best = {}
        for _ in n:

        
        
        return n


n = 3
edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0
dst = 2
k = 1
print(Solution().findCheapestPrice(n, edges, src, dst, k))
