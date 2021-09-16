#include <stdio.h>

int main(void)
{
    int a, num;
    scanf("%d", &num);

    for (int i = 0; i < num; i++) {
        if (!num)
            break;

        int num_a, sum = 0;
        scanf("%d", &num_a);
        for (int i = 0; i < num_a; i++) {
            scanf("%d", &a);
            sum += a;
        }
        printf("%d\n", sum);
    }
    return 0;
}