#include <stdlib.h>
#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* Merge(struct ListNode* pHead1, struct ListNode* pHead2 )
{
    struct ListNode head;
    struct ListNode *cur = &head;

    while (pHead1 && pHead2) {
        if (pHead1->val <= pHead2->val) {
            cur->next = pHead1;

            cur = cur->next;
            pHead1 = pHead1->next;
        } else {
            cur->next = pHead2;

            cur = cur->next;
            pHead2 = pHead2->next;
        }
    }

    if (pHead1) {
        cur->next = pHead1;
    } else {
        cur->next = pHead2;
    }

    return head.next;
}
