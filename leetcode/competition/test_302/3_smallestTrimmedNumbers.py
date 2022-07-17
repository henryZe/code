from typing import List

def compare(num_pair):
    return num_pair[0]

class Solution:
    def smallestTrimmedNumbers(self, nums: List[str], queries: List[List[int]]) -> List[int]:
        answer = []
        for q in queries:
            bit = q[1]
            seq = q[0]
            num_int = []

            for i, num in enumerate(nums):
                num_pair = [int(num[-bit:]), i]
                num_int.append(num_pair)

            # print(num_int)
            num_int.sort(key=compare)
            # print(num_int)
            answer.append(num_int[seq - 1][1])
            # print(num_int[seq - 1][1])

        return answer


# nums = ["102","473","251","814"]
# queries = [[1,1],[2,3],[4,2],[1,2]]
nums = ["24","37","96","04"]
queries = [[2,1],[2,2]]
print(Solution().smallestTrimmedNumbers(nums, queries))
