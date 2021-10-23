#include <stdio.h>

int main(void)
{
    int a;

    while (scanf("%x", &a) != EOF) {
        printf("%d\n", a);
    }

    return 0;
}