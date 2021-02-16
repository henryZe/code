from typing import List
import collections

class Solution:
    # BFS
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # out degree
        outdeg = collections.defaultdict(list)
        # in degree
        indeg = [0] * numCourses
        result = 0

        for r in prerequisites:
            outdeg[r[1]].append(r[0])
            indeg[r[0]] += 1

        q = collections.deque([])
        for i in range(numCourses):
            if indeg[i] == 0:
                q.append(i)

        while q:
            node = q.popleft()
            result += 1

            for o in outdeg[node]:
                indeg[o] -= 1
                if indeg[o] == 0:
                    q.append(o)

        return result == numCourses


numCourses = 2
prerequisites = [[0,1]]
print(Solution().canFinish(numCourses, prerequisites))
