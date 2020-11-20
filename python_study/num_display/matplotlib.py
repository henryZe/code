# -*- coding: utf-8 -*-
"""
Created on Tue Oct 13 15:57:22 2020

@author: user
"""

import matplotlib.pyplot as plt
import matplotlib
import numpy as np
import matplotlib.gridspec as gridspec

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
    plt.plot(a, np.cos(2 * np.pi * a), "r--")

    plt.xlabel("横轴(值)：时间", fontproperties="STSong", fontsize=10, color="green")
    plt.ylabel("纵轴(值)：振幅", fontproperties="STSong", fontsize=10)
    plt.title("正弦波实例 $y = cos(2*pi*x)$", fontproperties="STSong", fontsize=10)
    # x, y, text
    plt.text(2, 1, r'$\mu=100$', fontsize=10)
    # text, arrow x/y, text x/y, arrow properties
    plt.annotate(r'$\mu=100$', xy=(2, 1), xytext=(3, 1.5),
                arrowprops=dict(facecolor="black", shrink=0.1, width=2))

    plt.axis([-1, 6, -2, 2])
    plt.grid(True)
    plt.show()

if 0:
    plt.subplot2grid((3, 3), (1, 0), colspan=2)
    plt.subplot2grid((3, 3), (1, 2), rowspan=2)

if 0:
    gs = gridspec.GridSpec(3,3)

    ax1 = plt.subplot(gs[0, :])
    ax2 = plt.subplot(gs[1, :-1])
    ax3 = plt.subplot(gs[1:, -1])
    ax4 = plt.subplot(gs[2, 0])
    ax5 = plt.subplot(gs[2, 1])

if 0:
    # 坐标图
    plt.plot
    # 箱形图
    plt.boxplot
    # 条形图
    plt.bar
    # 横向条形图
    plt.barh
    # 极坐标图
    plt.polar
    # 饼图
    plt.pie
    # 功率谱密度图
    plt.psd
    # 谱图
    plt.specgram
    # X-Y相关性函数
    plt.cohere
    # 散点图
    plt.scatter
    # 步阶图
    plt.step
    # 直方图
    plt.hist
    # 等值图
    plt.contour
    # 垂直图
    plt.vlines
    # 柴火图
    plt.stem
    # 数据日期
    plt.plot_date

if 0:
    labels = "Frogs", "Hogs", "Dogs", "Logs"
    sizes = [15, 30, 45, 10]
    # out-standing
    explode = (0, 0.1, 0, 0)

    plt.pie(sizes, explode=explode, labels=labels, autopct="%1.1f%%",
            shadow=False, startangle=90)
    plt.axis("equal")
    plt.show()

if 0:
    np.random.seed(0)
    # 均差, 标准差
    mu, sigma = 100, 20
    # 次数为 100
    a = np.random.normal(mu, sigma, size=100)
    
    # b 为直方个数
    plt.hist(a, 10, normed=1)
    plt.title("Histogram")

    plt.show()

if 0:
    # number
    N = 20

    # 2pi 等分区域
    theta = np.linspace(0.0, 2 * np.pi, N, endpoint=False)
    # 长度
    radii = 10 * np.random.rand(N)
    # 宽度
    width = np.pi / 4 * np.random.rand(N)

    ax = plt.subplot(111, projection="polar")
    bars = ax.bar(theta, radii, width=width, bottom=0.0)

    for r, bar in zip(radii, bars):
        bar.set_facecolor(plt.cm.viridis(r/10.))
        bar.set_alpha(0.5)

    plt.show()

if 0:
    # 图表, 区域 defalt:1,1,1
    fig, ax = plt.subplots()
    # x, y, sign
    ax.plot(10 * np.random.randn(100), 10 * np.random.randn(100), "o")
    ax.set_title("Simple Scatter")

    plt.show()
