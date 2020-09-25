#!/usr/bin/python3
# -*- coding: utf-8 -*-

import jieba

book = input()
if book == "":
    book = "shuihu.txt"

txt = open(book, "r", encoding="utf-8").read()

excludes = {"将军", "却说", "荆州", "二人", "不可", "不能", "如此", \
            "商议", "如何", "军士", "左右", "主公", "军马", "引兵", \
            "次日", "大喜", "两个", "一个", "如何", "那里", "只见", \
            "哥哥", "说道", "头领", "众人", "兄弟", "这里", "出来", \
            "小人", "这个"}

words = jieba.lcut(txt)

counts = {}
for word in words:
    if len(word) == 1:
        continue
    elif word in excludes:
        continue
    # elif word == "孟德" or word == "丞相":
    #     word = "曹操"
    # elif word == "孔明" or word == "孔明曰":
    #     word = "诸葛亮"
    # elif word == "玄德" or word == "玄德曰":
    #     word = "刘备"
    # elif word == "关公" or word == "云长":
    #     word = "关羽"

    counts[word] = counts.get(word, 0) + 1

items = list(counts.items())
items.sort(key = lambda x:x[1], reverse=True)

for i in range(20):
    word, count = items[i]
    print("{:<10}{:>5}".format(word, count))
