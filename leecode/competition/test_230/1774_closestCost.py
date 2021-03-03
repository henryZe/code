from typing import List

class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        can = [False] * (20000 + 1)

        for base in baseCosts:
            can[base] = True

        for _ in range(2):
            for top in toppingCosts:
                for i in range(20000, top, -1):
                    can[i] = can[i] or can[i - top]

        ans = baseCosts[0]
        abs_ans = abs(baseCosts[0] - target)
        for i in range(20000 + 1):
            if can[i] and abs(i - target) < abs_ans:
                ans = i
                abs_ans = abs(i - target)

        return ans


# baseCosts = [1,7]
# toppingCosts = [3,4]
# target = 10

# baseCosts = [2,3]
# toppingCosts = [4,5,100]
# target = 18

# baseCosts = [3,10]
# toppingCosts = [2,5]
# target = 9

baseCosts = [10]
toppingCosts = [1]
target = 1
print(Solution().closestCost(baseCosts, toppingCosts, target))
