from typing import List
import heapq

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __str__(self):
        return "{} -> {}".format(self.val, self.next)

    def __eq__(self, other):
        return self.val == other.val

    def __ne__(self, other):
        return self.val != other.val

    def __gt__(self, other):
        return self.val > other.val

    def __ge__(self, other):
        return self.val >= other.val

    def __lt__(self, other):
        return self.val < other.val

    def __le__(self, other):
        return self.val <= other.val

class Solution:
    def mergeKLists(self, lists: List[ListNode]) -> ListNode:
        head = ListNode()
        cur = head
        heap = []
        for l in lists:
            if l:
                # print(l.val)
                heapq.heappush(heap, l)

        while heap:
            node = heapq.heappop(heap)
            cur.next = node
            cur = cur.next
            next = node.next
            if next:
                heapq.heappush(heap, next)

        return head.next

l1 = ListNode(1, ListNode(4, ListNode(5)))
l2 = ListNode(1, ListNode(3, ListNode(4)))
l3 = ListNode(2, ListNode(6))
lists = [l1, l2, l3]
print(Solution().mergeKLists(lists))
