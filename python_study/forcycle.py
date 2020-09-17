#!/usr/bin/python3
# -*- coding: utf-8 -*-

#for
names = ['henry', 'bert', 'youri']
for name in names:
	print(name)

sum = 0
for x in list(range(101)):
	sum += x
print(sum)

sum = 0
n = 0
while n < 10:
	sum += n
	n += 1
print(sum)


L = ['Bart', 'Lisa', 'Adam']
for name in L:
	print('Hello, %s' % name)
