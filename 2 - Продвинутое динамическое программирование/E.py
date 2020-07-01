n, m = map(int, input().split())
board = []
dp = []

for _ in range(n):
    board.append(input() + 'X')

for _ in range(n * m + 1):
    dp.append([0] * (1 << n))

dp[0][0] = 1

for i in range(n * m):
    row_id, col_id = i % n, i // n
    for mask in range(len(dp[0])):
        cell = board[row_id][col_id]
        if (cell == 'X' and mask & 1 == 0) or (cell == '.' and mask & 1 == 1):
            next_mask = mask >> 1
            dp[i + 1][next_mask] += dp[i][mask]

        if cell == '.' and mask & 1 == 0:
            if board[row_id][col_id + 1] == '.':
                next_mask = (mask >> 1) + (1 << (n - 1))
                dp[i + 1][next_mask] += dp[i][mask]

            if mask & 2 == 0 and row_id + 1 < n and board[row_id + 1][col_id] == '.':
                next_mask = (mask >> 1) + 1
                dp[i + 1][next_mask] += dp[i][mask]

print(dp[-1][0])
