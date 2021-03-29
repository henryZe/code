#!/usr/bin/python3
# -*- coding: utf-8 -*-

import math
from functools import reduce

print(abs(-20))
print(max(-20, 5, 515, 0, 0.12))

a = abs
print(a(-52.12))

n1 = 255
n2 = 1000
print(hex(n1), hex(n2))

def my_max(x, y):
	if not isinstance(x, (int, float)) or not isinstance(y, (int, float)):
		raise TypeError('bad operand type')

	if x > y:
		return x
	else:
		return y

print(my_max(n1, n2))		

def nop():
	pass

def move(x, y, step, angle = 0):
	nx = x + step * math.cos(angle)
	ny = y - step * math.sin(angle)
	return nx, ny

x, y = move(100, 200, 300, math.pi/6)
print(x, y)
r = move(100, 200, 300, math.pi/6)
print(r)


def quadratic(a, b, c):
	return (-b + math.sqrt(b*b-4*a*c))/(2*a), (-b - math.sqrt(b*b-4*a*c))/(2*a)

print(quadratic(2, 3, 1))
print(quadratic(1, 3, -4))


def power(x, n = 2):
	s = 1
	while n > 0:
		s *= x
		n -= 1

	return s

print(power(5))
print(power(5, 2))

def add_end(L=None):
	if L is None:
		L = []

	L.append('END')
	return L

print(add_end())
print(add_end())

def calc(*numbers):
	sum = 0
	for n in numbers:
		sum += n * n

	return sum		

print(calc(1, 2, 3, 4))

num = (1, 2, 3, 4, 5)
print(calc(*num))

def person(name, age, **kw):
	print('name:', name, 'age:', age, 'other:', kw)
	return

person('henry', 8)
person('henry', 8, city = 'tianjing')

extra = {'city': 'guangzhou', 'job': 'Engineer'}
person('jack', 23, **extra)


def fact(n):
	if n == 1:
		return 1
	return n * fact(n-1)

print(fact(10))


def move(n, a, b, c):
	if n == 1:
		print(a, '-->', c)
	else:
		move(n - 1, a, c, b)
		print(a, '-->', c)
		move(n - 1, b, a, c)
	return 

move(10, 'a', 'b', 'c')


def add(x, y, f):
	return f(x) + f(y)

print(add(-4, 1, abs))

def f(x):
	return x * x

print(list(map(f, [0, 1, 2, 3, 4])))


def add_simple(x, y):
	return x + y

print(reduce(add_simple, [1, 2, 3, 4]))

def str2int(s):
	def fn(x, y):
		return x * 10 + y

	def char2num(s):
		# value = dict[key]
		return {'0':0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}[s]

	return reduce(fn, map(char2num, s))

print(str2int('1234567890'))


def normalize(s):
	return s.capitalize()

L1 = ['adam', 'LISA', 'barT']
L2 = list(map(normalize, L1))
print(L2)


def prod(l):
	def mul(x, y):
		return x * y

	return reduce(mul, l)

print('3 * 5 * 7 * 9 =', prod([3, 5, 7, 9]))


def str2float(s):
	def char2num(s):
		return {'0':0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}[s]

	def f(x, y):
		return x * 10 + y

	num = s.split('.')
	num1 = reduce(f, map(char2num, num[0]))
	num2 = reduce(f, map(char2num, num[1]))/(10**len(num[1]))
	return num1 + num2

print('str2float(\'123.456\') =', str2float('123.456'))