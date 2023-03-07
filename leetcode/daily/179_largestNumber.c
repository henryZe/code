#include <stdlib.h>
#include <string.h>

int compare(int *x, int *y)
{
    long long sx = 10, sy = 10;

    while (sx <= *x) {
        sx *= 10;
    }
    while (sy <= *y) {
        sy *= 10;
    }

    // decrease order, y - x
    return sx * (*y) + (*x) - sy * (*x) - (*y);
}

char * largestNumber(int* nums, int numsSize)
{
    char *str = malloc(sizeof(char) * numsSize * 10);
    memset(str, 0, numsSize * 10);

    qsort(nums, numsSize, sizeof(int), compare);

    char tmp[16];
    for (int i = 0; i < numsSize; i++) {
        sprintf(tmp, "%d", nums[i]);
        strcat(str, tmp);
    }

    // not return '00' but '0'
    while (str[0] == '0' && strlen(str) > 1)
        str += 1;

    return str;
}
