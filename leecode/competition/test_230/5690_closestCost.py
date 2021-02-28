from typing import List

class Solution:
    def closestCost(self, baseCosts: List[int], toppingCosts: List[int], target: int) -> int:
        m = len(baseCosts)
        n = len(topping)

        baseCosts.sort()
        toppingCosts.sort()

        def compare(price):
            if price >= target:
                nonlocal finish
                finish = 1
            return price

        finish = 0
        best = 
        for i in range(m):
            price = compare(baseCosts[i])
            if finish:
                best 

            for j in range(n):
                price += toppingCosts[j]
                if price > target:
                    best = price



        return best


# baseCosts = [1,7]
# toppingCosts = [3,4]

# target = 10

baseCosts = [2,3]
toppingCosts = [4,5,100]
target = 18

# baseCosts = [3,10]
# toppingCosts = [2,5]
# target = 9

# baseCosts = [10]
# toppingCosts = [1]
# target = 1
print(Solution().closestCost(baseCosts, toppingCosts, target))
