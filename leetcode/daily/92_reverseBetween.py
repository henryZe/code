class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __str__(self):
        return "{} -> {}".format(self.val, self.next)

class Solution:
    def reverseBetween(self, head: ListNode, left: int, right: int) -> ListNode:
        dummyNode = ListNode(-1)
        dummyNode.next = head
        pre = dummyNode
        for _ in range(left - 1):
            pre = pre.next

        cur = pre.next
        for _ in range(right - left):
            next = cur.next
            cur.next = next.next
            next.next = pre.next
            pre.next = next

        return dummyNode.next

if __name__ == "__main__":
    head = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))
    left = 2
    right = 4
    # head = ListNode(5)
    # left = 1
    # right = 1
    # head = ListNode(3, ListNode(5))
    # left = 1
    # right = 2
    print(Solution().reverseBetween(head, left, right))