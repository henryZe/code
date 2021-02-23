import collections

class LRUCache(collections.OrderedDict):

    def __init__(self, capacity: int):
        self.capacity = capacity
        return

    def get(self, key: int) -> int:
        if key not in self:
            return -1

        self.move_to_end(key)
        return self[key]

    def put(self, key: int, value: int) -> None:
        if key in self:
            self.move_to_end(key)

        self[key] = value

        if len(self) > self.capacity:
            self.popitem(last=False)

        return


opts = ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
data = [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]

obj = LRUCache(2)
obj.put(1, 1)
obj.put(2, 2)
print(obj.get(1))
obj.put(3, 3)
print(obj.get(2))
obj.put(4, 4)
print(obj.get(1))
print(obj.get(3))
print(obj.get(4))
