
class Solution:
    def combinationSum2(self, num, target):
        n_num = len(num)
        index_list = list(range(n_num))
        def get_num(x):
            return num[x]
        index_list.sort(key=get_num)

        def dfs(res, cur, sel: int):
            if sum(cur) == target:
                temp = cur[:]
                res.append(temp)
                return

            i = sel
            while i < len(index_list):
                if num[index_list[i]] == -1:
                    continue
                
                if (num[index_list[i]] + sum(cur)) <= target:
                    cur.append(num[index_list[i]])
                    num[index_list[i]] = -1
                    dfs(res, cur, i + 1)
                    num[index_list[i]] = cur.pop()
                else:
                    break

                while i < (len(index_list) - 1) and num[index_list[i]] == num[index_list[i + 1]]:
                    i += 1
                i += 1

            return

        res = []
        cur = []
        dfs(res, cur, 0)
        return res

num = [100,10,20,70,60,10,50]
target = 80
print(Solution().combinationSum2(num, target))