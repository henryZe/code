#include <stdio.h>

int main(void)
{
    int a, b, num;
    scanf("%d\n", &num);
    for (int i = 0; i < num; i++) {
        scanf("%d %d\n", &a, &b);
        printf("%d\n", a + b);
    }
    return 0;
}