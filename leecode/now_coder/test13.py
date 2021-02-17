# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

#
# 
# @param root TreeNode类 
# @return int整型
#
class Solution:
    def maxDepth(self , root ) -> int:
        # write code here
        def dfs(node: TreeNode) -> int:
            if not node:
                return 0
            
            l = dfs(node.left) + 1
            r = dfs(node.right) + 1
            
            return max(l, r)
        
        return dfs(root)