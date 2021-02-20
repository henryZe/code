class Solution:
    def maxLength(self , arr ):
        cur_arr = []
        maxlength = 0

        for a in arr:
            if a in cur_arr:
                maxlength = max(maxlength, len(cur_arr))
                start = cur_arr.index(a)
                cur_arr = cur_arr[start + 1:]
            cur_arr.append(a)

        return max(len(cur_arr), maxlength)


print(Solution().maxLength([2,3,4,5]))
