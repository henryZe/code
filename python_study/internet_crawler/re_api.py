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

if 1:
    # pattern, string,
    # flags(re.I(GNORECASE), re.M(ULTILINE) '^'每行当作匹配开始, re.S/re.DOTALL '.'匹配所有字符(包括'\n'))
    match = re.search(r'[1-9]\d{5}', 'BIT 100081')
    if match:
        print(match.group(0))

    # match from the first character in string
    match = re.match(r'[1-9]\d{5}', 'BIT 100081')
    if match:
        print(match.group(0))

    match = re.match(r'[1-9]\d{5}', '100081 BIT')
    if match:
        print(match.group(0))

    # return all matched sub-string
    j

    # re.findall()
    # re.split()
    # re.finditer()
    # re.sub()


