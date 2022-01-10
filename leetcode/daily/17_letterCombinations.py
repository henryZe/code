from typing import List

class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        digit_dict = {}
        digit_dict["2"] = "abc"
        digit_dict["3"] = "def"
        digit_dict["4"] = "ghi"
        digit_dict["5"] = "jkl"
        digit_dict["6"] = "mno"
        digit_dict["7"] = "pqrs"
        digit_dict["8"] = "tuv"
        digit_dict["9"] = "wxyz"
        res = []

        def backtrack(cur_str: list, pos: int):
            if pos == len(digits):
                if cur_str:
                    res.append("".join(cur_str))
                    # print("res:", res)
                return

            for letter in digit_dict[digits[pos]]:
                cur_str.append(letter)
                # print("cur_str:", cur_str)
                backtrack(cur_str, pos + 1)
                cur_str.pop()

        cur_str = []
        backtrack(cur_str, 0)
        return res

digits = "23"
digits = ""
digits = "2"
print(Solution().letterCombinations(digits))