#!/usr/bin/python3
# -*- coding: utf-8 -*-

if 0:
    guess = eval(input())
    print("猜{}了".format("对" if guess == 99 else "错"))

if 0:
    try:
        num = eval(input("num:"))
        print(num ** 2)
    except NameError:
        print("not a number")
    else:
        print("input correct")
    finally:
        print("program exit")

if 0:
    height, weight = eval(input("height, weight(split by ','):"))
    bmi = weight / pow(height, 2)
    print("BMI: {:.2f}".format(bmi))

    who = ""
    if bmi < 18.5:
        who = "thin"
    elif 18.5 <= bmi < 25:
        who = "normal"
    elif 25 <= bmi < 30:
        who = "fat"
    else:
        who = "too fat"
    print("BMI (international) status: {0}".format(who))

if 0:
    import random

    random.seed(10)
    # float
    print("{}".format(random.random()))
    # range[10, 100)
    print("{}".format(random.randint(10, 100)))
    # range[10, 100), unit: 10
    print("{}".format(random.randrange(10, 100, 10)))
    # sizeof(ret) == bits
    print("{}".format(random.getrandbits(16)))
    # float in range[10, 100)
    print("{}".format(random.uniform(10, 100)))
    # choice item in [1, 10)
    print("{}".format(random.choice(range(1, 10))))

    # reorder list
    s = [1, 2, 3, 4, 5, 6, 7, 9]
    random.shuffle(s)
    print("{}".format(s))

if 0:
    pi = 0
    N = 100
    for k in range(N):
        pi += 1/pow(16, k) * ( \
            4/(8*k + 1) - 2/(8*k + 4) \
            - 1/(8*k + 5) - 1/(8*k + 6))
    print("{}".format(pi))

if 0:
    from random import random
    from time import perf_counter

    Darts = 1000 * 1000 * 1000
    hits = 0
    start = perf_counter()

    for i in range(1, 1 + Darts):
        x, y = random(), random()
        dist = pow(x ** 2 + y ** 2, 0.5)
        if dist <= 1:
            hits += 1
        
    pi = hits / Darts * 4
    print("pi = {}".format(pi))
    print("interval = {}".format(perf_counter() - start))

if 0:
    str = ""
    for i in range(100, 1000):
        a = i % 10
        b = int(i % 100 / 10)
        c = int(i / 100)
        
        sum = a ** 3 + b ** 3 + c ** 3
        if sum == i:
            str += "{},".format(i)

    print(str[:-1])

if 0:
    while True:
        for i in range(3):
            name = input()
            password = input()

            if name == "Kate" and password == "666666":
                print("登录成功！")
                break
        else:
            print("3次用户名或者密码均有误！退出程序。")
            break

if 0:
    sum = 0
    for i in range(2, 100):
        for j in range(2, i):
            if i % j == 0:
                break
        else:
            sum += i
            print("test {}".format(i))

    print("{}".format(sum))
