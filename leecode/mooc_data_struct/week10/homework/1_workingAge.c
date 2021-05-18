#include <stdlib.h>
#include <stdio.h>

#define BucketNum 51

int bucket_sort(int A[], int N)
{
    int i;
    int B[BucketNum];

    for (i = 0; i < BucketNum; i++)
        B[i] = 0;

    for (i = 0; i < N; i++)
        B[A[i]]++;

    for (i = 0; i < BucketNum; i++) {
        if (B[i])
            printf("%d:%d\n", i, B[i]);
    }

    return 0;
}

int main(void)
{
    int num;
    scanf("%d\n", &num);

    int tmp;
    int *array = malloc(sizeof(int) * num);

    for (int i = 0; i < num; i++) {
        scanf("%d", array + i);
    }

    bucket_sort(array, num);

    return 0;
}