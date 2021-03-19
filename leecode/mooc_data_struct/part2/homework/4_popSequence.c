#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct stack {
    int *data;
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

int stack_peek(struct stack *s)
{
    if (stack_empty(s))
        return -1;
    // printf("top %d peek %d\n", s->top, s->data[s->top - 1]);
    return s->data[s->top - 1];
}

bool stack_push(struct stack *s, int num)
{
    if (stack_full(s))
        return false;
    
    s->data[(s->top)++] = num;
    return true;
}

int stack_pop(struct stack *s)
{
    if (stack_empty(s))
        return -1;
    return s->data[--(s->top)];
}

bool test_stack(struct stack *s, int *seq, int seq_len)
{
    int num = 1;
    bool ret;

    for (int i = 0; i < seq_len; i++) {
        // printf("seq %d\n", seq[i]);

        while (stack_peek(s) != seq[i]) {
            ret = stack_push(s, num++);
            if (!ret)
                return false;
        }
        // printf("stack_peek %d\n", stack_peek(s));

        stack_pop(s);
    }

    return true;
}

int main(void)
{
    int stack_size, seq_len, seq_num;
    int **array;
    int *stack;

    scanf("%d %d %d", &stack_size, &seq_len, &seq_num);
    stack = malloc(sizeof(int) * stack_size);
    array = malloc(sizeof(int *) * seq_num);

    for (int i = 0; i < seq_num; i++) {
        array[i] = malloc(sizeof(int) * seq_len);
        for (int j = 0; j < seq_len; j++)
            scanf("%d", &(array[i][j]));
    }

    struct stack s = { .data = stack };
    for (int i = 0; i < seq_num; i++) {
        stack_init(&s, stack_size);
        printf("%s\n", test_stack(&s, array[i], seq_len) ? "YES" : "NO");
    }

    for (int i = 0; i < seq_num; i++)
        free(array[i]);
    free(array);
    free(stack);

    return 0;
}