from typing import List
import collections

class Solution:
    def findLadders(self, beginWord: str, endWord: str, wordList: List[str]) -> List[List[str]]:
        def addWord(word: str):
            if word not in wordId:
                nonlocal nodeNum
                wordId[word] = nodeNum
                nodeNum += 1

                idWord.append(word)
            return

        def transformCheck(word1: str, word2: str) -> bool:
            diffs = 0
            for i in range(len(word1)):
                if word1[i] != word2[i]:
                    diffs += 1
                if diffs > 1:
                    break
            return diffs == 1

        wordId = {}
        idWord = []
        edges = collections.defaultdict(list)
        nodeNum = 0

        if endWord not in wordList:
            return []

        addWord(beginWord)
        for word in wordList:
            addWord(word)

        for i in range(nodeNum):
            for j in range(i + 1, nodeNum):
                if transformCheck(idWord[i], idWord[j]):
                    edges[i].append(j)
                    edges[j].append(i)

        beginId = wordId[beginWord]
        endId = wordId[endWord]

        dis = [float('inf')] * nodeNum
        dis[beginId] = 0
        que = collections.deque([[beginWord]])
        res = []
        while que:
            routeNow = que.popleft()
            nodeNow = routeNow[-1]
            idNow = wordId[nodeNow]

            if idNow == endId:
                res.append(routeNow)

            else:
                for to in edges[idNow]:
                    if dis[to] >= dis[idNow] + 1:
                        dis[to] = dis[idNow] + 1
                        tmp = list(routeNow)
                        tmp.append(idWord[to])
                        que.append(tmp)

        return res


beginWord = "qa"
endWord = "sq"
wordList = ["si","go","se","cm","so","ph","mt","db","mb","sb","kr","ln","tm","le","av","sm","ar","ci","ca","br","ti","ba","to","ra","fa","yo","ow","sn","ya","cr","po","fe","ho","ma","re","or","rn","au","ur","rh","sr","tc","lt","lo","as","fr","nb","yb","if","pb","ge","th","pm","rb","sh","co","ga","li","ha","hz","no","bi","di","hi","qa","pi","os","uh","wm","an","me","mo","na","la","st","er","sc","ne","mn","mi","am","ex","pt","io","be","fm","ta","tb","ni","mr","pa","he","lr","sq","ye"]

print(Solution().findLadders(beginWord, endWord, wordList))
