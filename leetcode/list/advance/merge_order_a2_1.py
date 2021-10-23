from typing import List

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __str__(self):
        return "{} -> {}".format(self.val, self.next)

class Solution:
    def mergeKLists(self, lists: List[ListNode]) -> ListNode:
        res = []

        if len(lists) == 0:
            return None

        if len(lists) == 1 and lists[0] == None:
            return None

        for node in lists:
            while node:
                res.append(node.val)
                node = node.next

        res.sort()
        head = None
        prev = head
        for i in res:
            node = ListNode(i, None)
            if prev:
                prev.next = node
            else:
                head = node

            prev = node

        return head


ls = [
    ListNode(1, ListNode(4, ListNode(5))),
    ListNode(1, ListNode(3, ListNode(4))),
    ListNode(2, ListNode(6))
]
obj = Solution()
print(obj.mergeKLists(ls))
