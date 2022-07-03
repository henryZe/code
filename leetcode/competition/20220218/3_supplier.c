#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define PRINTSUCCESS(x, y) x ## y
#define EXPECT_EQ(x, y) { assert(x == y); printf("assert success\n"); }
#define FUNCTION_NAME(x, y, z) x ## y ## z
#define TEST(x, y) void FUNCTION_NAME(test, x, y)(void)
#define CALL_TEST(x, y) FUNCTION_NAME(test, x, y)()

#define SIZE 100001
#define MODNUMBER 1000000007

#define SUPPLY_PRICE 0
#define SUPPLY_NUMBER 1

struct node {
    int value;
    int index;
};

struct heapq {
    struct node heap[SIZE + 1];
    int heapSize;
};

void swap(struct node *a, struct node *b)
{
    struct node tmp = *a;
    *a = *b;
    *b = tmp;
}

struct heapq *heapinit(void)
{
    struct heapq *h = malloc(sizeof(struct heapq));
    h->heapSize = 0;
    return h;
}

// insert: O(logN)
void heappush(struct heapq *heap, struct node *x)
{
    struct node *h = heap->heap;

    if (heap->heapSize == SIZE)
        return;

    h[++(heap->heapSize)] = *x;

    for (int i = heap->heapSize; i > 1 && h[i].value < h[i >> 1].value; i >>= 1) {
        swap(&h[i], &h[i >> 1]);
    }
}

// search: O(logN)
int heappop(struct heapq *heap, struct node *x)
{
    struct node *h = heap->heap;
    *x = h[1];
    int i = 1, j = 2;

    if (!heap->heapSize) {
        return -1;
    }

    h[1] = h[heap->heapSize--];
    while (j <= heap->heapSize) {
        if (h[j + 1].value < h[j].value)
            j++;

        if (h[i].value > h[j].value) {
            swap(&h[i], &h[j]);
            i = j;
            j <<= 1;
            continue;
        }

        break;
    }

    return 0;
}

int GetMinAmount(int **suppliers, int suppliersSize, int *suppliersColSize, int total)
{
    struct node tmp;
    struct heapq *h;

    h = heapinit();

    for (int i = 0; i < suppliersSize; i++) {
        tmp.value = suppliers[i][0];
        tmp.index = i;
        heappush(h, &tmp);
    }

    long long ret = 0;
    for (int i = 0; i < total; i++) {
        heappop(h, &tmp);
        ret += tmp.value;

        suppliers[tmp.index][SUPPLY_PRICE]++;
        suppliers[tmp.index][SUPPLY_NUMBER]--;

        if (suppliers[tmp.index][SUPPLY_NUMBER]) {
            tmp.value = suppliers[tmp.index][SUPPLY_PRICE];
            heappush(h, &tmp);
        }
    }

    ret %= MODNUMBER;
    printf("ret = %lld\n", ret);
    return ret;
}

TEST(TestGetMinAmount, OneItem)
{
    int item[2] = {20, 2};
    int *suppliers[] = {item};
    int suppliersColSize[1] = {2};
    int ret = GetMinAmount(suppliers, 1,  suppliersColSize, 2);
    EXPECT_EQ(ret, (20 + 21));
}

TEST(TestGetMinAmount, TowItems)
{
    int item1[2] = {9, 4}; // 9, 10, 11
    int item2[2] = {11, 5}; // 11
    int *suppliers[] = {item1, item2};
    int suppliersColSize[] = {2, 2};
    int ret = GetMinAmount(suppliers, sizeof(suppliers) / sizeof(int*),  suppliersColSize, 4);
    EXPECT_EQ(ret, (9 + 10 + 11 + 11));
}

TEST(TestGetMinAmount, TowItemsAndItemNumZero)
{
    int item1[2] = {9, 1}; // 9
    int item2[2] = {11, 5}; // 11, 12, 13
    int *suppliers[] = {item1, item2};
    int suppliersColSize[] = {2, 2};
    int ret = GetMinAmount(suppliers, sizeof(suppliers) / sizeof(int*),  suppliersColSize, 4);
    EXPECT_EQ(ret, (9 + 11 + 12 + 13));
}

