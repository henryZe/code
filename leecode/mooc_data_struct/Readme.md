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





