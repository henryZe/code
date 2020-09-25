#!/usr/bin/python3
# -*- coding: utf-8 -*-

def getText():
    txt = open("hamlet.txt", "r").read()
    txt = txt.lower()
    for ch in '!"#$%&()*+,-./:;<=>?@[\\]^_‘{|}~':
        txt = txt.replace(ch, " ")
    return txt

hamletTxt = getText()
# list
words = hamletTxt.split()
#dict
counts = {}
for word in words:
    counts[word] = counts.get(word, 0) + 1

items = list(counts.items())
items.sort(key = lambda x:x[1], reverse=True)

for i in range(10):
    word, count = items[i]
    print("{:<10}{:>5}".format(word, count))
