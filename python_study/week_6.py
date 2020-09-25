#!/usr/bin/python3
# -*- coding: utf-8 -*-

if 0:
    # set feature:
    # A. unique
    # B. un-sort
    # C. constant
    A = {"python", 123, ("python", 123)}
    print(A)
    B = set("pypy123")
    print(B)

    # '-', '&', '|', '^'
    A = {"p", "y", 123}
    B = set("pypy123")
    print(A - B)
    print(B - A)
    print(A & B)
    print(A | B)
    print(A ^ B)

if 0:
    A = {"p", "y", 123}

    # add discard remove clear pop
    # copy len set in not in
    for i in A:
        print(i)

    try:
        while True:
            print(A.pop())
    except:
        pass

if 0:
    # discard redundant data
    ls = ["p", "y", "p", "y", 123]
    temp = set(ls)
    ls = list(temp)
    print(ls)

if 0:
    # array
    # in not in + * [index] [i:j:k]
    ls = ["python", 123, ".io"]
    print(ls[::-1])
    print(len(ls))
    print(ls.count(123))

if 0:
    # string
    str = "python123.io"
    print(min(str))
    print(max(str))
    print(str.index("1"))
    print(str.count("o"))

if 0:
    # tuple
    # not allow to modify ()
    creature = "cat", "dog", "tiger", "human"
    color = (0x001100, "blue", creature)
    print(color[-1][2])

if 0:
    # list
    # []
    ls = ["cat", "dog", "tiger", 1024]
    ls[1:2] = [1, 2, 3, 4]
    print(ls)

    del ls[::3]
    print(ls)
    print(ls * 2)

    ls.append(1234)
    print(ls)

    ls.insert(3, "human")
    print(ls)

    ls.reverse()
    print(ls)

if 0:
    ls = list()
    print(ls)

    ls += (1, 2, 3, 4, 5)
    print(ls)

    ls[2] = "1234"
    print(ls)

    ls.insert(2, "insert")
    print(ls)

    ls.pop(1)
    del ls[1]
    print(ls)

    del ls[1:4]
    print(ls)

    print(ls.count(0))
    print(0 in ls)
    ls.append(0)
    print(ls.count(0))
    print(ls.index(0))

    print(len(ls))
    print(max(ls))

    ls.clear()
    print(ls)

if 0:
    def getNum():
        nums = []

        iNumStr = input("num:")
        while iNumStr != "":
            nums.append(eval(iNumStr))
            iNumStr = input("num:")

        return nums

    def mean(nums):
        s = 0.0

        for num in nums:
            s += num
        return s / len(nums)

    def dev(nums, mean):
        sdev = 0.0

        for num in nums:
            sdev += (num - mean) ** 2

        return pow(sdev / (len(nums) - 1), 0.5)

    def median(nums):
        nums = sorted(nums)
        size = len(nums)

        if size % 2 == 0:
            med = (nums[size // 2 - 1] + nums[size // 2])/2
        else:
            med = nums[size // 2]
        return med

    n = getNum()
    m = mean(n)
    print("mean 平均值: {} median 中位数: {} variance 方差: {}".format(m, median(n), dev(n, m)))

if 0:
    # dictionary
    dic = {}
    print(type(dic))

    d = {"China":"Beijing", "America":"Washington", "France":"Paris"}
    print("China" in d)
    print(d.keys())
    print(d.values())

    print(d.get("China", "Islambad"))
    print(d.get("Pakistan", "Islambad"))
    print(d.popitem())

if 0:
    d = {}
    d["China"] = "Beijing"
    d["Korea"] = "Seoul"

    d["Korea"] = "HanCity"

    print("Korea" in d)
    print(len(d))

    d.clear()

if 1:
    