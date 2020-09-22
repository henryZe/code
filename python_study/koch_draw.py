#!/usr/bin/python3
# -*- coding: utf-8 -*-

import turtle

def koch(size, n):
    if n == 0:
        turtle.fd(size)
    else:
        for angle in [0, 60, -120, 60]:
            turtle.left(angle)
            koch(size / 3, n - 1)

def main(level, side):

    turtle.delay(0)
    turtle.speed(10)

    turtle.setup(800, 800)
    turtle.penup()
    turtle.goto(-300, 200)
    turtle.pendown()
    turtle.pensize(2)

    for i in range(side):
        koch(600, level)
        turtle.right(360 / side)

    turtle.hideturtle()
    turtle.done()

main(5, 3)
