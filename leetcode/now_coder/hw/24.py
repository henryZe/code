def lengthofLIS(heights):
    n = len(heights)
    dp = [1] * n
    for i in range(1, n):
        for j in range(i - 1, -1, -1):
            if heights[i] > heights[j]:
                dp[i] = max(dp[i], dp[j] + 1)

    return dp

while True:
    try:
        num = int(input())
        heights = list(map(int, input().split()))

        left = lengthofLIS(heights)
        right = lengthofLIS(heights[::-1])[::-1]
        # print(left)
        # print(right)

        max_len = 0
        for i in range(num):
            max_len = max(max_len, left[i] + right[i] - 1)
        print(num - max_len)

    except EOFError:
        break