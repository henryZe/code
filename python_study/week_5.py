#!/usr/bin/python3
# -*- coding: utf-8 -*-

if 0:
    def fact(n, m = 1):
        s = 1
        for i in range(1, n + 1):
            s *= i
        return s // m

    print(fact(10, 2))
    
if 1:
    def fact(n, *b):
        s = 1
        for i in range(1, n + 1):
            s *= i
        for item in b:
            s *= item
        return s

    print(fact(10, 3, 5, 8))
    print(fact(10))

    def max_self(a, *b):
        s = a
        for i in b:
            s = s if s > i else i
        return s



