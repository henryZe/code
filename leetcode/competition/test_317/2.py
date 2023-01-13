import collections
from typing import List
import heapq

def compare(pre, cur):
    if pre[0] == cur[0]:
        return pre if min(pre[1], cur[1]) == pre[1] else cur
    return pre if max(pre[0], cur[0]) == pre[0] else cur

class Solution:
    def mostPopularCreator(self, creators: List[str], ids: List[str], views: List[int]) -> List[List[str]]:
        c_dict = {}
        c_dict_max = {}
        l = []
        for i, creator in enumerate(creators):
            if creator not in c_dict:
                c_dict[creator] = views[i]
                c_dict_max[creator] = (views[i], ids[i])
                heapq.heappush(l, [-c_dict[creator], creator])
            else:
                c_dict[creator] += views[i]
                c_dict_max[creator] = compare(c_dict_max[creator], (views[i], ids[i]))
                heapq.heappush(l, [-c_dict[creator], creator])

        c = heapq.heappop(l)
        res = [[c[1], c_dict_max[c[1]][1]]]

        while l:
            next = heapq.heappop(l)
            if next[0] != c[0]:
                break
            res.append([next[1], c_dict_max[next[1]][1]])

        return res

# creators = ["alice","bob","alice","chris"]
# ids = ["one","two","three","four"]
# views = [5,10,5,4]
creators = ["alice","alice","alice"]
ids = ["a","b","c"]
views = [1,2,2]
# creators = ["a"]
# ids = ["a"]
# views = [0]
# creators = ["a","b"]
# ids = ["a","b"]
# views = [0,0]
print(Solution().mostPopularCreator(creators, ids, views))
