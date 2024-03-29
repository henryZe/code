class Solution:
    def topKstrings(self, strings, k):
        str_dict = {}
        for s in strings:
            if s not in str_dict:
                str_dict[s] = 1
            else:
                str_dict[s] += 1

        str_set = list(set(strings))
        # sorted by alphabets
        str_set.sort()
        n_set = len(str_set)
        str_index = list(range(n_set))

        def compare(x):
            return str_dict[str_set[x]]
        # sorted by times of appearance
        str_index.sort(key=compare, reverse=True)

        ret = []
        for i in str_index[:k]:
            ret.append([str_set[i], str(str_dict[str_set[i]])])

        return ret

# strings = ["a","b","c","b"]
# k = 2
# strings = ["123","123","231","32"]
# k = 2
strings = ["abcd","abcd","abcd","pwb2","abcd","pwb2","p12"]
k = 3
print(Solution().topKstrings(strings, k))
