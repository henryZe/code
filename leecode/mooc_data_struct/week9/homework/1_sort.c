#include <stdlib.h>
#include <stdio.h>

#define swap(x, y) do { int tmp = x; x = y; y = tmp; } while (0)

void bubble_sort(int A[], int N)
{
    for (int P = N - 1; P >= 0; P--) {
        int flag = 0;

        for (int i = 0; i < P; i++) {
            if (A[i] > A[i+1]) {
                swap(A[i], A[i + 1]);
                flag = 1;
            }
        }

        if (flag == 0)
            /* already sorted, optimize */
            break;
    }
}

void insertion_sort(int A[], int N)
{
    for (int P = 1; P < N; P++) {
        int i, tmp = A[P];

        for (i = P; i > 0 && A[i - 1] > tmp; i--) {
            A[i] = A[i - 1];
        }

        A[i] = tmp;
    }
}

void shell_sort(int A[], int N)
{
    for (int D = N/2; D > 0; D /= 2) {  // Shell 增量序列

        // insertion sort
        for (int P = D; P < N; P++) {
            int i, tmp = A[P];
            for (i = P; i >= D && A[i - D] > tmp; i -= D) {
                A[i] = A[i - D];
            }
            A[i] = tmp;
        }
    }
}

void Shell_withSedgewick(int A[], int N)
{
    int Si, D, P, i;
    int Tmp;

    int Sedgewick[] = { 16001, 8929, 3905, 2161, 929, 505, 209, 109, 41, 19, 5, 1, 0 };

    for (Si = 0; Sedgewick[Si] >= N; Si++);

    for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si]) {
        for (P = D; P < N; P++) {
            Tmp = A[P];

            for (i = P; i >= D && A[i-D] > Tmp; i -= D)
                A[i] = A[i-D];

            A[i] = Tmp;
        }
    }
}

int ScanForMin(int A[], int start, int end)
{
    int pos = start;

    for (int i = pos + 1; i <= end; i++) {
        if (A[pos] > A[i])
            pos = i;
    }

    return pos;
}

void selection_sort(int A[], int N)
{
    for (int i = 0; i < N; i++) {
        /* 从A[i]到A[N-1]中找最小元，并将其位置赋给MinPosition */
        /* 可优化 */
        int MinPosition = ScanForMin(A, i, N - 1);

        /* 将未排序部分的最小元换到有序部分的最后位置*/
        swap(A[i], A[MinPosition]);
    }
}

void siftDown(int *array, int parent, int size)
{
    while ((parent << 1) + 1 < size) {
        int child = (parent << 1) + 1;    // left son
        if ((child + 1) < size && array[child] > array[child + 1]) {
            child++;                      // right son
        }
        if (array[child] >= array[parent]) {
            break;
        }
        swap(array[child], array[parent]);

        parent = child;
    }
}

int heappop(int *heap, int size)
{
    int tmp = heap[0];

    if (!size)
        return -1;

    heap[0] = heap[size - 1];
    siftDown(heap, 0, size - 1);

    return tmp;
}

void heapify_MinHeap(int *A, int size)
{
    for (int i = (size >> 1) - 1; i >= 0; i--)
        siftDown(A, i, size);
}

