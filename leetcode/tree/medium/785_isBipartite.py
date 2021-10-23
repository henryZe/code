# 二分图特点
# 1. 所有点将被分成独立的集合
# 2. 每条边两端的点一定属于不同的集合
# 3. 可能存在孤点

# 二分图 -> 着色 -> 遍历（深度）
# 1. 在栈不为空的情况下进入循环，将栈顶点出栈
# 2. 对所有栈顶结点的相连结点着色，如果发生错误返回 False
# 3. 将着色正确的结点入栈
# 4. 继续循环
# 5. 若正常完成循环，返回 True

import collections
from typing import List

class Solution:
    def isBipartite(self, graph: List[List[int]]) -> bool:
        n = len(graph)
        UNCOLORED, RED, GREEN = 0, 1, 2
        color_graph = [UNCOLORED] * n

        def dfs(index: int, c: int) -> bool:
            color_graph[index] = c
            color = (GREEN if c == RED else RED)

            for neighbor in graph[index]:
                if color_graph[neighbor] == UNCOLORED:
                    valid = dfs(neighbor, color)
                    if not valid:
                        return False
                elif color_graph[neighbor] != color:
                    return False
            
            return True

        for i in range(n):
            if color_graph[i] == UNCOLORED:
                valid = dfs(i, RED)
                if not valid:
                    return False

        return True


# graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
# graph = [[1,3],[0,2],[1,3],[0,2]]
graph = [[2,3,5,6,7,8,9],[2,3,4,5,6,7,8,9],[0,1,3,4,5,6,7,8,9],[0,1,2,4,5,6,7,8,9],[1,2,3,6,9],[0,1,2,3,7,8,9],[0,1,2,3,4,7,8,9],[0,1,2,3,5,6,8,9],[0,1,2,3,5,6,7],[0,1,2,3,4,5,6,7]]
print(Solution().isBipartite(graph))
