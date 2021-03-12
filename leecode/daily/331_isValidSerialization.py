class Solution:
    # def isValidSerialization(self, preorder: str) -> bool:
    #     elements = preorder.split(",")
    #     stack = [1]
    # 
    #     for e in elements:
    #         if not len(stack):
    #             return False
    # 
    #         stack[-1] -= 1
    #         if not stack[-1]:
    #             stack.pop()
    # 
    #         if e.isdigit():
    #             stack.append(2)
    # 
    #     return len(stack) == 0

    def isValidSerialization(self, preorder: str) -> bool:
        count = 1
        elements = preorder.split(",")

        for e in elements:
            if count <= 0:
                return False

            count -= 1
            if e.isdigit():
                count += 2

        return count == 0


s = "9,3,4,#,#,1,#,#,2,#,6,#,#"
print(Solution().isValidSerialization(s))
