#include <stdio.h>
#include <stdlib.h>

// 直接计算
// int countOne(int x)
// {
//     int one = 0;
//     while (x) {
//         x &= (x - 1);
//         one++;
//     }
//     return one;
// }
// int* countBits(int num, int* returnSize)
// {
//     int *arr = malloc(sizeof(int) * (num + 1));
//     *returnSize = num + 1;
// 
//     for (int i = 0; i < num + 1; i++) {
//         arr[i] = countOne(i);
//     }
//     return arr;
// }

// 动态规划——最高有效位
// int* countBits(int num, int* returnSize)
// {
//     int *arr = malloc(sizeof(int) * (num + 1));
//     *returnSize = num + 1;
// 
//     int highBit = 0;
//     arr[0] = 0;
//     for (int i = 1; i < num + 1; i++) {
//         if ((i & (i - 1)) == 0) {
//             highBit = i;
//         }
//         arr[i] = arr[i - highBit] + 1;
//     }
// 
//     return arr;
// }

// 动态规划——最低有效位
// int* countBits(int num, int* returnSize)
// {
//     int *arr = malloc(sizeof(int) * (num + 1));
//     *returnSize = num + 1;
// 
//     arr[0] = 0;
//     for (int i = 1; i < num + 1; i++) {
//         arr[i] = arr[i>>1] + (i&1);
//     }
// 
//     return arr;
// }

// 动态规划——最低设置位
int* countBits(int num, int* returnSize)
{
    int *arr = malloc(sizeof(int) * (num + 1));
    *returnSize = num + 1;

    arr[0] = 0;
    for (int i = 1; i < num + 1; i++) {
        arr[i] = arr[i & (i-1)] + 1;
    }

    return arr;
}

int main(void)
{
    int size;
    int *arr = countBits(5, &size);

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
