# 数据结构

## 1 基本概念

### 1.1 渐进复杂度

* 1, logN, N, N*logN, N^2, N^3, 2^N, N!

## 2 线性结构

### 2.1 线性表及其实现

* 广义表

![linear_list](./pic/Generalized_List.png)

* 广义表是线性表的推广
* 广义表中的元素不仅可以是单元素也可以是另一个广义表

~~~ C
struct Gnode {
    int tag;	// 0 means data, 1 means subList
    union {
        elementType data;
        struct Gnode *subList;
    } uRegion;
    struct Gnode *next;
};
~~~

* 多重链表

![multiple_linked_list](./pic/multiple_linked_list.png)

![multiple_linked_list2](./pic/multiple_linked_list2.png)

~~~ C
// 抽象类型
struct multi_linked {
    struct multi_linked *down;
    union uRegion;
    struct multi_linked *right;
};

struct TermData {
    int row;
    int col;
    int val;
};
// Term
struct multi_linked_node {
    struct multi_linked_node *down;
    union {
        struct TermData data;
        struct head *next;
    } uRegion;
    struct multi_linked_node *right;
};
// Head
struct head {
    struct multi_linked_node *down;
    union {
        struct TermData data;
        struct head *next;
    } uRegion;
    struct multi_linked_node *right;
};
~~~

### 2.2 堆栈 stack

### 2.3 队列 queue

## 3 树

### 3.1 树的术语

* 一棵拥有 N 个结点的树，有(N - 1)条边
* 结点的度：结点的子树个数
* 树的度：树的所有结点中最大的度数
* 叶结点：度为0的结点
* 结点的层次：规定根结点在1层，其他任一结点的层数是其父结点的层数加一
* 树的深度：树中所有结点中的最大层次是这棵树的深度

- 儿子兄弟表示法

~~~ C
struct tree_node {
    struct tree_node *firstChild;
    struct tree_node *nextSibling;
};
~~~

- 任意一棵树都可以通过儿子兄弟表示法，使用二叉树来实现

![tree](./pic/tree.jpg)

### 3.2 二叉树的存储结构

- 顺序存储结构
    * 完全二叉树，父节点[i/2]，左孩子[2*i]，右孩子[2*i + 1]
    * 一般二叉树也可以，但会造成空间浪费

- 链表存储

### 3.3 二叉树的遍历

* 前序/中序/后序遍历
* 层序遍历
