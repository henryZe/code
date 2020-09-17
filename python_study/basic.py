#!/usr/bin/python3
# -*- coding: utf-8 -*-

#basic
name = input('what\'s your name:')
print((100+200), ('hello,'), name)

if name == 'henry':
	print('hello henry')
else:
	print('you are lying')
	print(9.23e-1)

print(5>3 and (3<1 or 1<4))

a = 'abc'
b = a
a = 'xyz'
print(b)

n = 123
f = 456.789
s1 = 'Hello, world'
s2 = 'Hello, \'Adam\''
s3 = r'Hello, "Bart"'
s4 = r'''Hello,
Lisa!'''
print(n, f, s1, s2, s3, s4)

print('好的')
print(ord('A'), chr(65))

exit()
