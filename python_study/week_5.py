#!/usr/bin/python3
# -*- coding: utf-8 -*-

if 0:
    def fact(n, m = 1):
        s = 1
        for i in range(1, n + 1):
            s *= i
        return s // m

    print(fact(10, 2))
    print(fact(m = 2, n = 10))

if 0:
    def fact(n, *b):
        s = 1
        for i in range(1, n + 1):
            s *= i
        for item in b:
            s *= item
        return s

    print(fact(10, 3, 5, 8))
    print(fact(10))

if 0:
    def max_self(a, *b):
        s = a
        for i in b:
            s = s if s > i else i
        return s

    print(max_self(10))
    print(max_self(10, 3, 15, 8))

if 0:
    ls = ["F", "f"]
    def func(a):
        ls.append(a)    # global variable
        return

    func("C")
    print(ls)

if 0:
    ls = ["F", "f"]
    def func(a):
        ls = []         # local variable
        ls.append(a)
        return

    func("C")
    print(ls)

if 0:
    f = lambda x, y: x + y
    print(f(10, 15))

if 0:
    def fact(n = 5):
        if n == 0:
            return 1
        else:
            return n * fact(n - 1)

    print(fact())

if 0:
    def rvs(s):
        if s == "":
            return s
        else:
            return rvs(s[1:]) + s[0]

    s = "123456789"
    print(s[::-1])
    print(rvs(s))

if 0:
    def f(n):
        if n == 1 or n == 2:
            return 1
        else:
            return f(n - 1) + f(n - 2)

    print(f(10))

if 0:
    count = 0
    def hanoi(n, src, dst, mid):
        global count
        if n == 1:
            print("{}:{}->{}".format(1, src, dst))
            count += 1
        else:
            hanoi(n - 1, src, mid, dst)
            print("{}:{}->{}".format(n, src, dst))
            count += 1
            hanoi(n - 1, mid, dst, src)

    hanoi(10, "src", "dst", "mid")
    print("count:{}".format(count))
