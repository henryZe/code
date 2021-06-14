# Advanced Data Structures and Algorithm Analysis

## 1 AVL tree, Splay tree, Amortized analysis

### 1.1 AVL Trees

Target: Speed up searching (with insertion and deletion, Dynamic Searching)

Definition: An empty binary tree is height balanced (The height of an empty tree is defined to be -1, means `N(-1) = 0, N(0) = 1`). If `T` is a nonempty binary tree with `Tl` and `Tr` as its left and right subtree, then `T` is height balanced iff(if and only if):
1. `Tl` and `Tr` are height balanced (recursive definition), and
2. `|hl - hr| <= 1` where `hl` and `hr` are the heights of `Tl` and `Tr`, respectively.

Definition: The balance factor `BF = hl - hr`. In an AVL tree, BF = -1, 0 or 1.

rotation: RR, LL, LR, RL

LR can be considered as the combination of two single rotations (RR & LL). So it's also called a double rotation.

Let `Nh` be the minimum number of nodes in a height balanced tree of height `h`. Then the tree must be `Nh = Nh-1 + Nh-2 + 1`.

### 1.2 Splay Trees

Target: Any `M` consecutive tree operations starting from an empty tree take at most `O(M logN)` time.

Idea: After a node is accessed, it is pushed to the root by a series of AVL tree rotations.

Splaying not only moves the accessed node to the root, but also roughly halves the depth of most nodes on the path.

Rotation:
1. zig-zag: double rotation
2. zig-zig: single rotation

![splay_tree_rotate](./pic/splay_tree_rotate.png)

Deletion:
1. Find X
2. Remove X
3. FindMax(`Tl`)
4. Make `Tr` the right child of the root of `Tl`.
