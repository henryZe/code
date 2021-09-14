#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct self_stack {
    int *data;
    int top;
    int size;
};

void stack_init(struct self_stack *s, int n)
{
    s->data = (int *)malloc(n * sizeof(int));
    s->top = 0;
    s->size = n;
}

bool stack_is_empty(struct self_stack *s)
{
    return s->top == 0;
}

void stack_push(struct self_stack *s, int data)
{
    s->data[s->top++] = data;
    return;
}

int stack_pop(struct self_stack *s)
{
    return s->data[--s->top];
}

bool isPail(struct ListNode* head)
{
    struct self_stack num;
    stack_init(&num, 1000001);

    struct ListNode *node = head;
    while (node) {
        stack_push(&num, node->val);
        node = node->next;
    }

    node = head;
    while (node) {
        if (node->val != stack_pop(&num))
            return false;
        node = node->next;
    }

    return true;
}

int main(void)
{
    struct ListNode head = {
        .val = 1,
        .next = NULL,
    };
    printf("%s\n", isPail(&head) ? "true" : "false");
    return 0;
}
