from typing import List

class Solution:
    def minSessions(self, tasks: List[int], sessionTime: int) -> int:
        n = len(tasks)
        dic = [0] * (1 << n)

        for i in range(1 << n):
            for j in range(n):
                if i & (1 << j):
                    dic[i] += tasks[j]

        f = [n] * (1 << n)
        for i in range(1 << n):
            if dic[i] <= sessionTime:
                f[i] = 1
                continue
            
            j = i
            while j:
                f[i] = min(f[i], f[j] + f[i ^ j])
                # j is the sub-set of i
                j = (j - 1) & i

        return f[-1]

print(Solution().minSessions([2, 1, 2, 1, 2, 1], 3))