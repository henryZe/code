# -*- coding: utf-8 -*-
"""
Created on Fri Nov 20 14:42:23 2020

@author: user
"""

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

if 0:
    d = pd.Series(range(20))
    print(d)
    print(d.cumsum())

if 0:
    # List
    a = pd.Series([9, 8, 7, 6], index = ['a', 'b', 'c', 'd'])
    print(a)

if 0:
    # 标量值
    a = pd.Series(25, index = ['a', 'b', 'c', 'd'])
    print(a)

    # 字典类型
    b = pd.Series({'a':9, 'b':8, 'c':7})
    print(b)
    c = pd.Series({'a':9, 'b':8, 'c':7}, index = ['c', 'a', 'b', 'd'])
    print(c)

    # ndarray
    d = pd.Series(np.arange(5))
    print(d)
    e = pd.Series(np.arange(5), index = np.arange(9, 4, -1))
    print(e)

    print(e.index)
    print(e.values)

    print(b['a'], b[0])
    print(b[['c', 'b', 'a']])

if 0:
    a = pd.Series([9, 8, 7, 6], index = ['a', 'b', 'c', 'd'])
    print(a)
    print(a[3])
    print(a[:3])
    print(a[a > a.median()])
    print(np.exp(a))

    print('c' in a)
    print(0 in a)
    print(a.get('f', 100))

if 0:
    a = pd.Series([1, 2, 3], ['c', 'd', 'e'])
    b = pd.Series([9, 8, 7, 6], ['a', 'b', 'c', 'd'])

    print(a + b)

if 0:
    b = pd.Series([9, 8, 7, 6], ['a', 'b', 'c', 'd'])
    print(b.name)

    b.name = "Series Object"
    b.index.name = "Index Name"
    print(b)

if 0:
    b = pd.Series([9, 8, 7, 6], ['a', 'b', 'c', 'd'])
    print(b)
    b['a'] = 15
    b.name = "Series"
    b['b', 'c'] = 20
    print(b)

if 0:
    # nparray
    b = pd.DataFrame(np.arange(10).reshape(2, 5))
    print(b)

    # dict & Series
    dt = {"one": pd.Series([1, 2, 3], index = ['a', 'b', 'c']),
          "two": pd.Series([9, 8, 7, 6], index = ['a', 'b', 'c', 'd'])}
    d = pd.DataFrame(dt)
    print(d)

    e = pd.DataFrame(dt, index = ['b', 'c', 'd'], columns = ['two', 'three'])
    print(e)

    # list & dict
    dl = {'one': [1, 2, 3, 4], 'two': [9, 8, 7, 6]}
    f = pd.DataFrame(dl, index = ['a', 'b', 'c', 'd'])
    print(f)

if 0:
    dl = {"城市": ["Beijing", "Shanghai", "Guangzhou", "Shenzhen", "Shenyang"],
          "环比": [101.5, 101.2, 101.3, 102.0, 100.1],
          "同比": [120.7, 127.3, 119.4, 140.9, 101.4],
          "定基": [121.4, 127.8, 120.0, 145.5, 101.6]}

    d = pd.DataFrame(dl, index = ['c1', 'c2', 'c3', 'c4', 'c5'])
    print(d)
    print(d.index)
    print(d.columns)
    print(d.values)

    print(d['同比'])
    print(d['同比']['c2'])

    e = d.reindex(index = ['c5', 'c4', 'c3', 'c2', 'c1'])
    print(d)
    print(e)

    # index, columns
    # fill_value
    # method(ffill: forward fill, bfill: backward fill)
    # limit: max filled slots
    # copy: True, copy; False, non-copy
    f = d.reindex(columns = ['城市', '定基', '环比', '同比'])
    print(f)

    newc = d.columns.insert(4, '新增')
    print(newc)
    newd = d.reindex(columns = newc, fill_value = 200)
    print(newd)

    # nc = d.columns.delete(2)
    nc = d.columns
    print(nc)
    ni = d.index.insert(5, 'c0')
    print(ni)
    nd = d.reindex(index = ni, columns = nc, method = 'bfill')
    print(nd)

    print(d.drop('c5'))
    print(d.drop('同比', axis = 1))

