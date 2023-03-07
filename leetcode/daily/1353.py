from typing import List
import heapq

class Solution:
    def maxEvents(self, events: List[List[int]]) -> int:
        n = len(events)

        start = {}
        for event in events:
            if event[0] not in start:
                start[event[0]] = [event]
            else:
                start[event[0]].append(event)

        res = 0
        day = 1
        consume = 0

        q = []
        while q or consume < n:
            if day in start:
                for event in start[day]:
                    heapq.heappush(q, [event[1], event[0]])
                    consume += 1

            if not q:
                day += 1
                continue

            event = heapq.heappop(q)
            while event[0] < day and q:
                event = heapq.heappop(q)

            if event[1] <= day and day <= event[0]:
                # print(day, event)
                res += 1

            day += 1

        return res

obj = Solution()
# events = [[1,2],[1,2],[1,6],[1,2],[1,2]]
# events = [[1,4],[4,4],[2,2],[3,4],[1,1]]
# events = [[1,5],[1,5],[1,5],[2,3],[2,3]]
# events = [[52,79],[7,34]]
events = [[27,27],[8,10],[9,11],[20,21],[25,29],[17,20],[12,12],[12,12],[10,14],[7,7],[6,10],[7,7],[4,8],[30,31],[23,25],[4,6],[17,17],[13,14],[6,9],[13,14]]
print(obj.maxEvents(events))
