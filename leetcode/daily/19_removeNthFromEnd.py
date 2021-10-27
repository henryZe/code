
# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def removeNthFromEnd(self, head: ListNode, n: int) -> ListNode:
        new = ListNode(0, head)
        slow = new
        fast = head
        for i in range(n):
            fast = fast.next

        while fast:
            slow = slow.next
            fast = fast.next
        
        slow.next = slow.next.next
        return new.next


listHead = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))
n = 2
Solution().removeNthFromEnd(listHead, n)
temp = listHead
while temp:
    print(temp.val)
    temp = temp.next
