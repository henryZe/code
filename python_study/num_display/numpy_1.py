# -*- coding: utf-8 -*-
"""
Created on Tue Oct 13 15:57:22 2020

@author: user
"""

import numpy as np

# calculate
if 0:
    def npSum():
        a = np.array([0, 1, 2, 3, 4])
        b = np.array([9, 8, 7, 6, 5])

        c = a ** 2 + b ** 3
        return c

    print(npSum())

# create
if 0:
    a = np.array([[0, 1, 2, 3, 4],
                 [9, 8, 7, 6, 5]])

    print(a.ndim)
    print(a.shape)
    print(a.size)
    print(a.dtype)
    print(a.itemsize)

    b = np.array([[0, 1, 2, 3, 4],
                 [9, 8, 7, 6]])

    print(b.ndim)
    print(b.shape)
    print(b.size)
    print(b.dtype)
    print(b.itemsize)

    a1 = np.array(((1, 2, 3), (4, 5, 6)))
    a2 = np.array(([1, 2, 3], (4, 5, 6)))

    a3 = np.arange(10)
    a4 = np.ones((3, 6), dtype = np.int32)
    a5 = np.zeros((3, 6))
    a6 = np.full((3, 6), 10)
    a7 = np.eye(5)

    a8 = np.ones((2, 3, 6), dtype = np.int32)

    a9 = np.ones_like(a1)
    a10 = np.full_like(a1, 10)

    a11 = np.linspace(1, 10, 4)
    a12 = np.linspace(1, 10, 4, endpoint = False)

    a13 = np.concatenate((a11, a12))

    # transform
    a14 = np.ones((3, 4, 5), dtype=np.int32)
    # not modify self
    a15 = a14.reshape((15, 4))
    # modify self
    a14.resize((4, 15))
    a16 = a15.flatten()
    # swap line & conlumn
    a17 = a14.swapaxes(1, 0)

    new_a = a17.astype(np.float)
    l1 = new_a.tolist()

# slice
if 0:
    a = np.arange(24).reshape((2, 3, 4))
    n1 = a[1, 2, 3]
    n2 = a[-1, -2, -3]
    print(n1, n2)

    a1 = a[:, 1, -3]
    a2 = a[:, 1:3, :]
    a3 = a[:, :, ::2]

# calculate
if 0:
    a = np.arange(24).reshape((2, 3, 4))
    print(a.mean())
    a = a / a.mean()

if 0:
    a = np.arange(24).reshape((2, 3, 4))
    print(np.square(a))
    b = np.sqrt(a)
    print(np.modf(b))

    print(np.maximum(a, b))
    print(a > b)
