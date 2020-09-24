#!/usr/bin/python3
# -*- coding: utf-8 -*-

if 0:
    # set feature:
    # A. unique
    # B. un-sort
    # C. constant
    A = {"python", 123, ("python", 123)}
    print(A)
    B = set("pypy123")
    print(B)

    # '-', '&', '|', '^'
    A = {"p", "y", 123}
    B = set("pypy123")
    print(A - B)
    print(B - A)
    print(A & B)
    print(A | B)
    print(A ^ B)

if 0:
    A = {"p", "y", 123}

    # add discard remove clear pop
    # copy len set in not in
    for i in A:
        print(i)

    try:
        while True:
            print(A.pop())
    except:
        pass

if 0:
    # discard redundant data
    ls = ["p", "y", "p", "y", 123]
    temp = set(ls)
    ls = list(temp)
    print(ls)

if 0:
    # array
    # in not in + * [index] [i:j:k]
    ls = ["python", 123, ".io"]
    print(ls[::-1])
    print(len(ls))
    print(ls.count(123))

    str = "python123.io"
    print(min(str))
    print(max(str))
    print(str.index("1"))
    print(str.count("o"))

if 1:

