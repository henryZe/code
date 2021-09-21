def rabbit(month, dp):
    if month < 2:
        return 1
    r = 1
    for i in range(2, month + 1):
        r += dp[month - i]
    return r
    
while True:
    try:
        n = int(input())
        dp = [0] * (n)
        for i in range(n):
            dp[i] = rabbit(i, dp)
        print(dp[n - 1])
    except EOFError:
        break