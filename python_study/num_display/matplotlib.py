# -*- coding: utf-8 -*-
"""
Created on Tue Oct 13 15:57:22 2020

@author: user
"""

import matplotlib.pyplot as plt
import matplotlib
import numpy as np

if 0:
    plt.plot([3, 1, 4, 5, 2])
    plt.ylabel("grade")
    plt.savefig("test.png", dpi=600)
    plt.show()

if 0:
    plt.plot([0, 2, 4, 6, 8], [3, 1, 4, 5, 2])
    plt.ylabel("Grade")
    # Xstart, Xend, Ystart, Yend
    plt.axis([-1, 10, 0, 6])
    plt.show()

if 0:
    # 绘图区域
    # nrows, ncols, plot_number
    plt.subplot(3, 2, 4)

if 0:
    def f1(t):
        return np.exp(-t) * np.cos(2 * np.pi * t)
    
    def f2(t):
        return np.cos(2 * np.pi * t)
    
    a = np.arange(0, 5, 0.02)
    
    plt.subplot(2, 1, 1)
    plt.plot(a, f1(a))

    plt.subplot(2, 1, 2)
    plt.plot(a, f2(a), "r--")
    plt.show()
    
if 0:
    a = np.arange(10)
    # color + linestyle"线条风格" + marker"标记风格"
    plt.plot(a, a * 1.5, "r-.o", a, a * 2.5, "b:", a, a * 3.5, "yp", a, a * 4.5, "gd")
    plt.show()
    
if 0:
    # 黑体
    matplotlib.rcParams["font.family"] = "SimHei"
    plt.plot([3, 1, 4, 5, 2])
    plt.ylabel("纵轴(值)")
    plt.savefig("test", dpi=600)
    plt.show()

if 0:
    # 华文宋体
    matplotlib.rcParams["font.family"] = "STSong"
    matplotlib.rcParams["font.size"] = 20

    a = np.arange(0, 5, 0.02)
    plt.xlabel("横轴(值)：时间")
    plt.ylabel("纵轴(值)：振幅")

    plt.plot(a, np.cos(2 * np.pi * a), "r--")
    plt.savefig("test.png", dpi=600)
    plt.show()

if 0:
    a = np.arange(0, 5, 0.02)
    plt.xlabel("横轴(值)：时间", fontproperties="STSong", fontsize=10)
    plt.ylabel("纵轴(值)：振幅", fontproperties="STSong", fontsize=10)

    plt.plot(a, np.cos(2 * np.pi * a), "r--")
    plt.show()

if 1:
    


