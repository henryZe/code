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
        print("predict games: playerA & playerB")

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
