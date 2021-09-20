while True:
    try:
        l = input().split()
        n = int(l[0])
        strs = l[1:n+1]
        target = l[n+1]
        k = int(l[-1])
        # print(strs)
        # print(target)
        # print(k)

        l = []
        for s in strs:
            if s != target and sorted(s) == sorted(target):
                l.append(s)
        l.sort()
        print(len(l))
        if k - 1 < len(l) and k - 1 >= 0:
            print(l[k-1])

    except EOFError:
        break
