#include <stdio.h>

int main(void)
{
    int a, num_a;

    while (scanf("%d", &num_a) != EOF) {
        int sum = 0;
        for (int i = 0; i < num_a; i++) {
            scanf("%d", &a);
            sum += a;
        }
        printf("%d\n", sum);
    }
    return 0;
}