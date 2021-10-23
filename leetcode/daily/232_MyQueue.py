class MyQueue:
    def __init__(self):
        self.input = []
        self.output = []
        return

    def push(self, x: int) -> None:
        self.input.append(x)
        return

    def pop(self) -> int:
        if not self.output:
            while self.input:
                self.output.append(self.input.pop())
        return self.output.pop()

    def peek(self) -> int:
        if not self.output:
            while self.input:
                self.output.append(self.input.pop())
        return self.output[-1]

    def empty(self) -> bool:
        if not self.input and not self.output:
            return True
        return False

obj = MyQueue()
obj.push(1)
obj.push(2)

print(obj.peek())
print(obj.pop())
print(obj.empty())
