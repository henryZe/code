
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
        return

    def __str__(self):
        return "{} -> {}".format(self.val, self.next)

class Solution:
    def deleteDuplicates(self, head: ListNode) -> ListNode:
        if not head:
            return head

        dummy = ListNode(0, head)

        cur = dummy
        while cur.next and cur.next.next:
            # print(cur.next.val, cur.next.next.val)
            if cur.next.val == cur.next.next.val:
                same = cur.next.val
                while cur.next and cur.next.val == same:
                    # delete node
                    cur.next = cur.next.next
            else:
                cur = cur.next
            # print(cur.val)

        return dummy.next

# head = ListNode(1, ListNode(2, ListNode(3, ListNode(3, ListNode(4, ListNode(4, ListNode(5)))))))
head = ListNode(1, ListNode(1, ListNode(1, ListNode(2, ListNode(3)))))
print(Solution().deleteDuplicates(head))
