#include <stdio.h>
#include <stdlib.h>

int** rotateMatrix(int** mat, int n)
{
    int **new_m = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        new_m[i] = (int *)malloc(sizeof(int) * n);
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            new_m[c][n - 1 - r] = mat[r][c];
        }
    }

    return new_m;
}

void display_matrix(int** mat, int n)
{
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("[");
        for (int j = 0; j < n; j++) {
            printf("%d,", mat[i][j]);
        }
        printf("]\n");
    }
    printf("]\n");
}

int main(void)
{
    int row0[] = {1,2,3};
    int row1[] = {4,5,6};
    int row2[] = {7,8,9};
    int *matrix[3] = {
        row0,
        row1,
        row2,
    };

    int **new_matrix = rotateMatrix(matrix, 3);
    display_matrix(new_matrix, 3);

    return 0;
}