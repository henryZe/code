#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool insertion_sort(int A[], int N, int B[])
{
    bool flag = false;

    for (int P = 1; P < N; P++) {
        int i, tmp = A[P];

        for (i = P; i > 0 && A[i - 1] > tmp; i--) {
            A[i] = A[i - 1];
        }

        A[i] = tmp;

        if (flag)
            break;

        if (memcmp(A, B, N * sizeof(int)) == 0)
            flag = true;
    }

    return flag;
}

void merge(int A[], int tmpA[], int L, int R, int RightEnd)
{
    /* 左边终点位置。假设左右两列挨着 */
    int LeftEnd = R - 1;

    /* 存放结果的数组的初始位置 */
    int cur = L;

    int NumElements = RightEnd - L + 1;

    while (L <= LeftEnd && R <= RightEnd) {
        if (A[L] <= A[R])
            tmpA[cur++] = A[L++];
        else
            tmpA[cur++] = A[R++];
    }

    /* 直接复制左边剩下的 */
    while (L <= LeftEnd)
        tmpA[cur++] = A[L++];

    /*直接复制右边剩下的 */
    while (R <= RightEnd)
        tmpA[cur++] = A[R++];

    for (int i = 0; i < NumElements; i++, RightEnd--)
        A[RightEnd] = tmpA[RightEnd];
}

void merge_pass(int A[], int TmpA[], int N, int length)
{
    int i, j;

    /* length = 当前有序子列的长度 */
    for (i = 0; i <= N - 2 * length; i += 2 * length)
        merge(A, TmpA, i, i + length, i + 2 * length - 1);

    if (i + length < N) {
        /* 归并最后2个子列 */
        merge(A, TmpA, i, i + length, N - 1);
    } else {
        /* 最后只剩1个子列 */
        for (j = i; j < N; j++)
            TmpA[j] = A[j];
    }
}

bool merge_sort(int A[], int N, int B[])
{
    bool flag = false;
    int length = 1; /* 初始化子序列长度*/
    int *TmpA = (int *)malloc(N * sizeof(int));

    if (!TmpA)
        return false;

    while (length < N) {
        merge_pass(A, TmpA, N, length);
        length *= 2;

        if (flag) {
            memcpy(A, TmpA, N * sizeof(int));
            break;
        }

        if (memcmp(TmpA, B, N * sizeof(int)) == 0)
            flag = true;

        merge_pass(TmpA, A, N, length);
        length *= 2;

        if (flag)
            break;

        if (memcmp(A, B, N * sizeof(int)) == 0)
            flag = true;
    }
    free(TmpA);

    return flag;
}

int main(void)
{
    int size;
    scanf("%d\n", &size);

    int *array = (int *)malloc(sizeof(int) * size);
    int *array2 = (int *)malloc(sizeof(int) * size);
    int *partial = (int *)malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        scanf("%d ", array + i);
    }
    memcpy(array2, array, sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        scanf("%d ", partial + i);
    }

    if (insertion_sort(array, size, partial))
        printf("Insertion Sort\n");
    else {
        memcpy(array, array2, sizeof(int) * size);
        merge_sort(array, size, partial);
        printf("Merge Sort\n");
    }

    for (int i = 0; i < size; i++) {
        if (i == size - 1)
            printf("%d\n", array[i]);
        else
            printf("%d ", array[i]);
    }

    return 0;
}