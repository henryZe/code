n, m = map(int, input().split())

primary = {}
annex = {}
for i in range(1, m + 1):
    v, p, q = map(int, input().split())
    if q == 0:
        primary[i] = [v, p]
    else:
        if q in annex:
            annex[q].append([v, p])
        else:
            annex[q] = [[v, p]]

# print("primary", primary)
# print("annex", annex)

primary_m = len(primary)
dp = []
for _ in range(primary_m + 1):
    dp.append([0] * (n + 1))

w, v = [[]], [[]]
for key in primary:
    w_temp, v_temp = [], []
    w_temp.append(primary[key][0])
    v_temp.append(primary[key][0] * primary[key][1])

    if key in annex:
        w_temp.append(w_temp[0] + annex[key][0][0])
        v_temp.append(v_temp[0] + annex[key][0][0] * annex[key][0][1])
        if len(annex[key]) > 1:
            w_temp.append(w_temp[0] + annex[key][1][0])
            v_temp.append(v_temp[0] + annex[key][1][0] * annex[key][1][1])
            w_temp.append(w_temp[1] + annex[key][1][0])
            v_temp.append(v_temp[1] + annex[key][1][0] * annex[key][1][1])

    w.append(w_temp)
    v.append(v_temp)

# print("w", w)
# print("v", v)

for i in range(1, primary_m + 1):
    for j in range(10, n + 1, 10):
        max_v = dp[i - 1][j]

        n_k = len(w[i])
        for k in range(n_k):
            if j - w[i][k] >= 0:
                max_v = max(max_v, dp[i - 1][j - w[i][k]] + v[i][k])
        dp[i][j] = max_v

print(dp[primary_m][n])
