#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct TreeNode {
    struct TreeNode *left;
    struct TreeNode *right;
    int val;
};

#define N 2000

int** zigzagLevelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes)
{
    *returnSize = 0;
    if (!root)
        return NULL;

    struct TreeNode** node_queue = malloc(N * sizeof(struct TreeNode*));
    struct TreeNode* node;
    int* num_queue = malloc(2 * N * sizeof(int));
    int left = 0, right = 0;
    int front = N, rear = N;
    unsigned char left_order = true;
    int size;
    int column = 0;
    int i;
    int **ans = malloc(N * sizeof(int *));

    *returnColumnSizes = malloc(N * sizeof(int));
    node_queue[right++] = root;

    while (left < right) {
        size = right - left;

        front = N;
        rear = N;
        for (i = 0; i < size; i++) {
            node = node_queue[left++];

            if (left_order)
                num_queue[rear++] = node->val;
            else
                num_queue[--front] = node->val;

            if (node->left)
                node_queue[right++] = node->left;
            if (node->right)
                node_queue[right++] = node->right;
        }

        int *tmp = malloc(size * sizeof(int));
        for (i = 0; i < size; i++) {
            tmp[i] = num_queue[front++];
        }

        ans[*returnSize] = tmp;
        (*returnColumnSizes)[*returnSize] = size;
        (*returnSize)++;
        left_order = !left_order;
    }

    return ans;
}

int main(void)
{
    struct TreeNode rl = {NULL, NULL, 5};
    struct TreeNode rrl = {NULL, NULL, 12};
    struct TreeNode rrr = {NULL, NULL, 17};
    struct TreeNode rr = {&rrl, &rrr, 15};
    struct TreeNode root = {&rl, &rr, 10};
    int i, j;
    int returnSize;
    int *returnColumnSizes;
    int **res;

    res = zigzagLevelOrder(&root, &returnSize, &returnColumnSizes);
    for (i = 0; i < returnSize; i++) {
        printf("[");
        for (j = 0; j < returnColumnSizes[i] - 1; j++) {
            printf("%d,", (res[i])[j]);
        }
        if (j == returnColumnSizes[i] - 1) {
            printf("%d", (res[i])[j]);
        }
        if (i == returnSize - 1) {
            printf("]\n");
        } else {
            printf("],");
        }
    }
    return 0;
}
