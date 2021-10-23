#include "stdio.h"
#include "string.h"
#include "stdlib.h"

struct ListNode {
    int val;
    struct ListNode *next;
};

int val(struct ListNode *node)
{
    if (!node)
        return 0;
    return node->val;
}

struct ListNode *malloc_listnode(int val, struct ListNode *next)
{
    struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = next;
    return node;
}

struct ListNode* ReverseList(struct ListNode* pHead ) {
    // write code here
    struct ListNode* prev = NULL;
    struct ListNode* cur = pHead;
    struct ListNode* next = NULL;

    while (cur) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    return prev;
}

struct ListNode* addInList(struct ListNode* head1, struct ListNode* head2)
{
    int num = 0;
    int add1 = 0;
    struct ListNode *l1 = ReverseList(head1);
    struct ListNode *l2 = ReverseList(head2);
    struct ListNode *node, *prev = NULL;

    while (l1 || l2) {
        num = val(l1) + val(l2) + add1;
        add1 = num / 10;
        node = malloc_listnode(num % 10, prev);
        prev = node;

        if (l1)
            l1 = l1->next;
        if (l2)
            l2 = l2->next;
    }
    if (add1)
        node = malloc_listnode(add1, prev);

    return node;
}

int main(void)
{
    struct ListNode l12 = {
        .val = 7,
        .next = NULL,
    };
    struct ListNode l11 = {
        .val = 3,
        .next = &l12,
    };
    struct ListNode l1 = {
        .val = 9,
        .next = &l11,
    };

    struct ListNode l21 = {
        .val = 3,
        .next = NULL,
    };
    struct ListNode l2 = {
        .val = 6,
        .next = &l21,
    };

    struct ListNode *l = addInList(&l1, &l2);
    while (l) {
        printf("%d -> ", l->val);
        l = l->next;
    }
    printf("\n");
    
    return 0;
}
