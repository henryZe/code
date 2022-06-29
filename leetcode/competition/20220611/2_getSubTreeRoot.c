/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: 考生实现代码
 * Note: 缺省代码仅供参考，可自行决定使用、修改或删除 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LEN 10000

struct node {
    struct node *left;
    struct node *right;
    int arr_i;
    int value;
    int total;
};

struct queue {
    struct node **queue;
    int size;
    int front;
    int rear;
};

int init_queue(struct queue *q, int len)
{
    q->queue = malloc(sizeof(struct node *) * len);
    q->size = len;
    q->front = 0;
    q->rear = 0;

    return 0;
}

bool queue_is_full(struct queue *q)
{
    return q->rear == q->size;
}

int enqueue(struct queue *q, struct node *n)
{
    if (queue_is_full(q)) {
        return -1;
    }

    q->queue[q->rear] = n;
    q->rear += 1;
    return 0;
}

bool queue_is_empty(struct queue *q)
{
    return q->front == q->rear;
}

struct node *dequeue(struct queue *q)
{
    struct node *node;

    if (queue_is_empty(q)) {
        return NULL;
    }

    node = q->queue[q->front];
    q->front += 1;
    return node;
}

int queue_size(struct queue *q)
{
    return q->rear - q->front;
}

struct node *build_tree(const int* arr, int arrLen, struct node *nodes)
{
    struct node *n;
    struct node *root = nodes;
    int nodes_i = 1, arr_i = 0;

    struct queue q;
    init_queue(&q, arrLen);
    enqueue(&q, root);

    while (1) {
        n = dequeue(&q);
        if (n == NULL) {
            break;
        }

        n->arr_i = arr_i;
        printf("dequeue %d\n", arr_i);
        n->value = arr[arr_i++];
        n->total = -1;
        n->left = NULL;
        n->right = NULL;

        if (n->value == -1) {
            continue;
        }

        if (nodes_i < arrLen) {
            printf("enqueue %d\n", nodes_i);
            n->left = nodes + nodes_i++;
            enqueue(&q, n->left);
        }

        if (nodes_i < arrLen) {
            printf("enqueue %d\n", nodes_i);
            n->right = nodes + nodes_i++;
            enqueue(&q, n->right);
        }
    }

    return root;
}

int get_value(struct node *head, struct node *tree)
{
    if (!tree)
        return 0;

    printf("%ld tree %d\n", tree - head, tree->value);

    if (tree->value == -1)
        return 0;

    tree->total = get_value(head, tree->left) + get_value(head, tree->right) + tree->value;

    return tree->total;
}

int find_node(struct node *n, int arrLen, int value)
{
    int target = value / 2;

    for (int i = 0; i < arrLen; i++) {
        if (n[i].total == target)
            return i;
    }

    return -1;
}

// 待实现函数，在此函数中填入答题代码;
int GetSubTreeRoot(const int* arr, int arrLen)
{
    struct node nodes[arrLen];
    struct node *root;
    int total_value;
    int ret = -1;

    root = build_tree(arr, arrLen, nodes);
    total_value = get_value(nodes, root);
    ret = find_node(root, arrLen, total_value);

    return ret;
}

int main(void)
{
    int arrLen = 0;
    if (scanf("%d\n", &arrLen) != 1) { return -1; }
    int arr[MAX_LEN];
    for (int i = 0; i < arrLen; i++) {
        if (scanf("%d", &arr[i]) != 1) { return -1; }
    }

    int result = GetSubTreeRoot(arr, arrLen);
    printf("%d\n", result);
    return 0;
}
