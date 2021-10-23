class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def minDiffInBST(self, root: TreeNode) -> int:
        prev = -1
        diff = float("inf")

        # left -> root -> right -> parent root -> parent right -> ...
        def inOrder(root: TreeNode) -> int:
            if not root:
                return

            nonlocal prev, diff

            inOrder(root.left)
            if prev != -1:
                # update diff
                diff = min(diff, root.val - prev)
            # update prev
            prev = root.val
            inOrder(root.right)

            return

        inOrder(root)
        return diff

root = TreeNode(27, None, TreeNode(34, None, TreeNode(58, TreeNode(50, TreeNode(44, None, None), None), None)))
print(Solution().minDiffInBST(root))
