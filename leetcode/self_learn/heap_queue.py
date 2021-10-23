import heapq
import random

def test():
    data = list(range(10))
    random.shuffle(data)
    print(data)

    heap = []
    for d in data:
        heapq.heappush(heap, d)
    print(heap)

    data = []
    while heap:
        data.append(heapq.heappop(heap))
    print(data)

test()
