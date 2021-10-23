def jump(h: float, n):
    if n == 0:
        return -h
    t = h + h / 2 + jump(h / 2, n - 1)
    return t

def half(h: float, n):
    b = h
    for _ in range(n):
        b /= 2
    return b

while True:
    try:
        h = float(input())
        t = jump(h, 5)
        b = half(h, 5)
        print(t)
        print(b)

    except EOFError:
        break