#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define MAXTABLESIZE 100000 * 2
#define QQLEN 10
#define PWLEN 16
#define COUNTLEN 5

typedef char QQType[QQLEN + 1]; /* 关键词类型用字符串 */
typedef char PWType[PWLEN + 1]; /* 关键词类型用字符串 */
typedef int Index;                     /* 散列地址类型 */

typedef struct LNode *PtrToLNode;
struct LNode {
    QQType qq;
    PWType pw;
    PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

/******** 以上是单链表的定义 ********/

typedef struct TblNode *HashTable; /* 散列表类型 */
struct TblNode {   /* 散列表结点定义 */
    int TableSize; /* 表的最大长度 */
    List Heads;    /* 指向链表头结点的数组 */
};

int NextPrime(int N)
{
    /* 返回大于 N 且不超过 MAXTABLESIZE 的最小素数 */
    int i, p = (N % 2) ? N + 2 : N + 1; /*从大于 N 的下一个奇数开始 */

    while (p <= MAXTABLESIZE) {
        for (i = (int)sqrt(p); i > 2; i--)
            if (!(p % i))
                break; /* p不是素数 */
        if (i == 2)
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
    /* 以下分配链表头结点数组 */
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode));

    /* 初始化表头结点 */
    for (i = 0; i < H->TableSize; i++) {
        H->Heads[i].qq[0] = '\0';
        H->Heads[i].pw[0] = '\0';
        H->Heads[i].Next = NULL;
    }

    return H;
}

int Hash(QQType key, int TableSize)
{
    int len = strlen(key);

    if (len < COUNTLEN)
        return atoi(key) % TableSize;

    return atoi(key + len - COUNTLEN) % TableSize;
}

Position Find(HashTable H, QQType Key)
{
    Position P;
    int Pos;

    Pos = Hash(Key, H->TableSize); /* 初始散列位置 */
    P = H->Heads[Pos].Next; /* 从该链表的第1个结点开始 */

    /* 当未到表尾，并且Key未找到时 */
    while (P && strcmp(P->qq, Key))
        P = P->Next;

    return P; /* 此时P或者指向找到的结点，或者为NULL */
}

bool Insert(HashTable H, QQType Key, PWType pw)
{
    Position P, NewCell;
    int Pos;

    P = Find(H, Key);
    if (!P) { /* 关键词未找到，可以插入 */
        NewCell = (Position)malloc(sizeof(struct LNode));
        strcpy(NewCell->qq, Key);
        strcpy(NewCell->pw, pw);

        Pos = Hash(Key, H->TableSize); /* 初始散列位置 */

        /* 将NewCell插入为H->Heads[Pos]链表的第1个结点 */
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;

        // printf("insert pos %d\n", Pos);
        return true;

    } else { /* 关键词已存在 */
        return false;
    }
}

int newUser(HashTable hash, QQType qq, PWType pw)
{
    if (!Insert(hash, qq, pw)) {
        printf("ERROR: Exist\n");
        return -1;
    }

    printf("New: OK\n");
    return 0;
}

int logIn(HashTable hash, QQType qq, PWType pw)
{
    Position P = Find(hash, qq);

    if (!P) {
        printf("ERROR: Not Exist\n");
        return -1;
    }

    if (strcmp(P->pw, pw)) {
        printf("ERROR: Wrong PW\n");
        return -1;
    }

    printf("Login: OK\n");
    return 0;
}

int main(void)
{
    int num;
    scanf("%d\n", &num);

    HashTable hash = CreateTable(2 * num);

    char option;
    char qq[QQLEN + 1];
    char pw[PWLEN + 1];

    for (int i = 0; i < num; i++) {
        scanf("%c %s %s\n", &option, qq, pw);

        switch (option) {
        case 'L':
            logIn(hash, qq, pw);
            break;
        case 'N':
            newUser(hash, qq, pw);
            break;
        default:
            break;
        }
    }

    return 0;
}
