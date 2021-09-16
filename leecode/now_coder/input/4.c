#include <stdio.h>

int main(void)
{
    int a, num;
    while (1) {
        scanf("%d", &num);
        if (!num)
            break;

        int sum = 0;
        for (int i = 0; i < num; i++) {
            scanf("%d", &a);
            sum += a;
        }
        printf("%d\n", sum);
    }
    return 0;
}