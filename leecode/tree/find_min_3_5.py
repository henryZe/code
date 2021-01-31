class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

    def __str__(self):
        return "[{}:l {} r {}]".format(self.val, self.left, self.right)

class Solution:
    def kthSmallest(self, root: TreeNode, k: int) -> int:
        def inorder(r):
            return inorder(r.left) + [r.val] + inorder(r.right) if r else []

        return inorder(root)[k - 1]

    def kthSmallest_iter(self, root: TreeNode, k: int) -> int:
        stack = []

        while True:
            while root:
                stack.append(root)
                root = root.left

            root = stack.pop()
            k -= 1
            if not k:
                return root.val
            
            root = root.right

obj = Solution()

root_rr = TreeNode(2)
root_l = TreeNode(1, None, root_rr)
root_r = TreeNode(4)
root = TreeNode(3, root_l, root_r)

print(obj.kthSmallest_iter(root, 3))
