#!/usr/bin/python3
# -*- coding: utf-8 -*-

#list
classmate = ['bert', 123, True, ['gg', 'hh']]
print(len(classmate), classmate[0], classmate[-2], classmate[-1][1])
classmate.append('youri')
classmate.insert(1, 'barry')
print(classmate)
classmate.pop()
classmate.pop(2)
print(classmate)
a = ['c', 'b', 'a']
print(a)
a.sort()
print(a)

#tuple
t = (1, )


L = [
	['Apple', 'Google', 'Microsoft'],
    ['Java', 'Python', 'Ruby', 'PHP'],
    ['Adam', 'Bart', 'Lisa']
]

print(L[0][0], L[1][1], L[-1][-1])