if 0:
    b = pd.Series([9, 8, 7, 6], ['a', 'b', 'c', 'd'])
    print(b)
    print(b.drop(['b', 'c']))

if 0:
    a = pd.DataFrame(np.arange(12).reshape(3, 4))
    print(a)
    b = pd.DataFrame(np.arange(20).reshape(4, 5))
    print(b)

    print(a + b)
    print(a * b)

    print(b.add(a, fill_value = 100))
    print(b.mul(a, fill_value = 0))

if 0:
    b = pd.DataFrame(np.arange(20).reshape(4, 5))
    print(b)
    c = pd.Series(np.arange(4))
    print(c)

    # Broadcast Calculate
    print(c - 10)
    print(b - c)
    print(b.sub(c, axis = 1))

if 0:
    a = pd.DataFrame(np.arange(12).reshape(3, 4))
    print(a)
    b = pd.DataFrame(np.arange(12, 0, -1).reshape(3, 4))
    print(b)
    print(a > b)
    print(a == b)

if 0:
    a = pd.DataFrame(np.arange(12).reshape(3, 4))
    print(a)
    c = pd.Series(np.arange(4))
    print(c)

    print(a > c)
    print(c > 0)

if 0:
    # sort_index: axis = 0, ascending = True(升序排序)
    b = pd.DataFrame(np.arange(20).reshape(4, 5), index = ['c', 'a', 'd', 'b'])
    print(b)
    print(b.sort_index())
    print(b.sort_index(ascending = False))
    print(b.sort_index(axis = 1, ascending = False))

if 0:
    # sort_index: axis = 0, ascending = True(升序排序)
    b = pd.DataFrame(np.arange(20).reshape(4, 5), index = ['c', 'a', 'd', 'b'])
    print(b)
    # axis = 0, 按照 column = 2 降序排列
    print(b.sort_values(2, ascending = False))
    print(b.sort_values('a', axis = 1, ascending = False))

    a = pd.DataFrame(np.arange(12).reshape(3, 4), index = ['a', 'b', 'c'])
    c = a + b
    print(c)
    print(c.sort_values(2, ascending = False))
    print(c.sort_values(2))

if 0:
    a = pd.Series([9, 8, 7, 6], index = ['a', 'b', 'c', 'd'])
    print(a)
    print(a.describe())
    print(type(a.describe()))
    print(a.describe()['count'])
    print(a.describe()['max'])

if 0:
    b = pd.DataFrame(np.arange(20).reshape(4, 5), index = ['c', 'a', 'd', 'b'])
    print(b)
    # axis = 0
    print(b.describe())
    print(type(b.describe()))
    print(b.describe()[2])

if 0:
    b = pd.DataFrame(np.arange(20).reshape(4, 5), index = ['c', 'a', 'd', 'b'])
    print(b)

    # axis = 0
    print(b.cumsum())
    print(b.cumprod())
    print(b.cummin())
    print(b.cummax())

    # axis = 0, r(n - r + 1) + ... + r(n - 1) + r(n)
    print(b.rolling(2).sum())
    print(b.rolling(3).sum())

if 0:
    house_price = pd.Series([3.04, 22.93, 12.75, 22.6, 12.33],
                            index = ['2008', '2009', '2010', '2011', '2012'])
    m2 = pd.Series([8.18, 18.38, 9.13, 7.82, 6.69],
                            index = ['2008', '2009', '2010', '2011', '2012'])

    related = house_price.corr(m2)
    print(related)
    if related > 0.8:
        print("extreme strong related")
    elif related > 0.6:
        print("strong related")
    elif related > 0.4:
        print("median related")
    elif related > 0.2:
        print("weak related")
    else:
        print("none related")

    plt.plot(house_price)
    plt.plot(m2)

    plt.xlabel("year")
    plt.ylabel("RMB")
