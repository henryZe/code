def stack_operator(s: str) -> int:
    stack = []

    for c in s:
        if c.isdigit():
            stack.append(int(c))
        else:
            a2 = stack.pop()
            a1 = stack.pop()

            if c == "+":
                stack.append(a1 + a2)
            elif c == "-":
                stack.append(a1 - a2)
            elif c == "*":
                stack.append(a1 * a2)
            elif c == "/":
                stack.append(a1 // a2)
    return stack.pop()

# 后缀表达式求值
s = "62/3-42*+"
print(stack_operator(s))
