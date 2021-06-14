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

    for (i = 0; i < NumElements; i++, RightEnd--)
        A[RightEnd] = tmpA[RightEnd];
}

void MSort(int A[], int TmpA[], int L, int RightEnd)
{
    int Center;

    if (L < RightEnd) {
        Center = (L + RightEnd) / 2;
        MSort(A, TmpA, L, Center);
        MSort(A, TmpA, Center + 1, RightEnd);
        Merge(A, TmpA, L, Center + 1, RightEnd);
    }
}

void Merge_sort(int A[], int N)
{
    int *TmpA = malloc(N * sizeof(int));

    if (!TmpA)
        Error("空间不足");

    MSort(A, TmpA, 0, N - 1);
    free(TmpA);
}
