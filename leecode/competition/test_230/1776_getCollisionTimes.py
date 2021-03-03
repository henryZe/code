from typing import List

class Solution:
    def getCollisionTimes(self, cars: List[List[int]]) -> List[float]:
        stack = []
        size = len(cars)
        ans = [float(-1)] * size

        for i in range(size - 1, -1, -1):
            # 是否能追上上一辆车
            while stack:
                # 永远追不上上一辆车
                if cars[stack[-1]][1] >= cars[i][1]:
                    # 放弃, 改而追前一辆车
                    stack.pop()
                
                # 总能追上
                else:
                    # 它不会消失, 总能追上
                    if ans[stack[-1]] < 0:
                        break
                    # 前辆车消失之前, 能不能追上
                    dist = cars[stack[-1]][0] - cars[i][0]
                    chase = ans[stack[-1]] * (cars[i][1] - cars[stack[-1]][1])
                    # 如果追不上
                    if dist > chase:
                        # 追不上, 继续追前一辆车
                        stack.pop()
                    else:
                        # 追上了
                        break

            if not stack:
                ans[i] = float(-1)
            else:
                dist = cars[stack[-1]][0] - cars[i][0]
                speed = cars[i][1] - cars[stack[-1]][1]
                ans[i] = dist / speed

            stack.append(i)

        return ans

# cars = [[1,2], [2,1], [4,3], [7,2]]
# ref = [1.00000,-1.00000,3.00000,-1.00000]

# cars = [[3,4], [5,4], [6,3], [9,1]]
# ref = [2.00000,1.00000,1.50000,-1.00000]

cars = [[3,1],[9,4],[19,4]]

print(Solution().getCollisionTimes(cars))
# print(ref)
