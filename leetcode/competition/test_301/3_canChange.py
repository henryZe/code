class Solution:
    def canChange(self, start: str, target: str) -> bool:
        l = len(start)
        l_pos = r_pos = 0

        for i in range(l):
            if target[i] == 'L':
                l_start = l_pos
                for j in range(l_start, l):
                    if start[j] == 'L':
                        l_pos = j + 1
                    elif start[j] == 'R':
                        break
        return True


start = "_L__R__R_"
target = "L______RR"
# start = "R_L_"
# target = "__LR"
# start = "_R"
# target = "R_"

print(Solution().canChange(start, target))