TEST(TestGetMinAmount, ThreeItems)
{
    int item1[2] = {9, 4}; // 9, 10, 11
    int item2[2] = {11, 5}; // 11
    int item3[2] = {11, 4}; // 11
    int *suppliers[] = {item1, item2, item3};
    int suppliersColSize[] = {2, 2, 2};
    int ret = GetMinAmount(suppliers, sizeof(suppliers) / sizeof(int*),  suppliersColSize, 5);
    EXPECT_EQ(ret, (9 + 10 + 11 + 11 + 11));
}

TEST(TestGetMinAmount, ThreeItems2)
{
    int item1[2] = {9, 4}; // 9, 10, 11, 12
    int item2[2] = {11, 5}; // 11
    int item3[2] = {11, 4}; // 11
    int *suppliers[] = {item1, item2, item3};
    int suppliersColSize[] = {2, 2, 2};
    int ret = GetMinAmount(suppliers, sizeof(suppliers) / sizeof(int*),  suppliersColSize, 6);
    EXPECT_EQ(ret, (9 + 10 + 11 + 11 + 11 + 12));
}

TEST(TestGetMinAmount, LargeBuyTimes)
{
    int item[2] = {1, 1000000000};
    int *suppliers[] = {item};
    int suppliersColSize[1] = {2};
    int ret = GetMinAmount(suppliers, 1,  suppliersColSize, 1000000000);
    EXPECT_EQ(ret, 21);
}

TEST(TestGetMinAmount, HighPriceAndLargeBuyTimes)
{
    int item[2] = {1000000000, 1000000000};
    int *suppliers[] = {item};
    int suppliersColSize[1] = {2};
    int ret = GetMinAmount(suppliers, 1,  suppliersColSize, 1000000000);
    EXPECT_EQ(ret, 77);
}

TEST(TestGetMinAmount, LargeBuyTimesAndManyProviders)
{
    int item1[2] = {1, 1000000000};
    int item2[2] = {1, 1000000000};
    int *suppliers[] = {item1, item2};
    int suppliersColSize[] = {2, 2};
    int ret = GetMinAmount(suppliers, sizeof(suppliers) / sizeof(int*),  suppliersColSize, 1000000000);
    EXPECT_EQ(ret, 750000014);
}

TEST(TestGetMinAmount, LargeBuyTimesAndManyManyProviders)
{
    int suppliersSize = 100000;
    int *buf = (int*)malloc(sizeof(int) * suppliersSize * 2);
    int **suppliers = (int**)malloc(sizeof(int*) * suppliersSize);
    int *suppliersColSize = (int*)malloc(sizeof(int) * suppliersSize);

    for (int i = 0; i < suppliersSize; i++) {
        int *item = &buf[i * 2];
        item[0] = 1;
        item[1] = 1000000000;
        suppliers[i] = item;
        suppliersColSize[i] = 2;
    }

    int total = 1000000000;
    int ret = GetMinAmount(suppliers, suppliersSize,  suppliersColSize, total);
    EXPECT_EQ(ret, 499965000);

    free(buf);
    free(suppliers);
    free(suppliersColSize);
}

int main(void)
{
    CALL_TEST(TestGetMinAmount, OneItem);
    CALL_TEST(TestGetMinAmount, TowItems);
    CALL_TEST(TestGetMinAmount, TowItemsAndItemNumZero);
    CALL_TEST(TestGetMinAmount, ThreeItems);
    CALL_TEST(TestGetMinAmount, ThreeItems2);
    CALL_TEST(TestGetMinAmount, LargeBuyTimes);
    CALL_TEST(TestGetMinAmount, HighPriceAndLargeBuyTimes);
    CALL_TEST(TestGetMinAmount, LargeBuyTimesAndManyProviders);
    CALL_TEST(TestGetMinAmount, LargeBuyTimesAndManyManyProviders);

    return 0;
}