from typing import List
import collections

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

    def __str__(self):
        return "[{}:l {} r {}]".format(self.val, self.left, self.right)

class Solution:
    def zigzagLevelOrder(self, root: TreeNode) -> List[List[int]]:
        l = []
        if root == None:
            return l

        nodeQueue = collections.deque([root])
        reverse = False

        while len(nodeQueue):
            temp = []
            size = len(nodeQueue)
            for i in range(size):
                node = nodeQueue.popleft()
                temp.append(node.val)

                if node.left:
                    nodeQueue.append(node.left)
                if node.right:
                    nodeQueue.append(node.right)

            if reverse:
                temp.reverse()
            l.append(temp)
            reverse = not reverse

        return l

obj = Solution()

root_rl = TreeNode(15)
root_rr = TreeNode(7)
root_l = TreeNode(9)
root_r = TreeNode(20, root_rl, root_rr)
root = TreeNode(3, root_l, root_r)

print(obj.zigzagLevelOrder(root))
