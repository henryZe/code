from typing import List

class Solution:
    def smallestEvenMultiple(self, n: int) -> int:
        if n % 2:
            return n * 2
        else:
            return n

