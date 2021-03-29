#!/usr/bin/python3
# -*- coding: utf-8 -*-

file_name = 'file_rw.py'
file_write = 'test'

# read
f = open(file_name, 'r')
print(f.read())
f.close()

try:
	f = open(file_name, 'r')
	print(f.read())
finally:
	if f:
		f.close()

with open(file_name, 'r') as f:
	while True:
		ctx = f.readline()
		if ctx:
			print(ctx.strip())
		else:
			break

# write
with open(file_write, 'w') as f:
	f.write('write bytes')


# stringIO
from io import StringIO
from io import BytesIO

f = StringIO()
f.write('henry')
f.write(' ok?')
print(f.getvalue())

f = StringIO('hello\nhi\ngoodbye')
while True:
	s = f.readline()
	if s is '':
		break
	print(s.strip())

f = BytesIO()
f.write('中文'.encode('utf-8'))
print(f.getvalue())


# os
import os
print(os.name)
print(os.uname())
print(os.environ)
print(os.environ.get('PATH'))
print(os.path.abspath('.'))
os.mkdir(os.path.join('.', 'testdir'))
os.rmdir(os.path.join('.', 'testdir'))

print([x for x in os.listdir('.') if os.path.isdir(x)])
print([x for x in os.listdir('.') if os.path.splitext(x)[1] == '.py'])


# 1
print('1st Q')
for x in os.listdir('.'):
	print(x)

# 2
print('2nd Q')

def search_dir(direct, file_name):
	for x in os.listdir(direct):
		if os.path.isfile(os.path.join(direct, x)):
			if x == file_name:
				print(os.path.abspath(os.path.join(direct, x)))

		elif os.path.isdir(os.path.join(direct, x)):
			search_dir(os.path.join(direct, x), file_name)

search_dir('.', 'target')


# pickle
import pickle

d = dict(name='Bob', age=20, score=80)

file = open('dump.txt', 'wb')
pickle.dump(d, file)
file.close()

file = open('dump.txt', 'rb')
dl = pickle.load(file)
f.close()
print(dl)



