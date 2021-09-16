#include <stdio.h>

int main(void)
{
    int a, sum = 0;

    while (scanf("%d", &a) != EOF) {
        sum += a;
        if (getchar() == '\n') {
            printf("%d\n", sum);
            sum = 0;
        }
    }
    return 0;
}