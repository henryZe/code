# -*- coding: utf-8 -*-
"""
Created on Wed Dec  2 19:34:24 2020

@author: user
"""

def gen(n):
    for i in range(n):
        yield i**2

def normal_gen(n):
    return [i ** 2 for i in range(n)]

def main():
    for i in gen(5):
        print(i)

    for i in normal_gen(5):
        print(i)

main()
