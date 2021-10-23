from typing import List

# 后缀表达式
class Solution:
    def evalRPN(self, tokens: List[str]) -> int:
        stack = []
        for token in tokens:
            try:
                stack.append(int(token))
            except ValueError:
                num2 = stack.pop()
                num1 = stack.pop()

                if token == "+":
                    stack.append(num1 + num2)
                elif token == "-":
                    stack.append(num1 - num2)
                elif token == "*":
                    stack.append(num1 * num2)
                elif token == "/":
                    stack.append(int(num1 / num2))

        return stack.pop()

if __name__ == "__main__":
    # tokens = ["2","1","+","3","*"]
    # tokens = ["4","13","5","/","+"]
    tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
    print(Solution().evalRPN(tokens))
