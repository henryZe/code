import collections

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class BSTIterator:
    def inOrder(self, node: TreeNode):
        if not node:
            return

        self.inOrder(node.left)
        self.queue.append(node.val)
        self.inOrder(node.right)
        return

    def __init__(self, root: TreeNode):
        self.queue = collections.deque()
        self.inOrder(root)

    def next(self) -> int:
        return self.queue.popleft()

    def hasNext(self) -> bool:
        return len(self.queue) > 0


root = TreeNode(7, TreeNode(3), TreeNode(15, TreeNode(9), TreeNode(20)))
obj = BSTIterator(root)
print(obj.next())
print(obj.hasNext())
