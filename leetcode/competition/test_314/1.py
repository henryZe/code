from typing import List

class Solution:
    def hardestWorker(self, n: int, logs: List[List[int]]) -> int:
        start_time = 0
        max_period = 0
        res = 0
        for log in logs:
            end_time = log[1]
            period = end_time - start_time
            if period > max_period:
                max_period = period
                res = log[0]
            elif period == max_period:
                res = min(log[0], res)

            start_time = end_time

        return res

n = 10
logs = [[0,3],[2,5],[0,9],[1,15]]
n = 26
logs = [[1,1],[3,7],[2,12],[7,17]]
n = 2
logs = [[0,10],[1,20]]
print(Solution().hardestWorker(n, logs))