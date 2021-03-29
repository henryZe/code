#!/usr/bin/python3
# -*- coding: utf-8 -*-

import functools

def lazy_sum(*args):
    def sum():
        ax = 0
        for n in args:
            ax = ax + n
        return ax
    return sum

f1 = lazy_sum(1, 3, 5, 7, 9)
f2 = lazy_sum(1, 3, 5, 7, 9)

print(f1(), f1 == f2)
print(f2())


# lambda
f = lambda x: x * x
print(f(6))


# decorator
def log(text):
	def decorator(func):
		def wrapper(*args, **kw):
			print('%s %s():' % (text, func.__name__))
			return func(*args, **kw)
		return wrapper
	return decorator

@log('execute')
def now():
    print('2015-3-25')

now()


# partial
print(int('1234567', base = 8))

def int2(x, base = 2):
	return int(x, base)

print(int2('1010100101'))

int8 = functools.partial(int, base = 8)
print(int8('2352'))

max2 = functools.partial(max, 10)
print(max2(1,2,3,4))