#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

bool isValid(char *str)
{
    char *ref[] = { "()", "{}", "[]" };
    int len = strlen(str);
    struct stack s;
    s.data = malloc(len);
    bool res = true;

    stack_init(&s, len);

    for (int i = 0; i < len; i++) {
        int j;
        for (j = 0; j < 3; j++) {
            if (ref[j][1] == str[i]) {
                if (stack_pop(&s) != ref[j][0]) {
                    res = false;
                    break;
                }
                break;
            }
        }

        if (res == false)
            break;

        if (j == 3)
            stack_push(&s, str[i]);
    }

    if (res == false)
        return res;

    res = (s.top == 0) ? true : false;
    return res;
}

int main(void)
{
    char str[1024];
    scanf("%s\n", str);

    bool ret = isValid(str);
    if (ret) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    return 0;
}