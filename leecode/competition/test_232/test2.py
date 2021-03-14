from typing import List
import collections

class Solution:
    def findCenter(self, edges: List[List[int]]) -> int:
        dict = collections.defaultdict(set)
        for edge in edges:
            dict[edge[0]].add(edge[1])
            dict[edge[1]].add(edge[0])

        for key in dict.keys():
            if len(dict[key]) == len(dict) - 1:
                return key

        return -1

edges = [[1,2],[5,1],[1,3],[1,4]]
print(Solution().findCenter(edges))
