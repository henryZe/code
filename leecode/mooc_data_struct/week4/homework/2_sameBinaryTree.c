#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct tree {
    int val;
    bool visited;
    struct tree *left;
    struct tree *right;
};

int tree_insert(struct tree **t, struct tree *new)
{
    if (!(*t))
        t = new;

    if (*t.val)
}

// bool tree_find(struct tree **t, int x)
// {
//     if (!(*t))
//         t = 
// }

struct tree *create_tree(int num)
{
    int val;
    struct tree *t = NULL;
    struct tree *ls = malloc(sizeof(struct tree) * num);


    for (int j = 0; j < num; j++) {
        scanf("%d", val);

        ls[j].val = val;
        ls[j].visited = false;
        ls[j].left = NULL;
        ls[j].right = NULL;

        tree_insert(&t, &ls[j]);
    }

    return t;
}

int main(void)
{
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

            int ret = tree_verify(t, nums);
            printf("%s\n", ret ? "Yes" : "No");

            free(nums);
        }

        free(t);
    }

    return 0;
}
