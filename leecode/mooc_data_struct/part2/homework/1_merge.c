#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Merge( List L1, List L2 );

void self_print(List L)
{
    for (List it = L; it; it = it->Next)
        printf("-> %d ", it->Data);
    printf("\n");
}

int main(void)
{
    List L1 = NULL, L2 = NULL, L;

    L = Merge(L1, L2);
    self_print(L);

    return 0;
}

List Merge( List L1, List L2 )
{
    if (!L1)
        return L2;
    if (!L2)
        return L1;

    List temp;

    temp = L1;
    L1 = L1->Next;
    temp->Next = NULL;

    temp = L2;
    L2 = L2->Next;
    temp->Next = NULL;

    List head = malloc(sizeof(struct Node));
    List L = head;
    while (L1 && L2) {
        if (L1->Data > L2->Data) {
            L->Next = L2;
            L2 = L2->Next;
        } else {
            L->Next = L1;
            L1 = L1->Next;
        }
        L = L->Next;
    }

    if (!L1) {
        L->Next = L2;
        L2 = NULL;
    } else {
        L->Next = L1;
        L1 = NULL;
    }

    return head;
}