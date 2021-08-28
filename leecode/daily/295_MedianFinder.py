from sortedcontainers import SortedList

class MedianFinder:

    def __init__(self):
        """
        initialize your data structure here.
        """
        self.sortList = SortedList()
        self.left = self.right = None
        self.left_value = self.right_value = 0

    def addNum(self, num: int) -> None:
        size = len(self.sortList)
        self.sortList.add(num)

        if size == 0:
            self.left = self.right = 0
        else:
            if num < self.left_value:
                self.left += 1
            if num < self.right_value:
                self.right += 1

            if size & 1:
                if num < self.left_value:
                    self.left -= 1
                else:
                    self.right += 1
            else:
                if self.left_value < num < self.right_value:
                    self.left += 1
                    self.right -= 1
                elif num >= self.right_value:
                    self.left += 1
                else:
                    self.right -= 1
                    self.left = self.right

        self.left_value = self.sortList[self.left]
        self.right_value = self.sortList[self.right]

    def findMedian(self) -> float:
        return (self.left_value + self.right_value) / 2

# Your MedianFinder object will be instantiated and called as such:
# obj = MedianFinder()
# obj.addNum(num)
# param_2 = obj.findMedian()

obj = MedianFinder()
obj.addNum(1)
print(obj.findMedian())