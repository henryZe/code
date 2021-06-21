



struct Tree {
    int data;
    struct Tree *left;
    struct Tree *right;
};

int main(void)
{
    int cases;
    scanf("%d\n", &cases);

    for (int i = 0; i < cases; i++) {
        int num;
        scanf("%d\n", &num);

        int *preorder = malloc(sizeof(int) * num);
        for (int j = 0; j < num; j++) {
            scanf("%d ", preorder + j);
        }

        struct Tree *tree = build_tree(num, preorder);

        calc_height();
        calc_balance_factor();

        free(preorder);
    }

    return 0;
}
