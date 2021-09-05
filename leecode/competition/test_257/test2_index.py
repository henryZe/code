from typing import List

class Solution:
    def numberOfWeakCharacters(self, properties: List[List[int]]) -> int:
        n = len(properties)

        def takeAttack(member):
            return member[0]

        temp = properties
        temp.sort(key=takeAttack)
        # print(temp)

        count = 0
        for i in range(0, n):
            for j in range(n - 1, i, -1):
                if temp[i][0] < temp[j][0]:
                    if temp[i][1] < temp[j][1]:
                        count += 1
                        break

        return count

nums = [
    # [[5,5],[6,3],[3,6]],
    # [[2,2],[3,3]],
    # [[1,5],[10,4],[4,3]],
    [[7,7],[1,2],[9,7],[7,3],[3,10],[9,8],[8,10],[4,3],[1,5],[1,5]],
]
for i in nums:
    print(Solution().numberOfWeakCharacters(i))
