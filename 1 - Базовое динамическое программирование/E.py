INF = 300000

n = int(input())
prices = []
dp = []

for _ in range(n):
    prices.append(int(input()))

for _ in range(n + 1):
    dp.append([INF] * (n + 2))

dp[0][0] = 0
rows, cols = len(dp), len(dp[0]) - 1

for row_id in range(1, rows):
    price = prices[row_id - 1]
    for col_id in range(cols):
        if price > 100:
            min_price = min(
                INF if col_id == 0 else dp[row_id - 1][col_id - 1] + price,
                dp[row_id - 1][col_id + 1],
            )
        else:
            min_price = min(
                dp[row_id - 1][col_id] + price,
                dp[row_id - 1][col_id + 1],
            )
        dp[row_id][col_id] = min_price

min_price_id = 0
min_price_val = dp[-1][min_price_id]

for col_id, val in enumerate(dp[-1]):
    if val <= min_price_val:
        min_price_val = val
        min_price_id = col_id

days = []
next_sum, col_id = min_price_val, min_price_id

for row_id in range(rows - 2, 0, -1):
    if dp[row_id][col_id + 1] == next_sum:
        days.append(row_id + 1)
        col_id += 1
    else:
        launch_price = prices[row_id]
        if next_sum == dp[row_id][col_id] + launch_price and launch_price <= 100:
            pass
        else:
            col_id -= 1
        next_sum -= launch_price

days = list(reversed(days))

print(min_price_val)
print(min_price_id, len(days))
print(*days)
