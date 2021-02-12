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

    def copyRandomList(self, head: 'Node') -> 'Node':
        if head == None:
            return None

        if head in self.visitedHash:
            return self.visitedHash[head]

        node = Node(head.val, None, None)
        self.visitedHash[head] = node

        node.next = self.copyRandomList(head.next)
        node.random = self.copyRandomList(head.random)

        return node


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
