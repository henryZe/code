#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MoreThanHalfNum_Solution(int *numbers, int numbersLen)
{
    int count = numbersLen / 2 + 1;
    int hash[10001] = {0};

    int i;
    for (i = 0; i < numbersLen; i++) {
        hash[numbers[i]] += 1;
        if (hash[numbers[i]] == count) {
            break;
        }
    }

    return numbers[i];
}

int main(void)
{
    int nums[] = {1,2,3,2,2,2,5,4,2};
    printf("%d\n", MoreThanHalfNum_Solution(nums, sizeof(nums)/sizeof(nums[0])));
    return 0;
}