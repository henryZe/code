from typing import List
import random

def binarySearch(l: List[int], x: int) -> int:
    size = len(l)
    index = -1
    left, right = 0, size - 1

    while left != right:
        mid = (left + right) // 2
        if l[mid] > x:
            right = mid - 1
        elif l[mid] < x:
            left = mid + 1
        else:
            index = mid
            break

    return index

data = list(range(10))
print(binarySearch(data, 8))
