#!/usr/bin/python3
# -*- coding: utf-8 -*-

if 0:
    import random

    def main():
        printIntro()
        probA, probB, n = getInputs()
        winsA, winsB = simNGames(n, probA, probB)
        printSummary(winsA, winsB)

    def printIntro():
        print("predict games result: playerA & playerB")

    def getInputs():
        a = eval(input("A value(0-1):"))
        b = eval(input("B value(0-1):"))
        n = eval(input("how many matches:"))
        return a, b, n

    def gameOver(scoreA, scoreB):
        return scoreA >= 15 or scoreB >= 15

    def simOneGame(probA, probB):
        scoreA, scoreB = 0, 0

        serving = "A"
        while not gameOver(scoreA, scoreB):
            if serving == "A":
                if random.random() < probA:
                    scoreA += 1
                else:
                    serving = "B"
            else:
                if random.random() < probB:
                    scoreB += 1
                else:
                    serving = "A"

        return scoreA, scoreB

    def simNGames(n, probA, probB):
        winsA, winsB = 0, 0
        for i in range(n):
            scoreA, scoreB = simOneGame(probA, probB)
            if scoreA > scoreB:
                winsA += 1
            else:
                winsB += 1
        return winsA, winsB

    def printSummary(winsA, winsB):
        n = winsA + winsB
        print("Matches: {}".format(n))
        print("Player A {}, {:0.1%}".format(winsA, winsA / n))
        print("Player B {}, {:0.1%}".format(winsB, winsB / n))

    main()

if 0:
    import os.path, time

    # absolute path
    print(os.path.abspath("./week_8.py"))
    # relate path
    print(os.path.relpath("./week_8.py"))
    # directory name
    print(os.path.dirname("./week_8.py"))
    # file name
    print(os.path.basename("./week_8.py"))

    # access
    print(time.ctime(os.path.getatime("./week_8.py")))
    # modify
    print(time.ctime(os.path.getmtime("./week_8.py")))
    # create
    print(time.ctime(os.path.getctime("./week_8.py")))

    print(os.path.getsize("./week_8.py"))

if 0:
    import os

    os.system("C:\Windows\System32\calc.exe")
    os.system("C:\Windows\System32\mspaint.exe ./output.png")

if 0:
    import os

    # change directory
    os.chdir("D:\\")
    print(os.getcwd())
    print(os.getlogin())
    print(os.cpu_count())
    print(os.urandom(10))
