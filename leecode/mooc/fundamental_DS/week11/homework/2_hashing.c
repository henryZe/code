#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAXTABLESIZE 100000 /* 允许开辟的最大散列表长度 */

typedef int ElementType;    /* 关键词类型用整型 */
typedef int Index;          /* 散列地址类型 */
typedef Index Position;     /* 数据所在位置与散列地址是同一类型 */
/* 散列单元状态类型，分别对应：有合法元素、空单元、有已删除元素 */
typedef enum {
    Legitimate,
    Empty,
    Deleted,
} EntryType;

typedef struct HashEntry Cell; /* 散列表单元类型 */
struct HashEntry {
    ElementType Data; /* 存放元素 */
    EntryType Info;   /* 单元状态 */
};

typedef struct TblNode *HashTable; /* 散列表类型 */
struct TblNode {   /* 散列表结点定义 */
    int TableSize; /* 表的最大长度 */
    Cell *Cells;   /* 存放散列单元数据的数组 */
};

int NextPrime(int N)
{
    if (N == 1)
        return 2;

    /* 返回大于 N 且不超过 MAXTABLESIZE 的最小素数 */
    int i, p = (N % 2) ? N + 2 : N + 1; /*从大于 N 的下一个奇数开始 */

    while (p <= MAXTABLESIZE) {
        for (i = (int)sqrt(p); i > 2; i--)
            if (!(p % i))
                break; /* p不是素数 */
        if (i <= 2)
            break; /* for正常结束，说明p是素数 */
        else
            p += 2; /* 否则试探下一个奇数 */
    }

    return p;
}

HashTable CreateTable(int TableSize)
{
    HashTable H;
    int i;

    H = (HashTable)malloc(sizeof(struct TblNode));

    /* 保证散列表最大长度是素数 */
    H->TableSize = NextPrime(TableSize);
    /* 声明单元数组 */
    H->Cells = (Cell *)malloc(H->TableSize * sizeof(Cell));

    /* 初始化单元状态为“空单元” */
    for (i = 0; i < H->TableSize; i++)
        H->Cells[i].Info = Empty;

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
    while (H->Cells[NewPos].Info != Empty && H->Cells[NewPos].Data != Key) {
        if (CNum >= H->TableSize) {
            /* quadratic probing failed */
            NewPos = -1;
            break;
        }

        if (++CNum) {
            NewPos = CurrentPos + CNum * CNum;
            if (NewPos >= H->TableSize)
                NewPos %= H->TableSize; /* 调整为合法地址 */
        }
    }

    return NewPos; /* 此时NewPos或者是Key的位置，或者是一个空单元的位置（表示找不到）*/
}

int Insert(HashTable H, ElementType Key)
{
    Position Pos = Find(H, Key); /* 先检查Key是否已经存在 */

    if (Pos < 0)
        return Pos;

    if (H->Cells[Pos].Info != Legitimate) { /* 如果这个单元没有被占，说明Key可以插入在此 */
        H->Cells[Pos].Info = Legitimate;
        H->Cells[Pos].Data = Key;
    }

    return Pos;
}

int main(void)
{
    int tableSize, num;
    scanf("%d %d\n", &tableSize, &num);

    HashTable hash = CreateTable(tableSize);

    int n, pos;
    for (int i = 0; i < num; i++) {
        scanf("%d ", &n);
        pos = Insert(hash, n);

        if (pos < 0)
            printf("-");
        else
            printf("%d", pos);

        if (i < (num - 1))
            printf(" ");
        else
            printf("\n");
    }

    return 0;
}
