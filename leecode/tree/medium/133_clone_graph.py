class Node:
    def __init__(self, val = 0, neighbors = None):
        self.val = val
        self.neighbors = neighbors if neighbors is not None else []

    def __str__(self):
        str_ins = "{} -> ".format(self.val)
        for node in self.neighbors:
            str_ins.join("{} ".format(node.val))
        return str_ins


class Solution:
    def cloneGraph(self, node: 'Node') -> 'Node':
        return node

n1 = Node(1)

[2,4]
n2 = Node(2, [1,3])
n3 = Node(3, [2,4])
n4 = Node(4, [1,3])

new_n1 = Solution().cloneGraph(n1)
print(new_n1)
