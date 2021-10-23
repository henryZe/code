import collections

class TreeNode:
    def __init__(self, x: int, left: 'TreeNode' = None, right: 'TreeNode' = None):
        self.val = x
        self.left = left
        self.right = right

class Solution:
    hashParent = {}

    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        def dfs(root, parent):
            if not root:
                return

            self.hashParent[root] = parent
            dfs(root.left, root)
            dfs(root.right, root)
            return

        dfs(root, None)

        que = collections.deque([])
        while p:
            que.append(p)
            p = self.hashParent[p]

        while q:
            if q in que:
                return q
            else:
                q = self.hashParent[q]

        return None


p = TreeNode(5, TreeNode(6), TreeNode(2, TreeNode(7), TreeNode(4)))
q = TreeNode(1, TreeNode(0), TreeNode(8))
root = TreeNode(3, p, q)

res = Solution().lowestCommonAncestor(root, p, q)
if res:
    print(res.val)
else:
    print("no common ancestor")
