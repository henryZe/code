#!/usr/bin/python3
# -*- coding: utf-8 -*-

#dictionary
d = {'Mike': 95, 'Bob': 75, 'Tracy': 90}
print(d['Mike'])
print('Henry' in d)
print(d.get('Bob'))
d.pop('Bob')
print(d)

#set
s1 = set([1, 2, 3, 1, 2])
s1.add(4)
s1.remove(1)
s2 = set([4, 5, 6, 7])
print('s1 =', s1)
print('s2 =', s2)
print('s1 & s2 =', s1 & s2)
print('s1 & s2 =', s1 | s2)

a = 'abc'
b = a.replace('a', 'A')
print (a)
print (b)
