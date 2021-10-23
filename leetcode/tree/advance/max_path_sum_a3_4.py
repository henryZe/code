# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    maxSum = float("-inf")

    def maxPathSum(self, root: TreeNode) -> int:

        def maxGain(node: TreeNode):
            if not node:
                return 0

            # get left & right subtree gain
            leftGain = max(0, maxGain(node.left))
            rightGain = max(0, maxGain(node.right))

            pathGain = leftGain + rightGain + node.val
            # update max sum
            self.maxSum = max(self.maxSum, pathGain)

            # return node max gain
            return node.val + max(leftGain, rightGain)

        maxGain(root)
        return self.maxSum


root = TreeNode(-10,TreeNode(9),TreeNode(20,TreeNode(15),TreeNode(7)))
print(Solution().maxPathSum(root))
