#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct tree {
    int val;
    struct tree *left;
    struct tree *right;
};

struct tree *create_tree(void)
{
    int num;

    scanf("%d", &num);
    if (num <= 0)
        return NULL;

    int i = 0;
    struct tree *parent = NULL;
    struct tree *cur = NULL;
    struct tree *leaves = malloc(sizeof(struct tree) * num);
    memset(leaves, 0, num * sizeof(struct tree));

    int top = 0;
    struct tree *stack[num];
    memset(stack, 0, num * sizeof(struct tree *));

    char str[8];
    bool option = true; // true: push false: pop

    do {
        scanf("%s", str);
        if (!strcmp(str, "Push")) {
            cur = &leaves[i++];
            scanf("%d", &(cur->val));
            if (parent) {
                if (option) {
                    parent->left = cur;
                } else {
                    parent->right = cur;
                }
            }
            parent = cur;
            option = true;
            stack[top++] = cur;

        } else {
            // pop
            cur = stack[--top];
            option = false;
        }

        parent = cur;
    } while (top || i < num);

    // printf("%d %s\n", num, str);
    return &leaves[0];
}

void postOrder(struct tree *t, int root_val)
{
    if (!t)
        return;

    postOrder(t->left, root_val);
    postOrder(t->right, root_val);

    if (t->val != root_val)
        printf("%d ", t->val);
    else
        printf("%d\n", t->val);
    return;
}

int main(void)
{
    struct tree *t = create_tree();
    postOrder(t, t->val);
    return 0;
}
