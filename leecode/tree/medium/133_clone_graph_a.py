class Node:
    def __init__(self, val = 0, neighbors = None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []

class Solution:
    def __init__(self):
        self.visited = {}

    # dfs
    def cloneGraph(self, node: 'Node') -> 'Node':
        if not node:
            return node

        if node in self.visited:
            return self.visited[node]

        cloneNode = Node(node.val, [])
        self.visited[node] = cloneNode

        for neighbor in node.neighbors:
            cloneNode.neighbors.append(self.cloneGraph(neighbor))

        return cloneNode
