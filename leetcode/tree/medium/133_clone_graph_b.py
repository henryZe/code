import collections

class Node:
    def __init__(self, val = 0, neighbors = None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []

class Solution:
    # bfs
    def cloneGraph(self, node: 'Node') -> 'Node':
        if not node:
            return node

        visited = {}
        queue = collections.deque([node])
        visited[node] = Node(node.val, [])

        while queue:
            n = queue.popleft()
            for neighbor in n.neighbors:
                if neighbor not in visited:
                    queue.append(neighbor)
                    visited[neighbor] = Node(neighbor.val, [])
                visited[n].neighbors.append(visited[neighbor])

        return visited[node]
