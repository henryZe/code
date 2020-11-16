# -*- coding: utf-8 -*-

import numpy as np

if 0:
    a = np.arange(100).reshape(5, 20)

    # separate sign as "delimiter"
    np.savetxt("a.csv", a, fmt="%.1f", delimiter=",")

    # if unpack is True, load into different variable
    b = np.loadtxt("a.csv", dtype=np.int, delimiter=",")

if 0:
    a = np.arange(100).reshape(5, 10, 2)
    a.tofile("b.csv", sep=",", format="%d")
    a.tofile("b.dat", format="%d")

    # count: -1 means the whole file
    # sep: if NULL, write with binary format
    # a.fromfile(frame, dtype, count, sep)
    b = np.fromfile("b.csv", dtype=np.int, sep=",")
    c = np.fromfile("b.csv", dtype=np.int, sep=",").reshape(5, 10, 2)

if 0:
    a = np.arange(100).reshape(5, 10, 2)
    np.save("a.npy", a)
    b = np.load("a.npy")
    
if 0:
    a = np.random.rand(3, 4, 5)
    b = np.random.randn(3, 4, 5)
    c = np.random.randint(100, 200, (3, 4))
    np.random.seed(10)
    d = np.random.randint(100, 200, (3, 4))

    np.random.shuffle(d)
    e = np.random.permutation(d)

if 0:
    a = np.random.randint(100, 200, (8,))
    b = np.random.choice(a, (3, 2))
    # no repeated item
    c = np.random.choice(a, (3, 2), replace=False)
    # p means probability
    d = np.random.choice(a, (3, 2), p = a/np.sum(a))

if 0:
    # 均匀分布
    # uniform(low, high, size)
    u = np.random.uniform(0, 10, (3, 4))
    # 正态分布
    # normal(loc, scale, size)
    n = np.random.normal(10, 5, (3, 4))
    # 泊松分布 
    # poisson(lam, size)

if 0:
    a = np.arange(15).reshape(3, 5)
    b = np.sum(a)
    c = np.mean(a, axis=1)
    d = np.mean(a, axis=0)

    e = np.average(a, axis=0, weights=[10, 5, 1])
    f = np.std(a)
    g = np.var(a) 
    
if 0:
    a = np.arange(15, 0, -1).reshape(3, 5)
    b = np.max(a)
    c = np.min(a)
    print(np.argmax(a))
    print(np.argmin(a))
    print(np.unravel_index(np.argmax(a), a.shape))
    print(np.ptp(a))
    print(np.median(a))

if 0:
    a = np.random.randint(0, 20, (5))
    print(np.gradient(a))
    
    c = np.random.randint(0, 50, (3, 5))
    print(c)
    print(np.gradient(c))
