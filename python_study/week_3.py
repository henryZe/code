#!/usr/bin/python3
# -*- coding: utf-8 -*-

if 0:
    from random import random
    from math import sqrt
    from time import clock

    def pi_calc(sum):
        hits = 0
        
        for i in range(1, sum):
            x, y = random(), random()
            dist = sqrt(x**2 + y**2)
            if dist <= 1.0:
                hits += 1

        pi = 4 * (hits / sum)
        print("pi value: %s" % pi)

    def main():
        sum = 2 ** 30
        print("range %d" % sum)

        clock()
        pi_calc(sum)
        print("wasted time: %-5.5ss" % clock())

    main()

if 0:
    print("{{{}}}: Computer {} CPU occupancy rate {}%.".format("2017-08-15", "python", 10))
    print("{0:30}".format("python"))
    print("{0:-^30}".format("python"))
    print("{0:=>30}".format("python"))
    print("{0:=^30,}".format(123123.456))
    print("{0:=^30.1f}".format(123123.456))
    print("{0:b},{0:c},{0:d},{0:o},{0:x},{0:X}".format(425))
    print("{0:e},{0:E},{0:f},{0:.2%}".format(1.23456))

if 0:
    factor = 0.001
    val = pow(1 + factor, 365)
    print("up {:f}".format(val))
    val = pow(1 - factor, 365)
    print("down {:f}".format(val))

if 0:
    val = 1
    factor = 0.001
    for n in range(365):
        if n % 7 in [0]:
            val *= (1 - factor)
        else:
            val *= (1 + factor)

    print("weekday {:.2f}".format(val))

if 0:
    def DayUp(df):
        dayup = 1

        for i in range(365):
            if i % 7 in [6, 0]:
                dayup = dayup * (1 - 0.01)
            else:
                dayup = dayup * (1 + df)

        return dayup

    factor = 0.01
    while DayUp(factor) < pow(1 + 0.01, 365):
        factor += 0.001

    print("factor {:f}".format(factor))

if 0:
    buf = "henry"
    print(buf * 5)

    i = input("1 ~ 7:")
    buf = "一二三四五六日"
    print("星期" + buf[eval(i) - 1])

if 0:
    print(chr(9801))
    print(str(ord('♉')))

    for i in range(12):
        print(chr(9800 + i) + ' ', end = '')

if 0:
    print("{}: computer{} cpu usage is {}%".format("2020-09-30", "C", 10))
    print("{1:=^30}".format("2020-09-30", "2020-09-29"))

if 0:
    import time

    scale = 100
    print("执行开始".center(scale // 2, "-"))

    start = time.perf_counter()

    for i in range(scale + 1):
        a = '*' * i
        b = '.' * (scale - i)
        c = (i / scale) * 100

        dur = time.perf_counter() - start
        print("\r{:^3.0f}%[{}{}] {:.2f}s".format(c, a, b, dur), end = "")
        time.sleep(0.1)

    print("\n" + "执行结束".center(scale // 2, "-"))

if 0:
    def DayUp(df):
        dayup = 1

        for i in range(365):
            if i % 7 in [6, 0]:
                dayup = dayup * (1 - 0.01)
            else:
                dayup = dayup * (1 + df)

        return dayup

    factor = 0.01
    val = pow(1 + factor, 365)

    while DayUp(factor) < val:
        factor += 0.001

    print("工作日的努力参数是:", "{:.3f}".format(factor))

if 0:
    value = pow(eval(input()), 3)
    print("{:-^20}".format(value))

if 0:
    value = eval(input())
    for i in range(value + 1):
        if (i % 2) == 0:
            continue

        buf = i * "*"
        print(buf.center(value, " "))

if 1:
    


