#include <stdio.h>

struct tree {
    int val;
    struct tree *left;
    struct tree *right;
};

int tree_insert(struct tree *t, struct tree *new)
{
    return 0;
}

struct tree *create_avl_tree(int num)
{
    int val;
    struct tree *root = NULL;
    struct tree *ls = malloc(sizeof(struct tree) * num);

    for (int i = 0; i < num; i++) {
        scanf("%d", &val);

        ls[i].val = val;
        ls[i].left = NULL;
        ls[i].right = NULL;

        root = tree_insert(root, &ls[i]);
    }

    return root;
}

int main(void)
{
    int num;
    scanf("%d", &num);

    printf("%d\n", create_avl_tree(num)->val);
    return 0;
}