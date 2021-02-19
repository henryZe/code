#include "stdlib.h"
#include "stdio.h"

struct ListNode {
    int val;
    struct ListNode *next;
};

/**
 * 
 * @param pHead ListNode类 
 * @return ListNode类
 */
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

int main(void)
{
    struct ListNode node3 = {
        .val = 3,
        .next = NULL,
    };
    struct ListNode node2 = {
        .val = 2,
        .next = &node3,
    };
    struct ListNode node1 = {
        .val = 1,
        .next = &node2,
    };

    struct ListNode *reverse = ReverseList(&node1);
    while (reverse) {
        printf("%d -> ", reverse->val);
        reverse = reverse->next;
    }

    return 0;
}