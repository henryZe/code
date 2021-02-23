from typing import List
import collections

# double direct bfs
class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        def addWord(word: str):
            if word not in wordId:
                nonlocal nodeNum
                wordId[word] = nodeNum
                nodeNum += 1

        def addEdge(word: str):
            addWord(word)
            originId = wordId[word]
            chars = list(word)
            for i in range(len(word)):
                tmp = chars[i]
                chars[i] = '*'
                newWord = "".join(chars)
                addWord(newWord)
                varId = wordId[newWord]
                edge[originId].append(varId)
                edge[varId].append(originId)
                chars[i] = tmp

        wordId = {}
        nodeNum = 0
        edge = collections.defaultdict(list)

        if endWord not in wordList:
            return 0

        addEdge(beginWord)
        for w in wordList:
            addEdge(w)
        print(edge)

        beginId = wordId[beginWord]
        endId = wordId[endWord]
        beginQue = collections.deque([beginId])
        endQue = collections.deque([endId])

        disBegin = [float("inf")] * nodeNum
        disEnd = [float("inf")] * nodeNum
        disBegin[beginId] = 0
        disEnd[endId] = 0

        while beginQue or endQue:
            queSize = len(beginQue)
            for _ in range(queSize):
                node = beginQue.popleft()
                if disEnd[node] != float("inf"):
                    return (disBegin[node] + disEnd[node]) // 2 + 1
                for var in edge[node]:
                    if disBegin[var] == float("inf"):
                        disBegin[var] = disBegin[node] + 1
                        beginQue.append(var)

            queSize = len(endQue)
            for _ in range(queSize):
                node = endQue.popleft()
                if disBegin[node] != float("inf"):
                    return (disBegin[node] + disEnd[node]) // 2 + 1
                for var in edge[node]:
                    if disEnd[var] == float("inf"):
                        disEnd[var] = disEnd[node] + 1
                        endQue.append(var)

        return 0

beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]

print(Solution().ladderLength(beginWord, endWord, wordList))
