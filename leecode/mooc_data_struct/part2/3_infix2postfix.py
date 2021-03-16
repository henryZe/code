def infix2postfix(s: str) -> str:
    postfix = []
    stack = []
    operator = {}
    operator["+"] = operator["-"] = 0
    operator["*"] = operator["/"] = 1

    for c in s:
        if c.isdigit():
            postfix.append(c)

        else:
            if c in operator:
                while stack and stack[-1] in operator and operator[stack[-1]] >= operator[c]:
                    postfix.append(stack.pop())
                stack.append(c)

            elif c == "(":
                stack.append(c)

            elif c == ")":
                while stack[-1] != "(":
                    postfix.append(stack.pop())
                stack.pop()

    while stack:
        postfix.append(stack.pop())

    return "".join(postfix)

s = "2*(6/3+4*(1 + 1))-5"
print(s)
print(infix2postfix(s))
