import heapq

def func():
    req_num, cache_size = map(int, input().split())
    request = list(map(int, input().split()))

    dist = {}
    last_dist = [req_num] * req_num

    for i in range(req_num - 1, -1, -1):
        if request[i] not in dist:
            dist[request[i]] = i
            last_dist[i] = req_num

        else:
            last_dist[i] = dist[request[i]]
            dist[request[i]] = i

    cache_st = [False] * (req_num + 1)
    cache = []
    miss_count = 0
    cache_cnt = 0
    for i in range(req_num):
        if not cache_st[i]:
            # print("missed", i, request[i])
            miss_count += 1

            if cache_cnt < cache_size:
                heapq.heappush(cache, -last_dist[i])
                cache_st[last_dist[i]] = True
                cache_cnt += 1
            else:
                pop_dist = -heapq.heappop(cache)
                # if pop_dist == req_num:
                #     print("pop no longer")
                # else:
                #     print("pop", request[pop_dist])
                cache_st[pop_dist] = False
                heapq.heappush(cache, -last_dist[i])
                cache_st[last_dist[i]] = True
        else:
            # print("cached", i, request[i])

            heapq.heappush(cache, -last_dist[i])
            cache_st[last_dist[i]] = True

    print(miss_count)
    return


if __name__ == "__main__":
    func()