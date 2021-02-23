from typing import List
import collections

class Solution:
    # BFS
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        # out degree
        outdeg = collections.defaultdict(list)
        # in degree
        indeg = [0] * numCourses
        result = []

        for r in prerequisites:
            outdeg[r[1]].append(r[0])
            indeg[r[0]] += 1

        q = collections.deque([])
        for i in range(numCourses):
            if indeg[i] == 0:
                q.append(i)

        while q:
            node = q.popleft()
            result.append(node)

            for o in outdeg[node]:
                indeg[o] -= 1
                if indeg[o] == 0:
                    q.append(o)

        if len(result) == numCourses:
            return result
        else:
            return []


numCourses = 4
prerequisites = [[1,0],[2,0],[3,1],[3,2]]
print(Solution().findOrder(numCourses, prerequisites))
