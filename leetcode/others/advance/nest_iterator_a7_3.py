class NestedInteger:
    def __init__(self, value=None):
        if not value:
            self.value = []

        self.value = value
        return

    def isInteger(self) -> bool:
        return isinstance(self.value, int)

    def getInteger(self) -> int:
        assert isinstance(self.value, int)
        return self.value

    def getList(self):
        assert isinstance(self.value, list)
        return self.value

class NestedIterator:
    def __init__(self, nestedList: NestedInteger):
        self.stack = nestedList[::-1]
        return

    def next(self) -> int:
        return self.stack.pop().getInteger()
    
    def hasNext(self) -> bool:
        while len(self.stack) > 0 and self.stack[-1].isInteger() is False:
            self.stack += self.stack.pop().getList()[::-1]
        return len(self.stack) > 0


def test(nestedList):
    i = NestedIterator(nestedList)
    v = []
    while i.hasNext():
        v.append(i.next())

    print(v)
    return

nestedList1 = [NestedInteger([NestedInteger(1),NestedInteger(1)]),NestedInteger(2),NestedInteger([NestedInteger(1),NestedInteger(1)])]
nestedList2 = [NestedInteger(1), NestedInteger([NestedInteger(4), NestedInteger([NestedInteger(6)])])]
test(nestedList1)
test(nestedList2)
