#!/usr/bin/python3
# -*- coding: utf-8 -*-

if 0:
    fd = open("output.txt", "w+")
    ls = ["中国", "法国", "美国"]
    fd.writelines(ls)
    fd.seek(0)
    for line in fd:
        print(line)
    fd.close()

if 0:
    import turtle as t

    t.title("自动轨迹绘制")
    t.setup(800, 600, 0, 0)
    t.pencolor("red")
    t.pensize(5)

    datals = []
    f = open("data.txt")
    for line in f:
        line = line.replace("\n", "")
        # 2D-array
        datals.append(list(map(eval, line.split(","))))
    f.close()

    for i in range(len(datals)):
        t.speed(1)
        t.pencolor(datals[i][3], datals[i][4], datals[i][5])
        t.fd(datals[i][0])
        if datals[i][1]:
            t.right(datals[i][2])
        else:
            t.left(datals[i][2])
    t.done()

if 0:
    fname = input("file:")
    # read CSV(comma seperated values) file
    fd = open(fname)
    ls = []
    for line in fd:
        line = line.replace("\n", "")
        ls.append(line.split(","))
    fd.close()

    fd = open(fname, "w")
    for item in ls:
        fd.write(",".join(item) + "\n")
    fd.close()

if 0:
    import wordcloud
    w = wordcloud.WordCloud(width=600, height=400)
    w.generate(open("hamlet.txt").read())
    w.to_file("output.png")

if 0:
    import wordcloud, jieba
    w = wordcloud.WordCloud(width=1000, height=700, font_path="msyh.ttc")
    txt = open("threekingdoms.txt", encoding="utf-8").read()
    w.generate(" ".join(jieba.lcut(txt)))
    w.to_file("output.png")

if 0:
    import wordcloud, jieba, imageio

    # f = open("Chinese_socialism.txt", encoding="utf-8")
    f = open("country_develop.txt", encoding="utf-8")
    t = f.read()
    f.close()

    mask = imageio.imread("fivestar.png")

    ls = jieba.lcut(t)
    txt = " ".join(ls)
    w = wordcloud.WordCloud(font_path="msyh.ttc", width=1000, height=700, \
                            background_color="white", mask=mask)
    w.generate(txt)
    w.to_file("output.png")
