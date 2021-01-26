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

### 2.2 递归

### 2.3 遍历

### 2.4 动态规划

### 2.5 贪心算法

### 2.6 dfs

### 2.7 双指针

