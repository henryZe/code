

class Solution():
    def __init__(self, first: int):
        self.first = first

    def isBadVersion(self, n):
        if n >= self.first:
            return True
        return False

    def firstBadVersion(self, n):
        l = 1
        r = n
        while l < r:
            mid = (l + r) // 2
            if self.isBadVersion(mid) == True:
                r = mid
            else:
                l = mid + 1
        return l

n = 5
s = Solution(4)
print(s.firstBadVersion(n))
