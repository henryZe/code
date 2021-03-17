#include <stdio.h>
#include <stdlib.h>

struct node {
    int coef;
    int exp;
    struct node *next;
};

struct queue {
    struct node *front;
    struct node *rear;
};

// struct node *add(, , )
// {
//     int ret;
    
//     compare();
//     switch (ret) {
//     case 1:
        
//         break;

//     case -1:

//         break;

//     default:

//         break;
//     }



//     return front->next;
// }

// struct node *mul()
// {

// }

void queue_init(struct queue *q)
{
    q->front = q->rear = NULL;
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

int main(void)
{
    int num1, num2;
    int coef, exp;
    struct node tmp;
    struct queue q1, q2;

    queue_init(&q1);
    queue_init(&q2);

    scanf("%d", &num1);
    for (int i = 0; i < num1; i++) {
        scanf("%d", &coef);
        scanf("%d", &exp);
        queue_add(&q1, coef, exp);
    }

    scanf("%d", &num2);
    for (int i = 0; i < num2; i++) {
        scanf("%d", &coef);
        scanf("%d", &exp);
        queue_add(&q2, coef, exp);
    }

    for (struct node *it = q1.front; it; it = it->next)
        printf("q1 %d %d\n", it->coef, it->exp);

    for (struct node *it = q2.front; it; it = it->next)
        printf("q2 %d %d\n", it->coef, it->exp);

    return 0;
}
