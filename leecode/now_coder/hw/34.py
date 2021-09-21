while True:
    try:
        s = input()
        l = list(s)
        l.sort()
        print("".join(l))
    except EOFError:
        break