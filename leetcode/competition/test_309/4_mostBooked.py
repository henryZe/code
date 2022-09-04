from typing import List
import heapq

class Solution:
    def mostBooked(self, n: int, meetings: List[List[int]]) -> int:
        meetings.sort()
        room = [-1] * n
        times = [0] * n
        q = []
        for s, e in meetings:
            while q and q[0][0] <= s:
                t, r = heapq.heappop(q)
                room[r] = -1

            for r in range(n):
                if room[r] == -1:
                    room[r] = e
                    times[r] += 1
                    heapq.heappush(q, [e, r])
                    # print("occupy", r, times[r])
                    break
            else:
                # rooms are busy
                t, r = heapq.heappop(q)
                room[r] = e - s + t
                times[r] += 1
                heapq.heappush(q, [room[r], r])
                # print("wait", r, times[r])
            # print("next")

        cur = 0
        res = -1
        for i, t in enumerate(times):
            if t > cur:
                cur = t
                res = i
        return res

# n = 2
# meetings = [[0,10],[1,5],[2,7],[3,4]]
# n = 3
# meetings = [[1,20],[2,10],[3,5],[4,9],[6,8]]
# n = 2
# meetings = [[0,10],[1,5],[2,7],[3,4],[8,11],[9,12]]
# n = 2
# meetings = [[0,10],[1,2],[12,14],[13,15]]
n = 4
meetings = [[18,19],[3,12],[17,19],[2,13],[7,10]]
print(Solution().mostBooked(n, meetings))
