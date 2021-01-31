from typing import List

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

    def __str__(self):
        return "[{}:l {} r {}]".format(self.val, self.left, self.right)

class Solution:
    def inorderTraversal(self, root: TreeNode) -> List[int]:
        def myInorder(l: List[int], root: TreeNode):
            if root == None:
                return

            myInorder(l, root.left)
            l.append(root.val)
            myInorder(l, root.right)

            return l

        l = []
        myInorder(l, root)
        return l

obj = Solution()

root_rl = TreeNode(15)
root_rr = TreeNode(7)
root_l = TreeNode(9)
root_r = TreeNode(20, root_rl, root_rr)
root = TreeNode(3, root_l, root_r)

print(obj.inorderTraversal(root))
