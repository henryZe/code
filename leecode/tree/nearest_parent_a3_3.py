class TreeNode:
    def __init__(self, x: int, left: 'TreeNode' = None, right: 'TreeNode' = None):
        self.val = x
        self.left = left
        self.right = right

class Solution:
    res = None

    # (flson && frson) || ((x = p || x = q) && (flson || frson))
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        def dfs(root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> bool:
            if root == None:
                return False

            lson = dfs(root.left, p, q)
            rson = dfs(root.right, p, q)

            if (lson and rson) or ((lson or rson) and ((root.val == p.val) or (root.val == q.val))):
                self.res = root

            return lson or rson or (root.val == p.val) or (root.val == q.val)

        dfs(root, p, q)
        return self.res

p = TreeNode(5, TreeNode(6), TreeNode(2, TreeNode(7), TreeNode(4)))
q = TreeNode(1, TreeNode(0), TreeNode(8))
root = TreeNode(3, p, q)

res = Solution().lowestCommonAncestor(root, p, q)
if res:
    print(res.val)
else:
    print("no common root")
