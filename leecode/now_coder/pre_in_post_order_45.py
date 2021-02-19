class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def threeOrders(self , root: TreeNode):
        def find(node: TreeNode):
            if not node:
                return
            
            preorder.append(node.val)
            find(node.left)
            inorder.append(node.val)
            find(node.right)
            postorder.append(node.val)
            return
        
        preorder = []
        inorder = []
        postorder = []

        find(root)
        return [preorder, inorder, postorder]
