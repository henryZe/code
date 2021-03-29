#!/usr/bin/python3
# -*- coding: utf-8 -*-

if 0:
	val = input("please input temp value (like 32C): ")
	if val[-1] in ['C', 'c']:
		f = 1.8 * eval(val[0 : -1]) + 32
		print("The convert temp is %.2fF" %f)
	elif val[-1] in ['F', 'f']:
		c = (eval(val[0: -1]) - 32) / 1.8
		print("The convert temp is %.2fC" %c)
	else:
		print("Invalid parameter.")

if 0:
    import turtle

    turtle.setup(650, 350)
    turtle.penup()
    turtle.fd(-250)
    turtle.pendown()
    turtle.pensize(25)
    turtle.pencolor("red")
    turtle.seth(-40)
    for i in range(4):
        turtle.circle(40, 80)
        turtle.circle(-40, 80)
    turtle.circle(40, 80/2)
    turtle.fd(40)
    turtle.circle(16, 180)
    turtle.fd(40 * 2 / 3)
    turtle.done()

if 0:
    import turtle

    turtle.goto(100, 100)
    turtle.goto(100, -100)
    turtle.goto(-100, -100)
    turtle.goto(-100, 100)
    turtle.goto(0, 0)
    turtle.fd(100)
    turtle.circle(50, 180)
    turtle.circle(-50, 180)
    turtle.bk(100)
    turtle.done()

if 0:
    import turtle as t

    t.goto(100, 100)
    t.goto(100, -100)
    t.goto(-100, -100)
    t.goto(-100, 100)
    t.goto(0, 0)
    t.fd(100)
    t.circle(50, 180)
    t.circle(-50, 180)
    t.bk(100)
    t.done()

if 0:
    import turtle

    turtle.pensize(5)
    turtle.goto(0, 100)
    turtle.goto(100, 100)
    turtle.goto(100, 0)
    turtle.goto(0, 0)
    turtle.done()

if 0:
    import turtle as t

    for i in range(6):
        t.right(60)
        t.fd(100)

    t.done()

if 0:
    import turtle as t

    for i in range(9):
        t.fd(150)
        t.right(80)

    t.done()

if 0:
    import turtle as t

    t.pensize(5)

    for i in range(8):
        t.left(90)
        t.fd(150)
        t.penup()
        t.bk(150)
        t.right(90)
        if (i % 2 == 0):
            t.pendown()
            t.circle(150, -45)
        else:
            t.circle(150, -45)
            t.pendown()

    t.done()

if 0:
    import turtle

    color = ["pink", "green", "yellow", "orange", "blue"]

    def draw_snake(rad, angle, len, neckrad):
        for i in range(len):
            turtle.pencolor(color[i])
            turtle.circle(rad, angle)
            turtle.circle(-rad, angle)

        turtle.circle(rad, angle/2)
        turtle.fd(rad)
        turtle.circle(neckrad + 1, 180)
        turtle.fd(rad * 2 / 3)

    def main():
        # point x y & top left location
        turtle.setup(1300, 200, 0, 0)
        pythonsize = 20
        turtle.pensize(pythonsize)
        turtle.seth(-40)
        draw_snake(30, 80, 5, pythonsize/2)

    main()

if 0:
    import turtle

    def triangle(len):
        turtle.fd(len)
        turtle.seth(120)
        turtle.fd(len)
        turtle.seth(-120)
        turtle.fd(len)

    def main():
        turtle.pensize = 20
        turtle.pencolor("red")
        len = 200
        triangle(len)

    main()
