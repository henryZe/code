from typing import List

class TreeNode:
    def __init__(self, val):
        self.val = ord(val) - ord('a')
        self.leaves = [None] * 26
        self.count = 1

class Solution:
    def idx(self, c):
        return ord(c) - ord('a')

    def sumPrefixScores(self, words: List[str]) -> List[int]:
        d_tree = TreeNode("A")
        for word in words:
            root = d_tree
            for c in word:
                if root.leaves[self.idx(c)]:
                    root = root.leaves[self.idx(c)]
                    root.count += 1
                else:
                    root.leaves[self.idx(c)] = TreeNode(c)
                    root = root.leaves[self.idx(c)]

        res = []
        for word in words:
            root = d_tree
            cur = 0
            for c in word:
                cur += root.leaves[self.idx(c)].count
                root = root.leaves[self.idx(c)]
            res.append(cur)

        return res

words = ["abc","ab","bc","b"]
# words = ["abcd"]
print(Solution().sumPrefixScores(words))