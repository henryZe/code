from typing import List
from collections import defaultdict
from sortedcontainers import SortedSet

class FoodRatings:
    def __init__(self, foods: List[str], cuisines: List[str], ratings: List[int]):
        self.food_hash = {}
        # hash + AVL-tree or rb-tree
        self.cuisine_hash = defaultdict(SortedSet)

        for i, food in enumerate(foods):
            self.food_hash[food] = [cuisines[i], ratings[i]]
            self.cuisine_hash[cuisines[i]].add((-ratings[i], food))

        return

    def changeRating(self, food: str, newRating: int) -> None:
        cuisine, rating = self.food_hash[food]
        # O(logN)
        self.cuisine_hash[cuisine].remove((-rating, food))
        # O(logN)
        self.cuisine_hash[cuisine].add((-newRating, food))
        self.food_hash[food][1] = newRating

    def highestRated(self, cuisine: str) -> str:
        # O(logN)
        # find rb_first node
        return self.cuisine_hash[cuisine][0][1]


obj = FoodRatings(["kimchi", "miso", "sushi", "moussaka", "ramen", "bulgogi"], ["korean", "japanese", "japanese", "greek", "japanese", "korean"], [9, 12, 8, 15, 14, 7])
print(obj.highestRated("korean"))
print(obj.highestRated("japanese"))
obj.changeRating("sushi", 16)
print(obj.highestRated("japanese"))
obj.changeRating("ramen", 16)
print(obj.highestRated("japanese"))
