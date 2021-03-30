#include <stdio.h>
#include <stdlib.h>

int abs(int x)
{
    return x > 0 ? x : -x;
}

struct tree {
    int val;
    int delta_degree;
    struct tree *left;
    struct tree *right;
};

enum rotation {
    LL,
    RR,
    LR,
    RL,
};

void inOrder(struct tree *t)
{
    if (!t)
        return;

    inOrder(t->left);
    printf("%d l: %d r: %d\n", t->val,
                t->left ? t->left->val : -1,
                t->right ? t->right->val : -1);
    inOrder(t->right);

    return;
}

struct tree *tree_insert(struct tree *t, struct tree *new)
{
    if (!t)
        return new;

    if (new->val <= t->val) {
        t->left = tree_insert(t->left, new);
    } else if (new->val > t->val) {
        t->right = tree_insert(t->right, new);
    }

    // update t's degree
    // if abs(delta_degree) > 1
    //     founder = t & troubler = new
    //     calculate relative location of t & new

    // switch(location) {
    //     case LL:
    //         rotate_ll
    //     case RR:
    //         rotate_rr
    //     case LR:
    //         rotate_lr
    //     case RL:
    //         rotate_rl
    //     default:
    //         break;
    // }

    // update degree

    return t;
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

    // display tree
    inOrder(root);
    return root;
}

int main(void)
{
    int num;
    scanf("%d", &num);

    printf("%d\n", create_avl_tree(num)->val);
    return 0;
}
