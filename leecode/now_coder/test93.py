#
# lru design
# @param operators int整型二维数组 the ops
# @param k int整型 the k
# @return int整型一维数组
#
from typing import List

class DLinknode:
    def __init__(self, key:int = 0, val:int = 0):
        self.key = key
        self.val = val
        self.prev = None
        self.next = None

class Solution:
    def __init__(self):
        self.head = DLinknode()
        self.tail = DLinknode()
        self.head.next = self.tail
        self.tail.prev = self.head
        self.size = 0
    
    def get(self, key):
        if key not in self.cache:
            return -1
        
        node = self.cache[key]
        self.moveToHead(node)
        return node.val
    
    def addToHead(self, node: DLinknode):
        node.next = self.head.next
        node.prev = self.head
        self.head.next.prev = node
        self.head.next = node
        return
    
    def removeNode(self, node: DLinknode):
        node.prev.next = node.next
        node.next.prev = node.prev
        return
    
    def removeTail(self):
        node = self.tail.prev
        self.removeNode(node)
        return node
    
    def moveToHead(self, node: DLinknode):
        self.removeNode(node)
        self.addToHead(node)
        return
    
    def lru_set(self, key, val):
        if key not in self.cache:
            node = DLinknode(key, val)
            self.size += 1
            if self.size > self.capacity:
                removed = self.removeTail()
                self.cache.pop(removed.key)
                self.size -= 1
                
            self.addToHead(node)
            self.cache[key] = node
            
        else:
            node = self.cache[key]
            node.val = val
            self.moveToHead(node)
            
        return
    
    def LRU(self , operators , k ) -> List[int]:
        res = []
        self.cache = {}
        self.capacity = k
        
        for op in operators:
            if op[0] == 1:
                self.lru_set(op[1], op[2])
            else:
                res.append(self.get(op[1]))
        
        return res


operators = [[1,1,1],[1,2,2],[1,3,2],[2,1],[1,4,4],[2,2]]
k = 3
print(Solution().LRU(operators, k))
