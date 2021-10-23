class Solution:
    # def checkOnesSegment(self, s: str) -> bool:
    #     def lowbit(num: int):
    #         return num & (-num)
    #
    #     num = int(s, 2)
    #     res = True
    #     while num:
    #         prev = lowbit(num)
    #         num -= prev
    #         if num:
    #             if (prev << 1) != lowbit(num):
    #                 res = False
    #                 break
    #
    #     return res

    def checkOnesSegment(self, s: str) -> bool:
        return "01" not in s

res = Solution().checkOnesSegment("1001")
# res = Solution().checkOnesSegment("110")
print(res)
