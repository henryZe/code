#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct stack {
    char *data;
    int top;
    int size;
};

int stack_init(struct stack *s, int stack_size)
{
    if (!s)
        return 0;

    s->top = 0;
    s->size = stack_size;
    return 0;
}

bool stack_empty(struct stack *s)
{
    return s->top == 0;
}

bool stack_full(struct stack *s)
{
    return s->top == s->size;
}

bool stack_push(struct stack *s, char num)
{
    if (stack_full(s))
        return false;
    
    s->data[(s->top)++] = num;
    return true;
}

char stack_pop(struct stack *s)
{
    if (stack_empty(s))
        return -1;
    return s->data[--(s->top)];
}

char stack_peek(struct stack *s)
{
    int pos = s->top - 1;
    return s->data[pos];
}

#define stack_size 10000

int main(void)
{
    char push_char[] = {'a', 'b', 'c', 'd'};
    char pop_char[] = {'a', 'd', 'b', 'c'};

    int num = 4;

    struct stack push;

    push.data = malloc(sizeof(char) * stack_size);
    push.top = 0;
    push.size = stack_size;

    int j = 0;
    for (int i = 0; i < num; i++) {
        stack_push(&push, push_char[i]);
        // printf("push %c %c\n", stack_peek(&push), push_char[i]);
        while (push.top && stack_peek(&push) == pop_char[j] && j < num) {
            // printf("pop %c\n", stack_peek(&push));
            stack_pop(&push);
            j++;
        }
    }
    
    printf("%s\n", j == num ? "True": "false");
    return 0;
}