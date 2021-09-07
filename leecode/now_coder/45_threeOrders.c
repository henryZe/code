struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * 
 * @param root TreeNode类 the root of binary tree
 * @return int整型二维数组
 * @return int* returnSize 返回数组行数
 * @return int** returnColumnSizes 返回数组列数
 */
int preorder(struct TreeNode* root, int *a, int num)
{
    if (!root)
        return num;

    a[num++] = root->val;
    num = preorder(root->left, a, num);
    num = preorder(root->right, a, num);

    return num;
}

int inorder(struct TreeNode* root, int *a, int num)
{
    if (!root)
        return num;

    num = inorder(root->left, a, num);
    a[num++] = root->val;
    num = inorder(root->right, a, num);

    return num;
}

int postorder(struct TreeNode* root, int *a, int num)
{
    if (!root)
        return num;

    num = postorder(root->left, a, num);
    num = postorder(root->right, a, num);
    a[num++] = root->val;

    return num;
}

int** threeOrders(struct TreeNode* root, int* returnSize, int** returnColumnSizes )
{
    int *a = (int *)malloc(sizeof(int) * 1000000);
    int *b = (int *)malloc(sizeof(int) * 1000000);
    int *c = (int *)malloc(sizeof(int) * 1000000);
    int num = 0;
    int **res = (int **)malloc(sizeof(int *) * 3);

    *returnColumnSizes = (int *)malloc(sizeof(int) * 3);

    (*returnColumnSizes)[0] = preorder(root, a, 0);
    (*returnColumnSizes)[1] = inorder(root, b, 0);
    (*returnColumnSizes)[2] = postorder(root, c, 0);

    res[0] = a;
    res[1] = b;
    res[2] = c;
    *returnSize = 3;

    return res;
}