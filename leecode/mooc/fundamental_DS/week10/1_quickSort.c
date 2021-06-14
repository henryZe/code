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

void Quicksort(int A[], int left, int right)
{
    if (cutoff <= right - left) {
        pivot = Median3(A, left, right);

        i = left;
        j = right - 1;
        while (1) {
            while (A[++i] < pivot);
            while (A[--j] > pivot);

            if (i < j)
                swap(&A[i], &A[j]);
            else
                break;
        }
        swap(&A[i], &A[right - 1]);
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
