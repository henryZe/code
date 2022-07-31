from typing import List

def draw_path(node, edges):
    h = {node:0}
    cur_len = 0
    while True:
        node = edges[node]
        if node == -1:
            break
        if node in h:
            break
        cur_len += 1
        h[node] = cur_len

    return h

class Solution:
    def closestMeetingNode(self, edges: List[int], node1: int, node2: int) -> int:
        h_node1 = draw_path(node1, edges)
        h_node2 = draw_path(node2, edges)
        path_len = float("inf")
        res = -1

        for key in h_node1.keys():
            if key in h_node2:
                cur_len = max(h_node1[key], h_node2[key])
                if cur_len < path_len:
                    res = key
                    path_len = cur_len
                elif cur_len == path_len and key < res:
                    res = key

        return res

# edges = [2,2,3,-1]
# node1 = 0
# node2 = 1
# edges = [1,2,-1]
# node1 = 0
# node2 = 2
edges = [4,4,8,-1,9,8,4,4,1,1]
node1 = 5
node2 = 6
print(Solution().closestMeetingNode(edges, node1, node2))
