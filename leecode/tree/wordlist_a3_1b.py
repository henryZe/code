from typing import List
import collections

class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        def addWord(word: str):
            if word not in wordId:
                nonlocal nodeNum
                print("wordId[{}] = {}".format(word, nodeNum))
                wordId[word] = nodeNum
                nodeNum += 1

        def addEdge(word: str):
            addWord(word)
            # original word id
            id1 = wordId[word]
            chars = list(word)
            for c in range(len(chars)):
                tmp = chars[c]
                chars[c] = '*'
                newWord = "".join(chars)
                addWord(newWord)
                # '*' word id
                id2 = wordId[newWord]
                edge[id1].append(id2)
                edge[id2].append(id1)
                chars[c] = tmp

        wordId = {}
        edge = collections.defaultdict(list)
        nodeNum = 0

        if endWord not in wordList:
            return 0

        addEdge(beginWord)
        for word in wordList:
            addEdge(word)

        beginId = wordId[beginWord]
        endId = wordId[endWord]

        dis = [float('inf')] * nodeNum
        dis[beginId] = 0
        que = collections.deque([beginId])
        while que:
            itemId = que.popleft()
            if itemId == endId:
                print(dis)
                return dis[itemId] // 2 + 1
            else:
                for i in edge[itemId]:
                    if dis[i] == float('inf'):
                        dis[i] = dis[itemId] + 1
                        print("dis[{}] = {}".format(i, dis[i]))
                        que.append(i)

        return 0

beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]

print(Solution().ladderLength(beginWord, endWord, wordList))
