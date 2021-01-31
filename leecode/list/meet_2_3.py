

class ListNode:
    def __init__(self, val, next=None):
        self.val = val
        self.next = next

    def __str__(self):
        return "{} -> {}".format(self.val, self.next)

class Solution:
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        p1, p2 = headA, headB
        around, bround = False, False

        if p1 == None or p2 == None:
            return

        while p1 != p2:
            if p1.next == None and around == False:
                p1 = headB
                around = True
            else:
                p1 = p1.next

            if p2.next == None and bround == False:
                p2 = headA
                bround = True
            else:
                p2 = p2.next

        return p1

obj = Solution()
# sector = ListNode(8, ListNode(4, ListNode(5)))
# l1 = ListNode(4, ListNode(1, sector))
# l2 = ListNode(5, ListNode(6, ListNode(1, sector)))
l1 = ListNode(2, ListNode(6, ListNode(4)))
l2 = ListNode(1, ListNode(5))

print(l1)
print(l2)
print(obj.getIntersectionNode(l1, l2))
