class Solution:
    def partitionString(self, s: str) -> int:
        cur_set = set()
        count = 1
        for c in s:
            if c in cur_set:
                count += 1
                cur_set = set()
                cur_set.add(c)
            else:
                cur_set.add(c)
            
        return count

s = "abacaba"
# s = "ssssss"
print(Solution().partitionString(s))
