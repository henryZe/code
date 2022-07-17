class Solution:
    def canChange(self, start: str, target: str) -> bool:
        s = start.replace("_", "")
        t = target.replace("_", "")
        if s != t:
            return False

        j = 0
        for i, c in enumerate(start):
            if c == '_':
                continue
            while target[j] == '_':
                j += 1

            if c == 'L':
                # target[j] must be 'L' too
                if j > i:
                    # 'L' can only be moved to left side
                    return False
            elif c == 'R':
                if j < i:
                    return False
            j += 1

        return True


# start = "_L__R__R_"
# target = "L______RR"
# start = "R_L_"
# target = "__LR"
start = "_R"
target = "R_"

print(Solution().canChange(start, target))
