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

### 3.4 二叉搜索树

* 非空左子树所有键值小于其根结点的键值
* 非空右子树所有键值大于其根结点的键值
* 左右子树都是二叉搜索树

- 操作函数：
    * find
    * findMin
    * findMax
    * insert
    * delete:
        1. 该结点左右子树皆为空，直接删除
        2. 该结点只有一个儿子，用儿子结点直接替换
        3. 该结点有两个儿子，实质是使用左子树最大值或者右子树最小值替换被删除结点，递归删除该左子树最大值/右子树最小值结点

### 3.5 平衡二叉树

* Balance Factor: 任意结点左右子树高度差的绝对值不超过1
* 一颗高度为 h 的平衡二叉树，最少结点数为 Nmin(h) = Nmin(h-1) + Nmin(h-2) + 1

![balance_tree](./pic/balance_tree.png)

* 平衡二叉树的调整
    - RR旋转（麻烦结点在发现者的右子树的右边）
    ![rr_rotate](./pic/rr_rotate.png)

    - LL旋转（麻烦结点在发现者的左子树的左边）
    ![ll_rotate](./pic/ll_rotate.png)

    - LR旋转（麻烦结点在发现者的左子树的右边）
    ![lr_rotate](./pic/lr_rotate.png)

    - RL旋转（麻烦结点在发现者的右子树的左边）
    ![rl_rotate](./pic/rl_rotate.png)

### 3.6 堆

* 大顶堆/小顶堆，属于完全二叉树，堆的路径呈现单调性
* 堆操作

~~~
create
IsFull
IsEmpty

Insert
DeleteMax
~~~

* create heap 如果使用 insert 方法，时间复杂度 O(n * logn)，最坏情况是各结点的高度之和

### 3.7 哈夫曼树

* WPL（带权路径长度）：设二叉树有n个叶子结点，每个叶子结点带有权值W(k)，从根结点到每个叶子结点的长度为l(k)，则每个叶子结点的带权路径长度之和 WPL = Sum(W(k) * l(k))

* WPL 最小的二叉树 即是 哈夫曼树

* 每次把权值最小的两棵二叉树合并

* 特点：
    - 没有度为1的结点
    - n 个叶子结点的哈夫曼树共有 2n-1 个结点
    - 哈夫曼树的任意非叶子节点的左右子树交换后仍是哈夫曼树
    - 对同一组权值，存在不同构的哈夫曼树

### 3.8 哈夫曼编码

* 不等长编码避免二义性：任何字符的编码都不是另一字符编码的前缀(prefix code), 可使用 trie tree 进行前缀检查

* 用二叉树进行编码：
    1. 左右分支：0, 1
    2. 字符只在叶子结点上

### 3.9 并查集

* 集合操作，其中关注：并集操作，查找操作
* 双亲表示法
* 集合操作：

~~~
Find
Union
~~~

* Union 为了改善合并以后的查找性能，可以采用小的集合合并到相对大的集合中，按秩归并，最坏情况下的树高：O(logN)
* Find 为了改善查找性能，采用**路径压缩**思路

## 4 图 graph

### 4.1 定义

* 表示**多对多**的关系

* 包含：
    1. 一组顶点：通常用 V(Vertex) 表示顶点集合
    2. 一组边：通常用 E(Edge) 表示边的集合
        * (v, w) 表示无向边
        * <v, w> 表示有向边，v -> w
        * 不考虑重边和自回路

* 操作集：

~~~
create
insertVertex
insertEdge
DFS
BFS
shortestPath
MST(minimum spanning tree)
~~~

### 4.2 图的表示

* 邻接矩阵

好处：
    1. 无向图：对应行/列非0元素的个数
    2. 有向图：对应行非0元素的个数是 “出度” ，对应列非0元素的个数是 “入度”

~~~
G[i][j] =   1 (若 <Vi, Vj> 是 G 中的边)
            0 (否则)
~~~

缺点：
    1. 浪费空间，存稀疏图（点很多而边很少）有大量无效元素
    2. 浪费时间，稀疏图

* 邻接表

好处：
    1. 节约稀疏图的空间（需要N个头指针 + 2E个结点（每个结点至少2 fields））

### 4.3 图的遍历

* DFS 复杂度
    1. 邻接表存储，则 O(N + E)
    2. 邻接矩阵存储，则 O(N * N)

~~~ C
void DFS(Vertex V)
{
    visited[V] = true;

    for (V 的每个邻接点 W)
        if (!visited[W])
            DFS(W);
}
~~~

* BFS

~~~ C

~~~
