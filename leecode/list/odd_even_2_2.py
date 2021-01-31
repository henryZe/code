class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __str__(self):
        return "{} -> {}".format(self.val, self.next)

class Solution:
    def oddEvenList(self, head: ListNode) -> ListNode:
        if not head:
            return head

        evenhead = head.next
        odd, even = head, evenhead

        while even and even.next:
            odd.next = even.next
            odd = odd.next
            even.next = odd.next
            even = even.next

        odd.next = evenhead
        return head
