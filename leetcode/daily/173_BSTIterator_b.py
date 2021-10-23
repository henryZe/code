import collections

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class BSTIterator:
    def __init__(self, root: TreeNode):
        self.cur = root
        self.stack = []

    def next(self) -> int:
        cur = self.cur
        while cur:
            self.stack.append(cur)
            cur = cur.left

        cur = self.stack.pop()
        self.cur = cur.right
        return cur.val

    def hasNext(self) -> bool:
        if self.cur:
            return True
        return len(self.stack) > 0


root = TreeNode(7, TreeNode(3), TreeNode(15, TreeNode(9), TreeNode(20)))
obj = BSTIterator(root)
print(obj.next())
print(obj.next())
print(obj.hasNext())
print(obj.next())
print(obj.hasNext())
print(obj.next())
print(obj.hasNext())
