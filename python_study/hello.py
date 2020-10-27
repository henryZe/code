#!/usr/bin/python3
# -*- coding: utf-8 -*-

'a test module'

__author__ = 'henry zeng'

import sys

def test():
	print(__name__)

	args = sys.argv
	if len(args) == 1:
		print('hello world')
	elif len(args) == 2:
		print('hello, %s' % args[1])
	else:
		print('too many args!')

if __name__ == '__main__':
	test()