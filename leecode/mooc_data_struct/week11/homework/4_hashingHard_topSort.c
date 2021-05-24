#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct edge {
    int w;
    struct edge *Next;
};

struct Vnode {
    int value;
    int inDegree;
    struct edge FirstEdge;
};

struct Graph {
    int Nv;             /* 顶点数 */
    struct Vnode *G;    /* 邻接表 */
};

#define QUEUE_SIZE 1001
struct queue {
    int *queue;
    int front;
    int rear;
};

struct Graph *create_graph(int v_num)
{
    struct Graph *g = malloc(sizeof(struct Graph));

    g->Nv = v_num;
    g->G = malloc(sizeof(struct Vnode) * v_num);
    for (int i = 0; i < v_num; i++) {
        g->G[i].value = -1;
        g->G[i].inDegree = -1;
        g->G[i].FirstEdge.Next = NULL;
    }

    return g;
}

int insert_edge(struct Graph *g, int i, int value)
{
    if (value < 0)
        // ignore
        return 0;

    g->G[i].value = value;

    int origin = value % g->Nv;

    if (origin == i) {
        g->G[i].inDegree = 0;
        return 0;
    }

    if (i > origin)
        g->G[i].inDegree = i - origin;
    else
        g->G[i].inDegree = g->Nv + i - origin;

    for (int j = origin; j != i; j = (j + 1) % g->Nv) {
        struct edge *e = malloc(sizeof(struct edge));
        e->w = i;
        e->Next = g->G[j].FirstEdge.Next;
        g->G[j].FirstEdge.Next = e;
    }

    return 0;
}

#define MAXTABLESIZE 100000 /* 允许开辟的最大散列表长度 */

typedef int ElementType;    /* 关键词类型用整型 */
typedef int Index;          /* 散列地址类型 */
typedef Index Position;     /* 数据所在位置与散列地址是同一类型 */
/* 散列单元状态类型，分别对应：有合法元素、空单元、有已删除元素 */

typedef struct TblNode *HashTable; /* 散列表类型 */
struct TblNode {   /* 散列表结点定义 */
    int TableSize; /* 表的最大长度 */
    ElementType *Cells;   /* 存放散列单元数据的数组 */
};

HashTable CreateTable(int TableSize)
{
    HashTable H;
    int i;

    H = (HashTable)malloc(sizeof(struct TblNode));

    /* 保证散列表最大长度是素数 */
    H->TableSize = TableSize;
    /* 声明单元数组 */
    H->Cells = (ElementType *)malloc(H->TableSize * sizeof(ElementType));

    return H;
}

int Hash(ElementType key, int TableSize)
{
    return key % TableSize;
}

Position Find(HashTable H, ElementType Key)
{
    Position CurrentPos, NewPos;
    int CNum = 0; /* 记录冲突次数 */

    NewPos = CurrentPos = Hash(Key, H->TableSize); /* 初始散列位置 */

    /* 当该位置的单元非空，并且不是要找的元素时，发生冲突 */
    while (H->Cells[NewPos] != Key) {
        if (CNum >= H->TableSize) {
            /* quadratic probing failed */
            NewPos = -1;
            break;
        }

        if (++CNum) {
            NewPos = CurrentPos + CNum;
            if (NewPos >= H->TableSize)
                NewPos -= H->TableSize; /* 调整为合法地址 */
        }
    }

    return NewPos; /* 此时NewPos或者是Key的位置，或者是一个空单元的位置（表示找不到）*/
}

struct heap {
    int *weight;
    int capacity;
    int size;
};

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

bool IsFull(struct heap *h)
{
    return h->capacity == h->size;
}

bool IsEmpty(struct heap *h)
{
    return h->size == 0;
}

int min_heap_push(struct heap *h, int x)
{
    int *d = h->weight;

    if (IsFull(h))
        return -1;

    d[++(h->size)] = x;

    for (int i = h->size; d[i] < d[i >> 1]; i >>= 1) {
        swap(&d[i], &d[i >> 1]);
    }

    return 0;
}

int min_heap_pop(struct heap *h)
{
    int *d = h->weight;
    int min = d[1];

    if (IsEmpty(h))
        return -1;

    d[1] = d[h->size--];
    for (int parent = 1, child = parent << 1; child <= h->size; parent = child, child <<= 1) {
        // there is right child or not
        if (child < h->size) {
            // choose smaller one
            if (d[child] > d[child + 1]) {
                child++;
            }
        }

        // stop search
        if (d[child] >= d[parent]) {
            break;
        }

        swap(d + child, d + parent);
    }

    return min;
}

struct heap *create_min_heap(int num)
{
    struct heap *h = malloc(sizeof(struct heap));

    h->weight = malloc(sizeof(int) * (num + 1));
    h->capacity = num;
    h->size = 0;

    h->weight[0] = INT_MIN;
    return h;
}

int main(void)
{
    int tableSize, count = 0;
    scanf("%d\n", &tableSize);

    struct Graph *g = create_graph(tableSize);
    HashTable Hash = CreateTable(tableSize);

    int value;
    for (int i = 0; i < tableSize; i++) {
        scanf("%d ", &value);

        if (value >= 0)
            count++;

        insert_edge(g, i, value);
        Hash->Cells[i] = value;
    }

    struct heap *heap = create_min_heap(tableSize);

    for (int i = 0; i < tableSize; i++) {
        if (g->G[i].inDegree == 0)
            min_heap_push(heap, g->G[i].value);
    }

    while (!IsEmpty(heap)) {
        int v = min_heap_pop(heap);
        if (--count)
            printf("%d ", v);
        else
            printf("%d\n", v);

        int i = Find(Hash, v);

        for (struct edge *e = g->G[i].FirstEdge.Next; e; e = e->Next) {
            if (--g->G[e->w].inDegree == 0)
                min_heap_push(heap, g->G[e->w].value);
        }
    }

    return 0;
}
