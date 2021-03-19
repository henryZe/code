class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __str__(self):
        return "{} -> {}".format(self.val, self.next)

class Solution:
    def reverseBetween(self, head: ListNode, left: int, right: int) -> ListNode:
        cur = head
        prev = None
        headInsert = head
        headOrigin = None
        i = 1

        while cur:
            next = cur.next

            
            if left <= i <= right:
                cur.next = prev
                

            prev = cur
            cur = next
            i += 1

        headInsert.next = cur
        if headOrigin:
            headOrigin.next = prev

        return head

if __name__ == "__main__":
    # head = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))
    # left = 2
    # right = 4
    # head = ListNode(5)
    # left = 1
    # right = 1
    head = ListNode(3, ListNode(5))
    left = 1
    right = 2
    print(Solution().reverseBetween(head, left, right))