from typing import List

class NumArray:
    def __init__(self, nums: List[int]):
        self.array = []
        for num in nums:
            self.array.append(num)
        return

    def sumRange(self, i: int, j: int) -> int:
        return sum(self.array[i:j+1])


# operations = ["NumArray", "sumRange", "sumRange", "sumRange"]
# args = [[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]

operations = ["NumArray","sumRange"]
args = [[[-1]],[0,0]]

res = []
for i in range(len(operations)):
    if operations[i] == "NumArray":
        obj = NumArray(args[i][0])
        res.append(None)
    elif operations[i] == "sumRange":
        x, y = args[i]
        res.append(obj.sumRange(x, y))

print(res)
