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

if 1:





