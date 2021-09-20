#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(void)
{
    float num;
    scanf("%f\n", &num);

    int num_i = num;
    float num_ref = num_i + 0.5;
    if (num >= num_ref) {
        printf("%d\n", num_i + 1);
    } else {
        printf("%d\n", num_i);
    }

    return 0;
}