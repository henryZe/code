#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int abs(int x)
{
    return x > 0 ? x : -x;
}

struct tree {
    int val;
    int depth;
    struct tree *left;
    struct tree *right;
};

enum ROTATION {
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
    printf("%d depth: %d l: %d r: %d\n",
            t->val, t->depth,
            t->left ? t->left->val : -1,
            t->right ? t->right->val : -1);
    inOrder(t->right);

    return;
}

int calc_depth(struct tree *t)
{
    int left_depth, right_depth;

    if (t->left) {
        left_depth = t->left->depth;
    } else {
        left_depth = 0;
    }

    if (t->right) {
        right_depth = t->right->depth;
    } else {
        right_depth = 0;
    }

    return fmax(left_depth + 1, right_depth + 1);
}

int calc_delta(struct tree *t)
{
    int left_depth, right_depth;

    if (t->left) {
        left_depth = t->left->depth;
    } else {
        left_depth = 0;
    }

    if (t->right) {
        right_depth = t->right->depth;
    } else {
        right_depth = 0;
    }

    return left_depth - right_depth;
}

struct tree *rotate_ll(struct tree *t, struct tree *new)
{
    struct tree *a = t;
    struct tree *b = t->left;

    a->left = b->right;
    b->right = a;

    // update depth
    a->depth = calc_depth(a);
    b->depth = calc_depth(b);
    return b;
}

struct tree *rotate_rr(struct tree *t, struct tree *new)
{
    struct tree *a = t;
    struct tree *b = t->right;

    a->right = b->left;
    b->left = a;

    // update depth
    a->depth = calc_depth(a);
    b->depth = calc_depth(b);
    return b;
}

struct tree *rotate_lr(struct tree *t, struct tree *new)
{
    struct tree *a = t;
    struct tree *b = t->left;
    struct tree *c = t->left->right;

    b->right = c->left;
    a->left = c->right;
    c->left = b;
    c->right = a;

    // update depth
    a->depth = calc_depth(a);
    b->depth = calc_depth(b);
    c->depth = calc_depth(c);
    return c;
}

struct tree *rotate_rl(struct tree *t, struct tree *new)
{
    struct tree *a = t;
    struct tree *b = t->right;
    struct tree *c = t->right->left;

    a->right = c->left;
    b->left = c->right;
    c->left = a;
    c->right = b;

    // update depth
    a->depth = calc_depth(a);
    b->depth = calc_depth(b);
    c->depth = calc_depth(c);
    return c;
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
    t->depth = calc_depth(t);

    // printf("calc_delta(%d) = %d\n",
    //         t->val, calc_delta(t));

    if (abs(calc_delta(t)) > 1) {
        // printf("founder %d depth %d troubler %d depth %d\n",
        //         t->val, t->depth, new->val, new->depth);

        int pos;
        if (t->val >= new->val) {
            if (t->left->val >= new->val) {
                pos = LL;
            } else {
                pos = LR;
            }
        } else {
            if (t->right->val >= new->val) {
                pos = RL;
            } else {
                pos = RR;
            }
        }

        // printf("position %d\n", pos);
        switch (pos) {
        case LL:
            t = rotate_ll(t, new);
            break;
        case RR:
            t = rotate_rr(t, new);
            break;
        case LR:
            t = rotate_lr(t, new);
            break;
        case RL:
            t = rotate_rl(t, new);
            break;
        default:
            break;
        }
    }

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
        ls[i].depth = 1;
        ls[i].left = NULL;
        ls[i].right = NULL;

        root = tree_insert(root, &ls[i]);

        // display tree
        // inOrder(root);
        // printf("\n");
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
