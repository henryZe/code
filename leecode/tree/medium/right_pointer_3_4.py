from typing import List

class Node:
    def __init__(self, val: int = 0, left: 'Node' = None, right: 'Node' = None, next: 'Node' = None):
        self.val = val
        self.left = left
        self.right = right
        self.next = next

    def __str__(self):
        return "[{}:l {} r {} n {}]".format(self.val, self.left, self.right, self.next)

class Solution:
    def connect(self, root: 'Node') -> 'Node':
        if not root:
            return root
        
        l = [root]
        while l:
            size = len(l)

            for i in range(size):
                node = l.pop(0)

                if i < size - 1:
                    node.next = l[0]
                # else:
                #     node.next = None
                
                if node.left:
                    l.append(node.left)
                if node.right:
                    l.append(node.right)

        return root

obj = Solution()

root_rl = Node(15)
root_rr = Node(7)
root_l = Node(9)
root_r = Node(20, root_rl, root_rr)
root = Node(3, root_l, root_r)

print(obj.connect(root))
