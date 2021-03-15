#include <stdlib.h>

#define MaxSize 16

struct bi_stack {
    int data[MaxSize];
    int top1;
    int top2;
};

void push(struct bi_stack *stack, int item, int tag)
{
    if (stack->top2 - stack->top1 == 1)
        printf("stack is full!\n");
    
    if (tag == 1) {
        stack->data[++(stack->top1)] = item;
    } else {
        stack->data[--(stack->top2)] = item;
    }
}

int pop(struct bi_stack *stack, int tag)
{
    if (tag == 1) {
        if (stack->top1 == -1) {
            printf("stack is empty!\n");
            return NULL;
        } else {
            return stack->data[stack->top1--];
        }
    } else {
        if (stack->top2 == MaxSize) {
            printf("stack is empty!\n");
            return NULL;
        } else {
            return stack->data[stack->top2++];
        }
    }
}
