from typing import List
import collections

class Solution:
    if 0:
        # dfs
        def findCircleNum(self, isConnected: List[List[int]]) -> int:
            def dfs(c: int):
                visited.add(c)
                for i in range(cities):
                    if i not in visited and isConnected[c][i]:
                        dfs(i)

            cities = len(isConnected)
            visited = set()
            circles = 0

            for c in range(cities):
                if c not in visited:
                    circles += 1
                    dfs(c)

            return circles

    if 1:
        # bfs
        def findCircleNum(self, isConnected: List[List[int]]) -> int:
            visited = set()
            cities = len(isConnected)
            circles = 0

            for c in range(cities):
                if c not in visited:
                    que = collections.deque([c])
                    while que:
                        city = que.popleft()
                        for i in range(cities):
                            if isConnected[city][i] and i not in visited:
                                visited.add(i)
                                que.append(i)
                    circles += 1

            return circles


isConnected = [
    [1,1,0],
    [1,1,0],
    [0,0,1]
]

print(Solution().findCircleNum(isConnected))
