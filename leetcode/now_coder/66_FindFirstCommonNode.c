#include "stdlib.h"

struct ListNode {
    int val;
    struct ListNode *next;
};

// a' + c + b' == b' + c + a'
struct ListNode* FindFirstCommonNode(struct ListNode* pHead1, struct ListNode* pHead2 ) {
    // write code here
    struct ListNode* p1 = pHead1;
    struct ListNode* p2 = pHead2;

	while (p1 != p2) {
        if (p1 == NULL)
            p1 = pHead2;
        else
            p1 = p1->next;

        if (p2 == NULL)
            p2 = pHead1;
        else
            p2 = p2->next;
    }

    return p1;
}
