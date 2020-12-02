# -*- coding: utf-8 -*-
"""
Created on Tue Dec  1 11:52:03 2020

@author: user
"""

import re

# . 表示任何单个字符
# [] 表示对单个字符给出取值范围
# [^] 表示对单个字符排除范围
# * 前一个字符0次或无限次扩展
# + 前一个字符1次或无限次扩展
# ? 前一个字符0次或1次扩展
# | 左右表达式任意一个
# {m} 扩展前一个字符m次
# {m, n} 扩展前一个字符m至n次(含n)
# ^ 匹配字符串开头
# $ 匹配字符串结尾
# () 分组标记,内部只能使用'|'
# \d 数字,等价于[0-9]
# \w 单词字符,等价于[A-Za-z0-9_]

# ^[A-Za-z]+$
# 26个字母组成的字符串

# ^[A-Za-z0-9]+$
# 26个字母和数字组成的字符串

# ^-?\d+$
# 整数形式的字符串

# ^[0-9]*[1-9][0-9]*$
# 正整数形式的字符串

# [\u4e00-\u9fa5]
# 匹配中文字符

# IP addr
# 0 - 99 : [1-9]?\d
# 100 - 199 : 1\d{2}
# 200 - 249 : 2[0-4]\d
# 250 - 255 : 25[0-5]
# (([1-9]?\d | 1\d{2} | 2[0-4]\d | 25[0-5]).){3} ([1-9]?\d | 1\d{2} | 2[0-4]\d | 25[0-5])

if 0:
    # return the first match one
    # pattern, string,
    # flags(re.I(GNORECASE), re.M(ULTILINE) '^'每行当作匹配开始, re.S/re.DOTALL '.'匹配所有字符(包括'\n'))
    match = re.search(r'[1-9]\d{5}', 'BIT 100081')
    if match:
        print(type(match))
        print(match.group(0))

if 0:
    # match from the first character in string
    match = re.match(r'[1-9]\d{5}', 'BIT 100081')
    if match:
        print(match.group(0))

    match = re.match(r'[1-9]\d{5}', '100081 BIT')
    if match:
        print(type(match))
        print(match.group(0))

if 0:
    # return all matched sub-string
    ls = re.findall(r'[1-9]\d{5}', 'BIT100081 TSU100084')
    if ls:
        print(type(ls))
        for i in range(len(ls)):
            print(ls[i])

if 0:
    # return split string, maxsplit: regard residue string as the last element
    ls = re.split(r'[1-9]\d{5}', 'BIT100081 TSU100084')
    if ls:
        print(type(ls))
        for i in range(len(ls)):
            print(ls[i])

    ls = re.split(r'[1-9]\d{5}', 'BIT100081 TSU100084', maxsplit = 1)
    if ls:
        for i in range(len(ls)):
            print(ls[i])

if 0:
    # equal to findall
    for match in re.finditer(r'[1-9]\d{5}', 'BIT100081 TSU100084'):
        if match:
            print(type(match))
            print(match.group(0))

if 0:
    # replace match sub-strings, and return result
    # repl: replace string
    # count: replace limited times
    str = re.sub(r'[1-9]\d{5}', ':zipcode', 'BIT100081 TSU100084')
    print(type(str))
    print(str)

if 0:
    # Object program
    # compile: pattern, flag
    pattern = re.compile(r'[1-9]\d{5}')
    result = pattern.search('BIT 100081')

if 0:
    match = re.search(r'[1-9]\d{5}', 'BIT100081 TSU100084')
    if match:
        print(type(match))
        print(match.group(0))
        print(match.string)
        print(match.re)
        print(match.pos)
        print(match.endpos)
        print(match.group(0))
        print(match.start())
        print(match.end())
        print(match.span())

if 0:
    # default: 贪婪匹配
    match = re.search(r'PY.*N', 'PYANBNCNDN')
    print(match.group(0))

    # 最小匹配
    match = re.search(r'PY.*?N', 'PYANBNCNDN')
    print(match.group(0))

    # *? : 0 to infinite, 最小匹配
    # +? : 1 to infinite, 最小匹配
    # ?? : 0 or 1, 最小匹配
    # {m, n}?: m to n, 最小匹配
