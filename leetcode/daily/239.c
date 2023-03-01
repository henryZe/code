void swap(int** a, int** b)
{
    int* tmp = *a;
    *a = *b, *b = tmp;
}

int cmp(int* a, int* b)
{
    return a[0] == b[0] ? a[1] - b[1] : a[0] - b[0];
}

struct Heap {
    // num & index
    int** heap;
    int size;
    int capacity;
};

void init(struct Heap* obj, int capacity)
{
    obj->size = 0;
    obj->heap = NULL;
    obj->capacity = capacity;
    obj->heap = malloc(sizeof(int*) * (obj->capacity + 1));
    for (int i = 1; i <= obj->capacity; i++) {
        obj->heap[i] = malloc(sizeof(int) * 2);
    }
}

void push(struct Heap* obj, int num0, int num1)
{
    int sub1 = ++(obj->size), sub2 = sub1 >> 1;

    (obj->heap[sub1])[0] = num0, (obj->heap[sub1])[1] = num1;

    while (sub2 > 0 &&
           cmp(obj->heap[sub2], obj->heap[sub1]) < 0) {
        swap(&(obj->heap[sub1]), &(obj->heap[sub2]));
        sub1 = sub2, sub2 = sub1 >> 1;
    }
}

void pop(struct Heap* obj)
{
    int sub = 1;

    swap(&(obj->heap[sub]), &(obj->heap[(obj->size)--]));

    while (sub <= obj->size) {
        int sub1 = sub << 1, sub2 = sub << 1 | 1;
        int maxSub = sub;
        if (sub1 <= obj->size &&
            cmp(obj->heap[maxSub], obj->heap[sub1]) < 0) {
            maxSub = sub1;
        }
        if (sub2 <= obj->size &&
            cmp(obj->heap[maxSub], obj->heap[sub2]) < 0) {
            maxSub = sub2;
        }
        if (sub == maxSub) {
            break;
        }
        swap(&(obj->heap[sub]), &(obj->heap[maxSub]));
        sub = maxSub;
    }
}

int* top(struct Heap* obj)
{
    return obj->heap[1];
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize)
{
    int len = numsSize - k + 1;
    int start = 0, end = 0;
    int cur = 0;
    int *res = malloc(sizeof(int) * len);

    struct Heap* q = malloc(sizeof(struct Heap));
    init(q, numsSize);

    for (end = 0; end < k; end++)
        push(q, nums[end], end);

    while (1) {
        if ((end - start) == k) {
            while (top(q)[1] < start) {
                pop(q);
            }
            res[cur++] = top(q)[0];
            start++;
        }

        if (end >= numsSize)
            // no more
            break;

        push(q, nums[end], end);
        end++;
    }

    *returnSize = len;
    return res;
}
