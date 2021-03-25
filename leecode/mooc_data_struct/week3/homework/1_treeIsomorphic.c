#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct tree {
    char val;
    bool is_root;
    struct tree *left;
    struct tree *right;
};

bool is_isomorphic(struct tree *t1, struct tree *t2)
{
    if (!t1 && !t2) {
        return true;
    } else if ((t1 && !t2) || (!t1 && t2)) {
        return false;
    } else if (t1->val != t2->val) {
        return false;
    }

    if (is_isomorphic(t1->left, t2->left) && is_isomorphic(t1->right, t2->right))
        return true;

    if (is_isomorphic(t1->right, t2->left) && is_isomorphic(t1->left, t2->right))
        return true;
    
    return false;
}

struct tree *create_tree(void)
{
    int num;
    char c, left, right;
    int l, r;

    scanf("%d", &num);

    struct tree *list = malloc(sizeof(struct tree) * num);
    for (int i = 0; i < num; i++) {
        list[i].is_root = true;
    }

    for (int i = 0; i < num; i++) {
        scanf(" %c %c %c", &c, &left, &right);

        list[i].val = c;

        if (left != '-') {
            l = left - '0';
            list[i].left = &list[l];
            list[l].is_root = false;
        } else {
            list[i].left = NULL;
        }
    
        if (right != '-') {
            r = right - '0';
            list[i].right = &list[r];
            list[r].is_root = false;
        } else {
            list[i].right = NULL;
        }
    }

    for (int i = 0; i < num; i++) {
        if (list[i].is_root)
            return &list[i];
    }

    return NULL;
}

int print_tree(struct tree *t)
{
    if (!t) {
        printf("NULL\n");
        return 0;
    }
    
    printf("%c\n", t->val);
    if (t->left) {
        printf("l: ");
        print_tree(t->left);
    }
    if (t->right) {
        printf("r: ");
        print_tree(t->right);
    }

    return 0;
}

int main(void)
{
    printf("%s\n", is_isomorphic(create_tree(), create_tree()) ? "Yes" : "No");
    return 0;
}