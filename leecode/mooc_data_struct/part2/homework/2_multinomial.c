#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int coef;
    int exp;
    struct node *next;
};

struct queue {
    struct node *front;
    struct node *rear;
};

struct queue *queue_create(void)
{
    struct queue *q = malloc(sizeof(struct queue));
    q->front = q->rear = NULL;
    return q;
}

void queue_free(struct queue *q)
{
    struct node *i = q->front;
    struct node *tmp;
    
    while (i) {
        tmp = i->next;
        free(i);
        i = tmp;
    }

    free(q);
}

void queue_add(struct queue *q, int coef, int exp)
{
    struct node *new_node = malloc(sizeof(struct node));

    new_node->coef = coef;
    new_node->exp = exp;
    new_node->next = NULL;

    if (!q->rear)
        // queue is empty
        q->front = new_node;
    else
        q->rear->next = new_node;    

    q->rear = new_node;
}

int compare(int a, int b)
{
    if (a == b)
        return 0;
    return a > b ? 1 : -1;
}

void queue_print(struct queue *q)
{
    char tmp[16] = {0};
    char str[128] = {0};

    for (struct node *it = q->front; it; it = it->next) {
        if (it->coef) {
            sprintf(tmp, "%d %d ", it->coef, it->exp);
            strcat(str, tmp);
        }
    }

    str[strlen(str) - 1] = '\n';
    printf("%s", str);
}

struct queue *add(struct queue *q1, struct queue *q2)
{
    int ret, coef;
    struct node *n1 = q1->front, *n2 = q2->front;
    struct queue *q = queue_create();

    while (n1 && n2) {
        ret = compare(n1->exp, n2->exp);
        switch (ret) {
        case 1:
            queue_add(q, n1->coef, n1->exp);
            n1 = n1->next;
            break;

        case -1:
            queue_add(q, n2->coef, n2->exp);
            n2 = n2->next;
            break;

        default:
            coef = n1->coef + n2->coef;
            // if (coef) {
                queue_add(q, coef, n1->exp);
                n1 = n1->next;
                n2 = n2->next;
            // }
            break;
        }
    }

    while (n1) {
        queue_add(q, n1->coef, n1->exp);
        n1 = n1->next;
    }

    while (n2) {
        queue_add(q, n2->coef, n2->exp);
        n2 = n2->next;
    }

    return q;
}

struct queue *mul(struct queue *q1, struct queue *q2)
{
    struct queue *q = NULL;

    for (struct node *i = q1->front; i; i = i->next) {
        struct queue *tmp = queue_create();

        for (struct node *j = q2->front; j; j = j->next) {
            queue_add(tmp, i->coef * j->coef, i->exp + j->exp);
        }

        if (!q) {
            q = tmp;
            continue;
        }

        struct queue *prev = q;
        q = add(prev, tmp);
        queue_free(prev);
        queue_free(tmp);
    }

    return q;
}

void queue_read(struct queue *q)
{
    int num;
    int coef, exp;

    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        scanf("%d", &coef);
        scanf("%d", &exp);
        queue_add(q, coef, exp);
    }
}

int main(void)
{
    struct queue *q1, *q2;

    q1 = queue_create();
    q2 = queue_create();

    queue_read(q1);
    queue_read(q2);

    // queue_print(q1);
    // queue_print(q2);

    struct queue *q_add, *q_mul;

    q_mul = mul(q1, q2);
    q_add = add(q1, q2);

    queue_print(q_mul);
    queue_print(q_add);

    queue_free(q1);
    queue_free(q2);

    queue_free(q_mul);
    queue_free(q_add);

    return 0;
}
