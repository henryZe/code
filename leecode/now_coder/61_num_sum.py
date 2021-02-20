class Solution:
    def twoSum(self , numbers , target ):
        pair = {}
        for i in range(len(numbers)):
            if numbers[i] not in pair:
                residue = target - numbers[i]
                pair[residue] = i
            else:
                j = pair[numbers[i]]
                return [j + 1, i + 1]
