#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* oddEvenList(struct ListNode* head)
{
    if (!head)
        return NULL;

    struct ListNode odd_h, even_h;
    // initialize !!!
    odd_h.next = even_h.next = NULL;

    struct ListNode *odd = &odd_h, *even = &even_h;

    bool is_odd = true;
    while (head) {
        if (is_odd) {
            odd->next = head;
            odd = odd->next;
        } else {
            even->next = head;
            even = even->next;
        }
        head = head->next;
        is_odd = !is_odd;
    }

    odd->next = even_h.next;
    even->next = NULL;

    return odd_h.next;
}

int main(void)
{
    // struct ListNode n6 = {6, NULL};
    // struct ListNode n5 = {5, &n6};
    // struct ListNode n4 = {4, &n5};
    // struct ListNode n3 = {3, &n4};
    // struct ListNode n2 = {2, &n3};
    // struct ListNode n1 = {1, &n2};

    struct ListNode n1 = {1, NULL};

    struct ListNode *ret = oddEvenList(&n1);
    while (ret) {
        printf("%d,", ret->val);
        ret = ret->next;
    }

    return 0;
}