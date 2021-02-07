#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* merge2Lists(struct ListNode *l1, struct ListNode *l2)
{
    printf("66\n");
    struct ListNode temp = {
        .val = 0,
        .next = NULL,
    };

    struct ListNode *head = &temp;
    struct ListNode *node = &temp;

    while (l1 && l2) {
        // printf("l1 %d l2 %d\n", l1->val, l2->val);
        if (l1->val <= l2->val) {
            node->next = l1;
            l1 = l1->next;
        } else {
            node->next = l2;
            l2 = l2->next;
        }
        node = node->next;
    }

    if (!l1) {
        node->next = l2;
    } else {
        node->next = l1;
    }
    printf("88\n");

    struct ListNode *res = node->next;
    while (res) {
        printf("%d -> ", res->val);
        res = res->next;
    }

    return head->next;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
    if (!lists)
        return NULL;

    if (!lists[0])
        return NULL;

    int interval = 1;
    int i;

    while (interval < listsSize) {
        for (i = 0; i < listsSize - interval; i += interval) {
            lists[i] = merge2Lists(lists[i], lists[i + interval]);
        }
        interval *= 2;
    }

    return lists[0];
}

int main(void)
{
    struct ListNode *res;

    struct ListNode l02 = {
        .val = 5,
        .next = NULL,
    };
    struct ListNode l01 = {
        .val = 4,
        .next = &l02,
    };
    struct ListNode l0 = {
        .val = 1,
        .next = &l01,
    };

    struct ListNode l12 = {
        .val = 4,
        .next = NULL,
    };
    struct ListNode l11 = {
        .val = 3,
        .next = &l12,
    };
    struct ListNode l1 = {
        .val = 1,
        .next = &l11,
    };

    struct ListNode l21 = {
        .val = 6,
        .next = NULL,
    };
    struct ListNode l2 = {
        .val = 2,
        .next = &l21,
    };

    struct ListNode *list[] = {&l0, &l1, &l2};
    res = mergeKLists(list, 3);

    struct ListNode *node = res;
    while (node) {
        printf("%d -> ", node->val);
        node = node->next;
    }

    return 0;
}
