from typing import List

class Solution:
    def minSessions(self, tasks: List[int], sessionTime: int) -> int:
        def rec_mins(tasks: List[int], index: int, cur_time: int, cur_snum: int):
            # print(tasks, index, cur_time, cur_snum)

            if cur_snum >= self.minS:
                return

            if cur_time == sessionTime:
                cur_time = 0
                cur_snum += 1
                index = 0

            if not tasks:
                if cur_time > 0:
                    cur_snum += 1
                self.minS = min(self.minS, cur_snum)
                # print("minS " + str(self.minS))
                return

            if index >= len(tasks):
                rec_mins(tasks, 0, 0, cur_snum + 1)
                return

            if tasks[index] + cur_time <= sessionTime:
                time = tasks[index]
                tasks.pop(index)
                rec_mins(tasks, index, cur_time + time, cur_snum)
                tasks.insert(index, time)

            rec_mins(tasks, index + 1, cur_time, cur_snum)
            return

        self.minS = len(tasks)
        tasks.sort(reverse=True)
        rec_mins(tasks, 0, 0, 0)
        return self.minS

# print(Solution().minSessions([1,2,3], 3))
# print(Solution().minSessions([3,1,3,1,1], 8))
# print(Solution().minSessions([1,2,3,4,5], 15))
# print(Solution().minSessions([2,2,1,3,3,1], 3))
print(Solution().minSessions([5,9,7,4,4,7,7,9], 9))
