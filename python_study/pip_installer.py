#!/usr/bin/python3
# -*- coding: utf-8 -*-

import os

f = open("libs.txt")
libs = f.readlines()
f.close()

try:
    for lib in libs:
        lib.strip("\n")
        print("Installing {} ...".format(lib))
        os.system("pip install " + lib)
    print("Successful")
except:
    print("Failed")
