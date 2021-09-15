#include <stdlib.h>
#include <stdio.h>

int* findElement(int** mat, int matRowLen, int* matColLen, int n, int m, int x, int* returnSize)
{
    *returnSize = 2;
    int *ret = (int *)malloc(2 * sizeof(int));

    int r_pos = n - 1;
    int c_pos = 0;
    while (mat[r_pos][c_pos] != x) {
        if (mat[r_pos][c_pos] > x) {
            r_pos--;
        } else if (mat[r_pos][c_pos] < x) {
            c_pos++;
        } else {
            break;
        }
    }

    ret[0] = r_pos;
    ret[1] = c_pos;
    return ret;
}

int main(void)
{
    int row0[] = {1,2,3};
    int row1[] = {4,5,6};
    int row2[] = {7,8,9};
    int *mat[] = {
        row0,
        row1,
        row2,
    };

    int size;
    // int *ret = findElement(mat, 2, NULL, 2, 3, 6, &size);
    int *ret = findElement(mat, 3, NULL, 3, 3, 6, &size);

    printf("[%d,%d]\n", ret[0], ret[1]);
    return 0;
}