struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int dfs(struct TreeNode* n, int len, int *res)
{
    if (!n)
        return len;

    if (n->left)
        len = dfs(n->left, len, res);

    res[len++] = n->val;

    if (n->right)
        len = dfs(n->right, len, res);

    return len;
}

int* getAllElements(struct TreeNode* root1, struct TreeNode* root2,
                    int* returnSize)
{
    int len, len1, len2;
    int *res1 = malloc(5000 * sizeof(int));
    int *res2 = malloc(5000 * sizeof(int));
    int *res = malloc(5000 * 2 * sizeof(int));

    // 1. walk tree1 & tree2
    len1 = dfs(root1, 0, res1);
    len2 = dfs(root2, 0, res2);

    // 2. merge list1 & list2
    len = len1 + len2;

    int j = 0, k = 0;

    for (int i = 0; i < len; i++) {
        if (j < len1 && k < len2) {
            if (res1[j] <= res2[k])
                res[i] = res1[j++];
            else
                res[i] = res2[k++];

            continue;
        }

        if (j < len1) {
            res[i] = res1[j++];
            continue;
        }

        if (k < len2) {
            res[i] = res2[k++];
            continue;
        }
    }

    *returnSize = len;
    return res;
}
