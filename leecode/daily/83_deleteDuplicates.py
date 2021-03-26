class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def deleteDuplicates(self, head: ListNode) -> ListNode:
        if not head:
            return head
        
        node = head
        while node.next:
            next = node.next
            if next.val == node.val:
                node.next = next.next
            else:
                node = next

        return head
