class Solution:
    def canChange(self, start: str, target: str) -> bool:
        l = len(start)
        l_list = list(start)
        r_list = list(start)
        ret = True

        for i in range(l):
            if target[i] == 'L':
                for j in range(i, l):
                    if l_list[j] == 'R':
                        return False
                    if l_list[j] == 'L':
                        l_list[j] = '_'
                        l_list[i] = 'L'
                        break

        for i in range(l - 1, -1, -1):
            if target[i] == 'R':
                for j in range(i, -1, -1):
                    if r_list[j] == 'L':
                        return False
                    if r_list[j] == 'R':
                        r_list[j] = '_'
                        r_list[i] = 'R'
                        break

        res = ["_"] * l
        for i in range(l):
            if l_list[i] == 'L':
                res[i] = 'L'
            if r_list[i] == 'R':
                res[i] = 'R'

        return ''.join(res) == target


start = "_L__R__R_"
target = "L______RR"
# start = "R_L_"
# target = "__LR"
# start = "_R"
# target = "R_"

print(Solution().canChange(start, target))
