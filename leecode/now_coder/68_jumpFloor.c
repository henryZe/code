#include "stdio.h"

int jumpFloor(int number)
{
    // write code here
    if (number == 0 || number == 1)
        return 1;

    return jumpFloor(number - 2) + jumpFloor(number - 1);
}

int main(void)
{
    printf("step = %d\n", jumpFloor(4));
    return 0;
}
