from typing import List
import collections

# Dijkstra 算法
# 在 Dijkstra 算法中，借助优先级队列持续搜索花费最低的下一个城市。
# 如果查找到某个城市，它原本的路线成本更低或者中转次数过多，则无需再搜索它。
# 否则，如果搜索到目的城市，那么当前花费就是最低成本，因为每次最先搜索的就是最低成本航线。
# 如果从某城市出发的航线花费更低，则将该节点加入到优先级队列用于搜索。

class Solution:
    def findCheapestPrice(self, n: int, flights: List[List[int]], src: int, dst: int, K: int) -> int:
        graph = collections.defaultdict(dict)
        for s, d, w in flights:
            graph[s][d] = w

        best = {}
        # cost, k, place
        pq = [(0, 0, src)]
        while pq:
            cost, k, place = pq.popleft()
            print("cost {} k {} place {}".format(cost, k, place))

            if k > K + 1 or cost > best.get((k, place), float("inf")):
                continue
            if place == dst:
                # best result
                return cost

            for dest, weight in graph[place].items():
                newcost = cost + weight
                if newcost < best.get((k + 1, dest), float("inf")):
                    print("newcost {} place {} dest {}".format(newcost, place, dest))

                    pq.append((newcost, k + 1, dest))
                    best[k + 1, dest] = newcost

        # can't reach dst
        return -1


n = 3
edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0
dst = 2
k = 1
print(Solution().findCheapestPrice(n, edges, src, dst, k))
