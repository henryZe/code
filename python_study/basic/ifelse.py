#!/usr/bin/python3
# -*- coding: utf-8 -*-

#if
age = int(input())

if age >= 18:
    print('adult')
elif age >= 6:
    print('teenager')
else:
    print('kid')

height = 1.79
weight = 60.5

bmi = weight / (height * height)
print(bmi)
if bmi < 18.5:
	print('too weak')
elif 18.5 <= bmi < 25:
	print('normal')
elif 25 <= bmi < 28:
	print('fat')
else:
	print('too fat')
