while True:
    try:
        s1 = input().split()[1:]
        s2 = list(set(map(int, input().split()[1:])))
        s2.sort()

        rst = []
        for num in s2:
            tmp = []
            for i, sub in enumerate(s1):
                if str(num) in sub:
                    tmp.extend([str(i), sub])
                    # print("tmp", tmp)
            if tmp:
                rst.extend([str(num), str(len(tmp) // 2)] + tmp)
                # print("rst", rst)
        print(str(len(rst)) + " " + " ".join(rst))

    except EOFError:
        break