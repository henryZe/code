class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

    def __str__(self):
        return "{} -> {}".format(self.val, self.next)

class Solution:
    def mergeTwoLists(self , l1 , l2 ):
        if not l1 or not l2:
            if l1:
                return l1
            else:
                return l2
        
        
        res = ListNode(0)
        head = res
        while l1 and l2:
            if l1.val < l2.val:
                res.next = l1
                l1 = l1.next
            else:
                res.next = l2
                l2 = l2.next
            res = res.next

        if not l1:
            res.next = l2
        else:
            res.next = l1

        return head.next


l1 = ListNode(1)
l2 = ListNode(2)
l = Solution().mergeTwoLists(l2, l1)
print(l)
