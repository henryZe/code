from typing import List

class Solution:
    def countMatches(self, items: List[List[str]], ruleKey: str, ruleValue: str) -> int:
        dict_key = {}
        type_name = ["type", "color", "name"]
        for i in range(3):
            dict_key[type_name[i]] = i
        
        res = 0
        for item in items:
            if item[dict_key[ruleKey]] == ruleValue:
                res += 1

        return res


# items = [["phone","blue","pixel"],["computer","silver","lenovo"],["phone","gold","iphone"]]
# ruleKey = "color"
# ruleValue = "silver"

items = [["phone","blue","pixel"],["computer","silver","phone"],["phone","gold","iphone"]]
ruleKey = "type"
ruleValue = "phone"

print(Solution().countMatches(items, ruleKey, ruleValue))
