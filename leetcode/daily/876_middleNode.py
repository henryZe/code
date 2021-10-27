
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def middleNode(self, head: ListNode) -> ListNode:
        slow = head
        fast = head.next

        while fast != None:
            slow = slow.next
            if fast.next:
                fast = fast.next.next
            else:
                break

        return slow


listHead = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))
print(Solution().middleNode(listHead).val)
