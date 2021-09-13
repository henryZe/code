#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ARRAYSIZE(x) (sizeof(x)/sizeof(x[0]))

struct tree {
    int val;
    struct tree *left;
    struct tree *right;
};

struct queue {
    struct tree **queue;
    int front;
    int rear;
};

struct tree *parse_tree(int* preorder, int* inorder, int len)
{
    if (len == 0) {
        return NULL;
    }

    struct tree *root = (struct tree *)malloc(sizeof(struct tree));
    root->val = preorder[0];

    if (len == 1) {
        root->left = NULL;
        root->right = NULL;
        return root;
    }

    for (int i = 0; i < len; i++) {
        if (root->val == inorder[i]) {
            root->left = parse_tree(preorder + 1, inorder, i);
            root->right = parse_tree(preorder + 1 + i, inorder + i + 1, len - i - 1);
        }
    }

    return root;
}

bool queue_is_full(struct queue *q)
{
    return q->rear == (q->front - 1);
}

bool queue_is_empty(struct queue *q)
{
    return q->front == q->rear;
}

int enqueue(struct queue *q, struct tree *node)
{
    if (queue_is_full(q))
        return -1;

    q->queue[q->rear] = node;
    q->rear += 1;
    return 0;
}

struct tree *dequeue(struct queue *q)
{
    struct tree *node;

    if (queue_is_empty(q))
        return NULL;

    node = q->queue[q->front];
    q->front += 1;
    return node;
}

int queue_size(struct queue *q)
{
    return q->rear - q->front;
}

int level_order(struct tree *root, int *ret, int len)
{
    int n;
    struct tree *node;
    struct queue q;
    q.front = q.rear = 0;
    q.queue = (struct tree **)malloc(len * sizeof(struct tree *));
    int pos = 0;

    enqueue(&q, root);
    while (!queue_is_empty(&q)) {

        n = queue_size(&q);
        for (int i = 0; i < n; i++) {
            node = dequeue(&q);

            if (i == (n - 1)) {
                // last one
                ret[pos++] = node->val;
            }

            if (node->left)
                enqueue(&q, node->left);
            if (node->right)
                enqueue(&q, node->right);
        }
    }

    return pos;
}

int* solve(int* preorder, int len1, int* inorder, int len2, int* returnSize)
{
    struct tree *root = parse_tree(preorder, inorder, len1);
    int *ret = (int *)malloc(len1 * sizeof(int));

    *returnSize = level_order(root, ret, len1);
    return ret;
}

int main(void)
{
    int preorder[] = {
        1,2,4,5,3
    };
    int inorder[] = {
        4,2,5,1,3
    };

    int size = 0;
    int *ret = solve(preorder, ARRAYSIZE(preorder), inorder, ARRAYSIZE(inorder), &size);

    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d,", ret[i]);
    }
    printf("]\n");

    return 0;
}
