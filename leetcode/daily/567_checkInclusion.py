from typing import Counter

class Solution:
    def checkInclusion(self, s1: str, s2: str) -> bool:
        ref_dict = Counter(s1)
        temp = {}
        left = 0
        n1 = len(s1)
        n2 = len(s2)
        for right in range(n2):
            if s2[right] not in ref_dict:
                left = right + 1
                temp = {}
                continue

            if right - left + 1 > n1:
                temp[s2[left]] -= 1
                left += 1

            if s2[right] in temp:
                temp[s2[right]] += 1
            else:
                temp[s2[right]] = 1

            # print(temp)
            if temp[s2[right]] == ref_dict[s2[right]]:
                res = True
                for key in ref_dict:
                    if key not in temp or temp[key] != ref_dict[key]:
                        res = False
                        break
                if res == True:
                    return True

        return False

# s1 = "ab"
# s2 = "eidbaooo"
# s1 = "ab"
# s2 = "eidboaoo"
s1 = "adc"
s2 = "dcda"
print(Solution().checkInclusion(s1, s2))
