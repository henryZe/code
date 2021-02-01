# Note

## 1 数据结构

### 1.1 链表

* reverse list

~~~ C
/**
 * struct ListNode {
 *  int val;
 *  struct ListNode *next;
 * };
 */
struct ListNode* ReverseList(struct ListNode* pHead) {
    struct ListNode *pReverseHead = NULL;
    struct ListNode *pNode = pHead;
    struct ListNode *pPrev = NULL;
    struct ListNode *pNext = NULL;
 
    while (pNode != NULL) {
        pNext = pNode->next;
         
        if (pNext == NULL)
            pReverseHead = pNode;
        
        // reverse list
        pNode->next = pPrev;
        
        pPrev = pNode;
        pNode = pNext;
    }
     
    return pReverseHead;
}
~~~

### 1.2 图

#### 1.2.1 Tree

* 中序遍历

~~~ C
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
void inorder(struct TreeNode* root, int *res, int* returnSize)
{
    if (!root) {
        return;

    } else {
        inorder(root->left, res, returnSize);

        res[*returnSize] = root->val;
        *returnSize += 1;

        inorder(root->right, res, returnSize);
    }
}

// recursion
int* inorderTraversal_recursion(struct TreeNode* root, int* returnSize)
{
    int *res = malloc(500 * sizeof(int));
    *returnSize = 0;
    inorder(root, res, returnSize);
    return res;
}

// iteration
int* inorderTraversal(struct TreeNode* root, int* returnSize)
{
    int top = 0;
    int *res = malloc(500 * sizeof(int));
    struct TreeNode *stk[500];

    *returnSize = 0;

    while (root || top > 0) {
        // put left tree into stack
        while (root) {
            stk[top++] = root;
            root = root->left;
        }

        // push root node
        root = stk[--top];
        res[(*returnSize)++] = root->val;
        
        // right tree iteration
        root = root->right;
    }

    return res;
}
~~~

* 二叉树的锯齿形层次遍历(tree_sort.c)

* 从前序与中序遍历序列构造二叉树()

## 2 算法

### 2.1 排序

#### 2.1.1 qsort

~~~ C
int compare(const void *a, const void *b)
{
    return *(int *)a > *(int *)b ? 1 : -1;
}
 
int* MySort(int* arr, int arrLen, int* returnSize ) {
    // write code here
    qsort(arr, arrLen, sizeof(int), compare);
    if (returnSize)
        *returnSize = arrLen;
     
    return arr;
}
~~~

### 2.2 递归 & 遍历

* 递归: A call A
* 遍历: A while B

### 2.3 动态规划

* 动态规划算法通常用于求解具有某种最优性质的问题。
* 在这类问题中，可能会有许多可行解。每一个解都对应于一个值，我们希望找到具有最优值的解。
* 动态规划算法与分治法类似，其基本思想也是将待求解问题分解成若干个子问题，先求解子问题，然后从这些子问题的解得到原问题的解。
* 与分治法不同的是，适合于用动态规划求解的问题，经分解得到子问题往往不是互相独立的。若用分治法来解这类问题，则分解得到的子问题数目太多，有些子问题被重复计算了很多次。
* 如果我们能够保存已解决的子问题的答案，而在需要时再找出已求得的答案，这样就可以避免大量的重复计算，节省时间。我们可以用一个表来记录所有已解的子问题的答案。不管该子问题以后是否被用到，只要它被计算过，就将其结果填入表中。这就是动态规划法的基本思路。
* 具体的动态规划算法多种多样，但它们具有相同的填表格式。

### 2.4 贪心算法

* 贪心算法（又称贪婪算法）是指，在对问题求解时，总是做出在当前看来是最好的选择。也就是说，不从整体最优上加以考虑，算法得到的是在某种意义上的局部最优解

* 贪心算法一般按如下步骤进行：
    1. 建立数学模型来描述问题
    2. 把求解的问题分成若干个子问题
    3. 对每个子问题求解，得到子问题的局部最优解
    4. 把子问题的解局部最优解合成原来解问题的一个解

### 2.5 dfs & bfs

* dfs: 深度优先算法, stack
* bfs: 广度优先算法, queue

### 2.6 双指针

* list 2-3, 若两个链表相交,两个指针同时遍历这两个链表,终会相交
