#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define swap(x, y) { int tmp = x; x = y; y = tmp; }

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

void PercDown(int A[], int p, int N)
{
    /* PercDown(MaxHeap H, int p) */
    /* 将 N 个元素的数组中以 A[p] 为根的子堆调整为最大堆 */
    int Parent, Child;
    int X;

    X = A[p]; /* 取出根结点存放的值 */
    for (Parent = p; (Parent * 2 + 1) < N; Parent = Child) {
        // left son
        Child = Parent * 2 + 1;

        if ((Child != N - 1) && (A[Child] < A[Child + 1]))
            /* Child指向左右子结点的较大者 */
            // right son
            Child++;

        if (X >= A[Child])
            break; /* 找到了合适位置 */
        else
            /* 下滤X */
            A[Parent] = A[Child];
    }
    A[Parent] = X;
}

void HeapSort(int A[], int N, int B[])
{
    /* 堆排序 */
    int i;
    bool flag = false;

    for (i = N/2 - 1; i >= 0; i--)
        /* 建立最大堆 */
        PercDown( A, i, N );

    for (i = N-1; i > 0; i--) {
        /* 删除最大堆顶 */
        swap(A[0], A[i]);
        /* resort A[0] */
        PercDown(A, 0, i);

        if (flag)
            break;

        if (memcmp(A, B, sizeof(int) * N) == 0)
            flag = true;
    }
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
        HeapSort(array, size, partial);
        printf("Heap Sort\n");
    }

    for (int i = 0; i < size; i++) {
        if (i == size - 1)
            printf("%d\n", array[i]);
        else
            printf("%d ", array[i]);
    }

    return 0;
}