import sys
import collections 

if __name__ == "__main__":
    n = int(sys.stdin.readline().strip())

    line = sys.stdin.readline().strip()
    ids = list(map(int, line.split(',')))

    line = sys.stdin.readline().strip()
    scores = list(map(int, line.split(',')))

    s_dict = collections.defaultdict(list)
    size = len(ids)
    for i in range(size):
        s_dict[ids[i]].append(scores[i])

    sum_score = {}
    for key in s_dict.keys():
        s_dict[key].sort(reverse=True)
        sum_score[key] = 0
        for i in range(3):
            sum_score[key] += s_dict[key][i]

    id_set = set(ids)
    id_set_list = list(id_set)
    id_set_list.sort()

    l = []
    while len(id_set_list):
        max_sum = 0

        for id_num in id_set_list:
            if sum_score[id_num] >= max_sum:
                max_sum = sum_score[id_num]
                max_id = id_num

        l.append(max_id)
        id_set_list.remove(max_id)

    print(l)