void Heap_sort_withExtraSpace(int A[], int N)
{
    int i, tmp[N];

    /* O(N) */
    heapify_MinHeap(A, N);

    for (i = 0; i < N; i++) {
        /* O(logN) */
        tmp[i] = heappop(A, N - i);
    }

    /* O(N) */
    for (i = 0; i < N; i++) {
        A[i] = tmp[i];
    }
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

void HeapSort(int A[], int N)
{
    /* 堆排序 */
    int i;

    for (i = N/2 - 1; i >= 0; i--)
        /* 建立最大堆 */
        PercDown( A, i, N );

    for (i = N-1; i > 0; i--) {
        /* 删除最大堆顶 */
        swap(A[0], A[i]);
        /* resort A[0] */
        PercDown(A, 0, i);
    }
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

void merge_sort(int A[], int N)
{
    int length = 1; /* 初始化子序列长度*/
    int *TmpA = malloc(N * sizeof(int));

    if (!TmpA)
        return;

    while (length < N) {
        merge_pass(A, TmpA, N, length);
        length *= 2;
        merge_pass(TmpA, A, N, length);
        length *= 2;
    }
    free(TmpA);
}

int Median3(int A[], int Left, int Right)
{
    int Center = (Left + Right) / 2;

    if (A[Left] > A[Center])
        swap(A[Left], A[Center]);
    if (A[Left] > A[Right])
        swap(A[Left], A[Right]);
    if (A[Center] > A[Right])
        swap(A[Center], A[Right]);
    /* A[Left] <= A[Center] <= A[Right] */

    swap(A[Center], A[Right - 1]);

    /* 只需考虑 A[Left + 1] ... A[Right - 2] */
    /* return pivot */
    return A[Right - 1];
}

#define CUTOFF 200

void Quicksort(int A[], int left, int right)
{
    int i, j;
    int cutoff = CUTOFF;
    int pivot;

    if (cutoff <= right - left) {
        pivot = Median3(A, left, right);

        i = left;
        j = right - 1;
        while (1) {
            while (A[++i] < pivot);
            while (A[--j] > pivot);

            if (i < j)
                swap(A[i], A[j]);
            else
                break;
        }
        swap(A[i], A[right - 1]);
        Quicksort(A, left, i - 1);
        Quicksort(A, i + 1, right);
    } else {
        insertion_sort(A + left, right - left + 1);
    }
}

void quick_sort(int A[], int N)
{
    Quicksort(A, 0, N - 1);
}

#define MaxDigit 4
#define Radix 10

struct Node {
    int key;
    struct Node *next;
};

/* 桶头结点 */
struct bucket {
    struct Node *head;
    struct Node *tail;
};

int GetDigit(int X, int D)
{
    int d, i;
    for (i = 1; i <= D; i++) {
        d = X % Radix;
        X /= Radix;
    }
    return d;
}

void LSDRadixSort(int A[], int N)
{
    /* 基数排序 - 次位优先 */
    int Di, i;
    struct bucket B[Radix];
    struct Node *tmp, *p, *List = NULL;

    for (i = 0; i < Radix; i++) /* 初始化每个桶为空链表 */
        B[i].head = B[i].tail = NULL;

    for (i = 0; i < N; i++) { /* 将原始序列逆序存入初始链表List */
        tmp = malloc(sizeof(struct Node));
        tmp->key = A[i];
        tmp->next = List;
        List = tmp;
    }

    /* 下面开始排序 */
    int D = 1, bucket_count;

    do {
        /* 下面是分配的过程 */
        p = List;
        while (p) {
            Di = GetDigit(p->key, D); /* 获得当前元素的当前位数字 */

            /* 从 List 中摘除 */
            tmp = p;
            p = p->next;

            /* 插入B[Di]号桶尾 */
            tmp->next = NULL;
            if (B[Di].head == NULL)
                B[Di].head = B[Di].tail = tmp;
            else {
                B[Di].tail->next = tmp;
                B[Di].tail = tmp;
            }
        }

        /* 下面是收集的过程 */
        List = NULL;
        bucket_count = 0;
        for (Di = Radix - 1; Di >= 0; Di--) { /* 将每个桶的元素顺序收集入List */
            if (B[Di].head) { /* 如果桶不为空 */
                /* 整桶插入List表头 */
                B[Di].tail->next = List;
                List = B[Di].head;
                B[Di].head = B[Di].tail = NULL; /* 清空桶 */
                bucket_count++;
            }
        }
        D++;
    // when bucket_count == 1, means the array has been sorted out.
    } while (bucket_count != 1);

    /* 将List倒入A[]并释放空间 */
    for (i = 0; i < N; i++) {
        tmp = List;
        List = List->next;
        A[i] = tmp->key;
        free(tmp);
    }
}

int main(void)
{
    int num;
    scanf("%d\n", &num);

    int tmp;
    int *array = malloc(sizeof(int) * num);

    for (int i = 0; i < num; i++) {
        scanf("%d", &tmp);
        array[i] = tmp;
    }

    // bubble_sort(array, num);
    // insertion_sort(array, num);
    // shell_sort(array, num);
    // Shell_withSedgewick(array, num);
    // selection_sort(array, num);
    // Heap_sort_withExtraSpace(array, num);
    // HeapSort(array, num);
    // merge_sort(array, num);
    // quick_sort(array, num);
    LSDRadixSort(array, num);

    for (int i = 0; i < num; i++) {
        if (i == num - 1)
            printf("%d\n", array[i]);
        else
            printf("%d ", array[i]);
    }

    return 0;
}