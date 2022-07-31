from typing import List

class Solution:
    def maximumGroups(self, grades: List[int]) -> int:
        grades.sort()

        n = len(grades)
        post_sum = [0] * n
        post_sum[-1] = grades[-1]
        for i in range(n - 2, -1, -1):
            post_sum[i] = post_sum[i + 1] + grades[i]
        cur_len = 1
        cur_pos = 0
        res = 1

        while cur_pos + cur_len < n:
            cur_sum = sum(grades[cur_pos:cur_pos + cur_len])
            next_sum = post_sum[cur_pos]
            next_len = len(grades[cur_pos + cur_len:])
            if cur_sum >= next_sum or cur_len >= next_len:
                break
            cur_pos += cur_len
            cur_len += 1
            res += 1

        return res


# grades = [10,6,12,7,3,5]
# grades = [8,8]
# grades = [47,2,16,17,41,4,38,23,47]
grades = [47,2,16,17,41,4,38,23,47]
print(Solution().maximumGroups(grades))
