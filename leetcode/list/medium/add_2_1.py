class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __str__(self):
        return "{} -> {}".format(self.val, self.next)

class Solution:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        def val(l1: ListNode) -> int:
            if not l1:
                val1 = 0
            else:
                val1 = l1.val
            return val1

        def calc(l1: ListNode, l2: ListNode) -> int:
            num = 0
            order = 0
            while l1 or l2:
                num += (val(l1) + val(l2)) * (10**order)
                if l1:
                    l1 = l1.next
                if l2:
                    l2 = l2.next
                order += 1
            return num

        def mk_list(num: int) -> ListNode:
            if num == 0:
                return None

            val = num % 10
            num //= 10
            return ListNode(val, mk_list(num))

        num = calc(l1, l2)
        if num == 0:
            return ListNode(0)

        return mk_list(num)


obj = Solution()
l1 = ListNode(2, ListNode(4, ListNode(3)))
l2 = ListNode(5, ListNode(6, ListNode(4)))

print(obj.addTwoNumbers(l1, l2))
