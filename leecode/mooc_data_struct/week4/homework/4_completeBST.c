#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define QUEUE_SIZE 1001

struct tree {
    int val;
    struct tree *left;
    struct tree *right;
};

struct queue {
    struct tree *queue[QUEUE_SIZE];
    int front;
    int rear;
};

int enqueue(struct queue *q, struct tree *node)
{
    if (q->rear == (q->front - 1)) {
        return -1;
    }

    q->queue[q->rear] = node;
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    return 0;
}

struct tree *dequeue(struct queue *q)
{
    struct tree *node;

    if (q->front == q->rear) {
        return NULL;
    }

    node = q->queue[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    return node;
}

bool queue_is_empty(struct queue *q)
{
    return q->front == q->rear;
}

int queue_size(struct queue *q)
{
    return q->rear >= q->front ?
           q->rear - q->front : q->rear + QUEUE_SIZE - q->front;
}

int level_order(struct tree *root)
{
    int n;
    struct tree *node;
    struct queue *q = malloc(sizeof(struct queue));
    q->front = 0;
    q->rear = 0;

    struct queue *print = malloc(sizeof(struct queue));
    print->front = 0;
    print->rear = 0;

    enqueue(q, root);
    while (!queue_is_empty(q)) {
        n = queue_size(q);

        for (int i = 0; i < n; i++) {
            node = dequeue(q);
            enqueue(print, node);

            if (node->left)
                enqueue(q, node->left);
            if (node->right)
                enqueue(q, node->right);
        }
    }

    while (queue_size(print) > 1) {
        printf("%d ", dequeue(print)->val);
    }
    if (!queue_is_empty(print)) {
        printf("%d\n", dequeue(print)->val);
    }

    return 0;
}

int compare(const void *a, const void *b)
{
    return *(int *)a > *(int *)b ? 1 : -1;
}

struct tree *create_empty_complete_BST(int num)
{
    if (!num)
        return NULL;

    struct tree *base = malloc(sizeof(struct tree) * (num + 1));

    for (int j = 2; j <= num; j++) {
        int i = j >> 1;

        base[j].left = NULL;
        base[j].right = NULL;

        if (j & 1) {
            base[i].right = &base[j];
        } else {
            base[i].left = &base[j];
        }
    }

    return &base[1];
}

int inOrder(struct tree *t, int *nums, int index)
{
    if (!t)
        return index;

    index = inOrder(t->left, nums, index);
    t->val = nums[index++];
    index = inOrder(t->right, nums, index);

    return index;
}

void inOrder_fill(struct tree *t, int *nums, int num)
{
    if (!t || !nums || !num)
        return;

    inOrder(t, nums, 0);
}

struct tree *create_completeBST(void)
{
    int num;
    scanf("%d", &num);

    int *nums = malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++) {
        scanf("%d", nums + i);
    }

    qsort(nums, num, sizeof(int), compare);

    struct tree *t = create_empty_complete_BST(num);
    inOrder_fill(t, nums, num);

    return t;
}

int main(void)
{
    struct tree *t;

    t = create_completeBST();
    level_order(t);

    return 0;
}