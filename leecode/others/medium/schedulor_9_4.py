from typing import List
import collections

class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        if 0:
            # dict
            freq = collections.Counter(tasks)

            m = len(freq)
            nextValid = [1] * m
            # dict key:value
            rest = list(freq.values())

            time = 0
            for i in range(len(tasks)):
                # time counter
                time += 1
                minValid = min(nextValid[j] for j in range(m) if rest[j] > 0)
                time = max(minValid, time)

                # pick max rest one
                best = -1
                for j in range(m):
                    if nextValid[j] <= time and rest[j] > 0:
                        if best == -1 or rest[j] > rest[best]:
                            best = j

                nextValid[best] = time + n + 1
                rest[best] -= 1

            return time

        if 1:
            # dict
            freq = collections.Counter(tasks)

            # 最多的执行次数
            maxExec = max(freq.values())
            # 具有最多执行次数的任务数量
            maxCount = sum(1 for v in freq.values() if v == maxExec)

            return max(len(tasks), (maxExec - 1) * (n + 1) + maxCount)

tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"]
n = 2
obj = Solution()
print(obj.leastInterval(tasks, n))
