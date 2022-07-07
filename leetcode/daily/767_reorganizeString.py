import heapq

class Solution:
    def reorganizeString(self, s: str) -> str:
        d = {}
        for c in s:
            if c in d:
                d[c] += 1
            else:
                d[c] = 1

        hq = []
        for key in d.keys():
            heapq.heappush(hq, [-d[key], key])

        length = len(s)
        l = [None] * length

        i = 0
        last = None
        while i < length:
            if not hq:
                break
            content = heapq.heappop(hq)
            if last and last[0]:
                heapq.heappush(hq, last)

            print(content)

            times = -content[0]
            l[i] = content[1]
            i += 1
            times -= 1
            last = [-times, content[1]]

        if hq or i < length:
            return ""

        return "".join(l)

# s = "aab"
# s = "aaab"
s = "aabbcc"
print(Solution().reorganizeString(s))
