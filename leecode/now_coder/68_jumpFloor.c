#include "stdio.h"

int jumpFloor(int number)
{
    // write code here
    if (number == 0 || number == 1)
        return 1;

    int a[number + 1];
    a[0] = 1;
    a[1] = 1;

    for (int i = 2; i <= number; i++) {
        a[i] = a[i - 1] + a[i - 2];
    }

    return a[number];
}

int main(void)
{
    printf("step = %d\n", jumpFloor(7));
    return 0;
}
