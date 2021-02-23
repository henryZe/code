class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random

    def __str__(self):
        return "{} -> {}".format(self.val, self.next)

class Solution:
    def __init__(self):
        self.visitedHash = {}

    def getClonedNode(self, node:'Node') -> 'Node':
        if node:
            if node in self.visitedHash:
                return self.visitedHash[node]
            else:
                self.visitedHash[node] = Node(node.val)
                return self.visitedHash[node]

        return None

    def copyRandomList(self, head: 'Node') -> 'Node':
        if not head:
            return None

        old_node = head
        new_node = Node(old_node.val, None, None)
        self.visitedHash[old_node] = new_node

        while old_node:
            new_node.next = self.getClonedNode(old_node.next)
            new_node.random = self.getClonedNode(old_node.random)

            old_node = old_node.next
            new_node = new_node.next

        return self.visitedHash[head]


obj = Solution()

n0 = Node(7)
n1 = Node(13)
n2 = Node(11)
n3 = Node(10)
n4 = Node(1)

n0.next = n1
n1.next = n2
n2.next = n3
n3.next = n4

n0.random = None
n1.random = n0
n2.random = n4
n3.random = n2
n4.random = n0

print(obj.copyRandomList(n0))
