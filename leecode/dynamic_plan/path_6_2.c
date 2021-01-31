#include <stdio.h>

int uniquePaths(int m, int n)
{
    int i, j;
    int f[m][n];

    for (i = 0; i < m; i++) {
        f[i][0] = 1;
    }

    for (j = 0; j < n; j++) {
        f[0][j] = 1;
    }

    for (i = 1; i < m; i++) {
        for (j = 1; j < n; j++) {
            f[i][j] = f[i-1][j] + f[i][j-1];
        }
    }

    return f[m-1][n-1];
}

int main(void)
{
    printf("%d\n", uniquePaths(23, 12));
    return 0;
}
