class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __str__(self):
        return "{} -> {}".format(self.val, self.next)

class Solution:
    def sortList(self, head: ListNode) -> ListNode:
        def merge(l1: ListNode, l2: ListNode) -> ListNode:
            if l1 == None or l2 == None:
                return l1 if l2 == None else l2

            head = ListNode()
            node = head

            while l1 and l2:
                if l1.val <= l2.val:
                    node.next = l1
                    l1 = l1.next
                else:
                    node.next = l2
                    l2 = l2.next

                node = node.next

            if l1 == None:
                node.next = l2
            else:
                node.next = l1

            return head.next

        def sortListHT(head: ListNode, tail: ListNode) -> ListNode:
            if head == None:
                return head
            
            if head.next == tail:
                head.next = None
                return head

            fast = head
            slow = head

            while fast != tail:
                fast = fast.next
                slow = slow.next
                if fast != tail:
                    fast = fast.next
                else:
                    break
            mid = slow

            return merge(sortListHT(head, mid), sortListHT(mid, tail))

        return sortListHT(head, None)


obj = Solution()
l = ListNode(4, ListNode(2, ListNode(1, ListNode(3))))
print(obj.sortList(l))
