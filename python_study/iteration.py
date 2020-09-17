#!/usr/bin/python3
# -*- coding: utf-8 -*-

from collections import Iterable
import os

#iteration
d = {'a':1, 'b':2, 'c':3, 'd':4, 'e':5, 'f':6, 'g':7}
for key in d:
	print(key)

for value in d.values():
	print(value)

for k, v in d.items():
	print(k, v)

print(isinstance('abc', Iterable))
print(isinstance([1,2,3], Iterable))
print(isinstance(123, Iterable))


#list generator
print([x * x for x in range(1, 11) if x % 2 == 0])
print([m + n for m in 'ABC' for n in 'xyz'])

print([d for d in os.listdir('./')])


L1 = ['Hello', 'World', 18, 'Apple', None]
L2 = [l.lower() for l in L1 if isinstance(l, str)]
print(L2)


#generator
g = (x * x for x in range(10))
for n in g:
	print(n)

def fib(max):
	n, a, b = 0, 0, 1
	while n < max:
		yield b
		a, b = b, a + b
		n += 1
	return

for n in fib(10):
	print(n)

def yhtriangles():
	L = [1]
	while True:
		yield L
		L.append(0)
		L = [L[i - 1] + L[i] for i in range(len(L))]

n = 0
for t in yhtriangles():
	print(t)
	n += 1
	if n == 10:
		break


#iterator