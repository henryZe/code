#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

int main(void)
{
    long num;
    scanf("%ld\n", &num);

    int k = sqrt(num) + 1;
    for (int i = 2; i <= k; i++) {
        while (num % i == 0) {
            num /= i;
            printf("%d ", i);
        }

        if (num == 1)
            break;
    }

    if (num != 1)
        printf("%ld ", num);

    printf("\n");
    return 0;
}