#!/usr/bin/python3
# -*- coding: utf-8 -*-

#encode
print('ABC'.encode('ascii'))
print(b'ABC'.decode('ascii'))

print('中文'.encode('utf-8'))
print(b'\xe4\xb8\xad\xe6\x96\x87'.decode('utf-8'))

print(len('ABC'))
print(len('中文'))

temp = input()
print('hello, %s, you have %d' % (temp, 100))
print('%2d - %02d' % (3, 1))
print('%.2f %%' % 3.14159)

print('%02.1f%%' % ((85-72)/72))