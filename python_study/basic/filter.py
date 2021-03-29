#!/usr/bin/python3
# -*- coding: utf-8 -*-

# filter
def is_odd(n):
	return n % 2

print(list(filter(is_odd, [0, 1, 2, 3])))


def odd_iter():
	n = 2
	while True:
		yield n
		n += 1

def not_divisible(n):
	return lambda x: x % n

def primes():
	it = odd_iter()
	while True:
		n = next(it)
		yield n
		it = filter(not_divisible(n), it)

for n in primes():
	if n < 1000:
		print(n)
	else:
		break

print('is_palindrome:')

def is_palindrome(n):
	num = str(n)
	return num == num[::-1]

output = filter(is_palindrome, range(1, 10000))
print(list(output))


#sorted
print(sorted([23123,234,-456,23,143564], key = abs))
print(sorted(['bob', 'about', 'Zoo', 'Credit'], key = str.lower, reverse = True))


L = [('Bob', 75), ('Adam', 92), ('Bart', 66), ('Lisa', 88)]

def by_name(l):
	return l[0].lower()

def by_score(l):
	return l[1]

L2 = sorted(L, key = by_name)
print(L2)

L2 = sorted(L, key = by_score, reverse = True)
print(L2)