#include <stdio.h>

int main(void)
{
    int a, b;
    while (1) {
        scanf("%d %d\n", &a, &b);
        if (!a && !b)
            break;
        printf("%d\n", a + b);
    }
    return 0;
}