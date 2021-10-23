#include <stdio.h>
#include <stdlib.h>

int maxLength(int* arr, int arrLen )
{
    int *begin = arr;
    int *cur = arr + 1;
    int max = 0;
    int len;

    for (int i = 1; i < arrLen; i++) {
        int *temp = begin;
        while (temp != cur) {
            if (*temp == *cur)
                break;
            temp++;
        }
        if (temp != cur) {
            len = cur - begin;
            max = max < len ? len : max;
            begin = temp + 1;
        }
        cur++;
    }

    len = cur - begin;
    max = max < len ? len : max;
    return max;
}

int main(void)
{
    int num;
    scanf("%d\n", &num);

    int *a = malloc(num * sizeof(int));
    for (int i = 0; i < num; i++) {
        scanf("%d,", a + i);
    }

    printf("%d\n", maxLength(a, num));
    return 0;
}