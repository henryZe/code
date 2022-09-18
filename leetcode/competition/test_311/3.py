from typing import List
from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
    def __str__(self) -> str:
        return str(self.val)

class Solution:
    def reverseOddLevels(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def print_array(arr):
            # print("level:")
            # for p in arr:
            #     print(p)
            return

        order = 1
        parent = [root]
        child = []
        while parent:
            if not parent[0].left:
                break

            print_array(parent)

            order *= -1
            for n in parent[::-1]:
                if order > 0:
                    child.append(n.left)
                    child.append(n.right)
                else:
                    child.append(n.right)
                    child.append(n.left)

            for _ in range(len(parent)):
                n = parent.pop(0)
                n.left = child.pop(0)
                parent.append(n.left)
                n.right = child.pop(0)
                parent.append(n.right)

        print_array(parent)
        return root

# root = [2,3,5,8,13,21,34]
# root = TreeNode(2,
#         TreeNode(3,
#             TreeNode(8),
#             TreeNode(13)),
#         TreeNode(5,
#             TreeNode(21),
#             TreeNode(34)))
# root = [0,1,2,0,0,0,0,1,1,1,1,2,2,2,2]
root = TreeNode(0,
        TreeNode(1,
            TreeNode(3,
                TreeNode(7),
                TreeNode(8)),
            TreeNode(4,
                TreeNode(9),
                TreeNode(10))),
        TreeNode(2,
            TreeNode(5,
                TreeNode(11),
                TreeNode(12)),
            TreeNode(6,
                TreeNode(13),
                TreeNode(14))))
Solution().reverseOddLevels(root)
# print(Solution().reverseOddLevels(root))
