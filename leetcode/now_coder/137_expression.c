#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct self_stack {
    int *data;
    int top;
    int size;
};

bool stack_is_empty(struct self_stack *s)
{
    return s->top == 0;
}

void stack_init(struct self_stack *s, int n)
{
    s->data = (int *)malloc(n * sizeof(int));
    s->top = 0;
    s->size = n;
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

int calc(struct self_stack *num, struct self_stack *op)
{
    while (!stack_is_empty(op)) {
        int num1 = stack_pop(num);
        int num2 = stack_pop(num);
        char oper = stack_pop(op);
        if (oper == '*') {
            num1 *= num2;
        } else if (oper == '+') {
            num1 += num2;
        } else {
            num1 -= num2;
        }
        stack_push(num, num1);
    }

    return stack_pop(num);
}

int solve(char *s)
{
    int n = strlen(s);

    struct self_stack op;
    stack_init(&op, n);
    struct self_stack num;
    stack_init(&num, n);

    struct self_stack op_r;
    stack_init(&op_r, n);
    struct self_stack num_r;
    stack_init(&num_r, n);

    int pos = 0;
    int number = 0;
    char oper;
    while (pos < n) {
        switch (s[pos]) {
        case ' ':
            pos++;
            break;
        case '+':
        case '-':
        case '*':
        case '(':
            stack_push(&op, s[pos]);
            pos++;
            break;
        case ')':
            oper = stack_pop(&op);
            while (oper != '(') {
                stack_push(&op_r, oper);
                stack_push(&num_r, stack_pop(&num));
                oper = stack_pop(&op);
            }
            stack_push(&num_r, stack_pop(&num));
            number = calc(&num_r, &op_r);
            stack_push(&num, number);
            pos++;
            break;
        default:
            number = 0;
            while ((s[pos] >= '0') && (s[pos] <= '9')) {
                number = number * 10 + (s[pos] - '0');
                pos++;
            }
            if (!stack_is_empty(&op)) {
                oper = stack_pop(&op);
                if (oper == '*') {
                    number *= stack_pop(&num);
                } else {
                    stack_push(&op, oper);
                }
            }
            stack_push(&num, number);
            break;
        }
    }

    while (!stack_is_empty(&op)) {
        stack_push(&op_r, stack_pop(&op));
    }

    while (!stack_is_empty(&num)) {
        stack_push(&num_r, stack_pop(&num));
    }

    return calc(&num_r, &op_r);
}

int main(void)
{
    // char *str = "1 + 2";
    // char *str = "2-1 + 2";
    char *str = "(1+(4+5+2)-3)+(6+8)";
    // char *str = "1 + 2 * (3 + 4 * 5)";  // 47
    printf("%d\n", solve(str));
    return 0;
}
