class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __str__(self):
        return "{} -> {}".format(self.val, self.next)

class Solution:
    def rotateRight(self, head: ListNode, k: int) -> ListNode:
        if not head or not k or not head.next:
            return head

        cur = head
        n = 1

        while cur.next:
            n += 1
            cur = cur.next

        cur.next = head
        rotate = n - k % n

        for _ in range(rotate):
            cur = head
            head = head.next
        cur.next = None

        return head

head = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))
k = 2
print(Solution().rotateRight(head, k))
