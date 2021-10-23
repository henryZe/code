from typing import List

class Solution:
    def numRabbits(self, answers: List[int]) -> int:
        rabbitDict = {}
        for a in answers:
            if a not in rabbitDict:
                rabbitDict[a] = 1
            else:
                rabbitDict[a] += 1
        num = 0
        for key in rabbitDict.keys():
            while rabbitDict[key] > (key + 1):
                num += key + 1
                rabbitDict[key] -= key + 1
            num += key + 1
        return num

answers = [1, 1, 2]
answers = [10, 10, 10]
answers = []
print(Solution().numRabbits(answers))