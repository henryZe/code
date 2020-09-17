#!/usr/bin/python3
# -*- coding: utf-8 -*-

# oop
# data packaging
# restricting access

class Student(object):
 
	position = 'student'

	def __init__(self, name, score):
		self.__name = name
		self.__score = score

	def get_name(self):
		return self.__name

	def get_score(self):
		return self.__score

	def set_score(self, score):
		if 0 <= score <= 100:
			self.__score = score
		else:
			return ValueError('bad score')

	def print_score(self):
		print('%s %s' % (self.__name, self.__score))

	def get_grade(self):
		if self.__score >= 90:
			return 'A'
		elif self.__score >= 60:
			return 'B'
		else:
			return 'C'

bart = Student('bart', 59)
lisa = Student('lisa', 87)
bart.print_score()
lisa.print_score()
print('%s grade: %s' % (lisa._Student__name, lisa.get_grade()))
bart.age = 8
print('bart age: %d' % bart.age)
s = Student('henry', 100)
print(s.position)
print(Student.position)


# inherit
class Animal(object):
	def run(self):
		print('Animal borned')

	def run_twice(self):
		Animal.run(self)
		Animal.run(self)

class Dog(Animal):
	def yell(self):
		print('wow! wow!') 

class Cat(Animal):
	def yell(self):
		print('miao! miao!') 

cat = Cat()
dog = Dog()
cat.run()
cat.run_twice()
cat.yell()
dog.yell()

print(isinstance(dog, object))
print(isinstance(dog, Animal))
print(isinstance(dog, Dog))

animal = Animal()
print(isinstance(animal, Dog))


# gain object info
print(type([1, 1, 745]) == list)
print(isinstance([1, 1, 745], (tuple, list)))
print(dir('hsdafjk'))

print(hasattr(dog, 'run'))
setattr(lisa, 'x', 19)
print(getattr(dog, 'run'))
print(getattr(dog, 'x', 404))






