from typing import List
import collections

class Solution:
    def findCircleNum(self, isConnected: List[List[int]]) -> int:
        def find(index: int) -> int:
            if parent[index] != index:
                # update to grand parent
                parent[index] = find(parent[index])
            print(parent)
            return parent[index]
        
        def union(index1: int, index2: int):
            parent[find(index1)] = find(index2)
        
        provinces = len(isConnected)
        parent = list(range(provinces))
        print(parent)
        
        for i in range(provinces):
            for j in range(i + 1, provinces):
                if isConnected[i][j] == 1:
                    union(i, j)
        
        circles = sum(parent[i] == i for i in range(provinces))
        return circles


isConnected = [
    [1,0,0,0,0,0,0,0,0,1,0,0,0,0,0],
    [0,1,0,1,0,0,0,0,0,0,0,0,0,1,0],
    [0,0,1,0,0,0,0,0,0,0,0,0,0,0,0],
    [0,1,0,1,0,0,0,1,0,0,0,1,0,0,0],
    [0,0,0,0,1,0,0,0,0,0,0,0,1,0,0],
    [0,0,0,0,0,1,0,0,0,0,0,0,0,0,0],
    [0,0,0,0,0,0,1,0,0,0,0,0,0,0,0],
    [0,0,0,1,0,0,0,1,1,0,0,0,0,0,0],
    [0,0,0,0,0,0,0,1,1,0,0,0,0,0,0],
    [1,0,0,0,0,0,0,0,0,1,0,0,0,0,0],
    [0,0,0,0,0,0,0,0,0,0,1,0,0,0,0],
    [0,0,0,1,0,0,0,0,0,0,0,1,0,0,0],
    [0,0,0,0,1,0,0,0,0,0,0,0,1,0,0],
    [0,1,0,0,0,0,0,0,0,0,0,0,0,1,0],
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,1]
]

print(Solution().findCircleNum(isConnected))
