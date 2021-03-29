#!/usr/bin/python3
# -*- coding: utf-8 -*-

if 0:
    r = 25
    area = 3.1415 * r * r
    print(area)
    print("{:.2f}".format(area))

if 0:
    import turtle
    turtle.pensize(2)
    turtle.circle(10)
    turtle.circle(40)
    turtle.circle(80)
    turtle.circle(160)

if 0:
    from turtle import *
    color('red', 'red')
    begin_fill()
    for i in range(5):
        fd(200)
        rt(144)
    end_fill()
    done()

if 0:
    TempStr = input("Please input temperature value:")
    if TempStr[-1] in ['F', 'f']:
        C = (eval(TempStr[0:-1]) - 32) / 1.8
        print("Translate: {:.2f}C".format(C))
    elif TempStr[-1] in ['C', 'c']:
        F = 1.8 * eval(TempStr[0:-1]) + 32
        print("Translate: {:.2f}F".format(F))
    else:
        print("Error")

if 0:
    value = input()
    Str = "零一二三四五六七八九"
    string = ""
    for i in range(len(value)):
        string += Str[eval(value[i])]
    print(string)

if 0:
    value = input()
    Str = "Hello World"
    if eval(value) == 0:
        print(Str)
    elif eval(value) > 0:
        for n in range(0, len(Str), 2):
            print(Str[n : n+2])
    else:
        for n in range(len(Str)):
            print(Str[n])

if 0:
    value = input()
    print("{:.2f}".format(eval(value)))

if 0:
    str1 = input("please input a name: ")
    str2 = input("please input a country name: ")
    print("The world is wide, {} wanna see {}.".format(str1, str2))

if 0:
    val = input("please input temp value (like 32C): ")
    if val[-1] in ['C', 'c']:
        f = 1.8 * float(val[0 : -1]) + 32
        print("The convert temp is %.2fF" %f)
    elif val[-1] in ['F', 'f']:
        c = (float(val[0: -1]) - 32) / 1.8
        print("The convert temp is %.2fC" %c)
    else:
        print("Invalid parameter.")

if 0:
    n = input("please input a number N: ")
    sum = 0
    for i in range(int(n)):
        sum += i + 1
    print("Sum of 1 to N is", sum)

if 0:
    for i in range(1, 10):
        for j in range(1, 10):
            print("{} * {} = {}\t".format(j, i, i * j), end='')
        print(' ')

if 0:
    sum, tmp = 0, 1
    for i in range(1, 11):
        tmp *= i
        sum += tmp
    print("result is {}".format(sum))

if 0:
    n = 1
    for i in range(5, 0, -1):
        n = (n + 1) << 1
    print("how many peach? %d" % n)

if 0:
    diet = ['tomato', 'cauliflower', 'cucumber', 'beef', 'shrimp']
    for x in range(0, 5):
        for y in range(0, 5):
            if not(x == y):
                print("{}-{}".format(diet[x], diet[y]))

if 0:
    from turtle import *

    fillcolor("orange")
    begin_fill()
    while True:
        forward(300)
        right(144)
        if abs(pos()) < 1:
            break
    end_fill()

if 0:
    from turtle import *

    color('blue', 'pink')
    begin_fill()
    while True:
        forward(200)
        left(179)
        if abs(pos()) < 1:
            break
    end_fill()
    done()

if 0:
    import turtle, time

    turtle.speed("fastest")
    turtle.bgcolor("green")
    turtle.pensize(2)
    for x in range(100):
        turtle.forward(2 * x)
        turtle.color("pink")
        turtle.left(90)
    time.sleep(3)

if 0:
    import turtle, time

    turtle.pensize(2)
    turtle.bgcolor("pink")
    colors = ['red', 'yellow', 'purple', 'blue']
    turtle.tracer(False)
    for x in range(400):
        turtle.forward(2 * x)
        turtle.color(colors[x % 4])
        turtle.left(91)
    turtle.tracer(True)
