#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct tree {
    int val;
    bool visited;
    struct tree *left;
    struct tree *right;
};

struct tree *tree_insert(struct tree *t, struct tree *new)
{
    if (!t)
        return new;

    if (t->val >= new->val) {
        t->left = tree_insert(t->left, new);
    } else {
        t->right = tree_insert(t->right, new);
    }

    return t;
}

struct tree *create_tree(int num)
{
    int val;
    struct tree *t = NULL;
    struct tree *ls = malloc(sizeof(struct tree) * num);

    for (int j = 0; j < num; j++) {
        scanf("%d", &val);

        ls[j].val = val;
        ls[j].visited = false;
        ls[j].left = NULL;
        ls[j].right = NULL;

        t = tree_insert(t, &ls[j]);
    }

    return t;
}

bool tree_find(struct tree *t, int x)
{
    if (!t)
        return false;

    if (t->val == x && !t->visited) {
        t->visited = true;
        return true;
    }

    if (!t->visited)
        return false;

    if (t->val >= x)
        return tree_find(t->left, x);
    
    return tree_find(t->right, x);
}

bool tree_verify(struct tree *t, int *nums, int num)
{
    // initialize visited flag
    for (int i = 0; i < num; i++) {
        t[i].visited = false;
    }

    for (int i = 0; i < num; i++) {
        if (!tree_find(t, nums[i]))
            return false;
    }

    return true;
}

int main(void)
{
    char str[256] = {0};

    while (1) {
        int num, cases;

        scanf("%d", &num);
        if (!num)
            break;

        scanf("%d", &cases);
        if (!cases)
            continue;

        struct tree *t = create_tree(num);

        for (int i = 0; i < cases; i++) {
            int *nums = malloc(sizeof(int) * num);

            for (int j = 0; j < num; j++) {
                scanf("%d", nums + j);
            }

            bool ret = tree_verify(t, nums, num);
            strcat(str, ret ? "Yes\n" : "No\n");

            free(nums);
        }

        free(t);
    }

    printf("%s", str);
    return 0;
}
