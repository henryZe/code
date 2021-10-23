#include <stdlib.h>
#include <stdio.h>

int find_index(int *array, int l, int r, int value)
{
    for (int i = l; i <= r; i++) {
        if (array[i] == value) {
            return i;
        }
    }

    return -1;
}

void Preorder(int *post, int l_p, int r_p, int *mid, int l_m, int r_m)
{
    if (l_p > r_p)
        return;

    printf(" %d", post[r_p]);
    int mid_root = find_index(mid, l_m, r_m, post[r_p]);

    int n_left = mid_root - l_m;
    int n_right = r_m - mid_root;

    // left subtree
    Preorder(post, l_p, l_p + n_left - 1, mid, l_m, mid_root - 1);
    // right subtree
    Preorder(post, l_p + n_left, r_p - 1, mid, mid_root + 1, r_m);
}

int main(void)
{
    int num;
    scanf("%d\n", &num);

    int *post_order = malloc(sizeof(int) * num);
    int *mid_order = malloc(sizeof(int) * num);

    for (int i = 0; i < num; i++) {
        scanf("%d ", post_order + i);
    }

    for (int i = 0; i < num; i++) {
        scanf("%d ", mid_order + i);
    }

    printf("Preorder:");
    Preorder(post_order, 0, num - 1, mid_order, 0, num - 1);
    printf("\n");

    return 0;
}
