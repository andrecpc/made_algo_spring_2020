# -*- coding: utf-8 -*-

import sys

n, m = map( int, sys.stdin.readline().strip().split(' ') )
values = [0] * n
for i in range(n):
    values[i] = list( map( int, sys.stdin.readline().strip().split(' ') ) )

dp = [ [0] * m for i in range(n) ]

for i in range(n):
    for j in range(m):
        if (i == 0) and (j == 0):
            dp[0][0] = values[0][0]
        elif i == 0:
            dp[0][j] = dp[0][j - 1] + values[0][j]
        elif j == 0:
            dp[i][0] = dp[i - 1][0] + values[i][0]
        else:
            dp[i][j] = max( dp[i - 1][j], dp[i][j - 1] ) + values[i][j]

fin_coins = dp[n - 1][m - 1]

path = ''

while ((n - 1) > 0) or ((m - 1) > 0):
    if n - 1 == 0:
        path += 'R'
        m -= 1
    elif m - 1 == 0:
        path += 'D'
        n -= 1
    elif dp[n - 2][m - 1] > dp[n - 1][m - 2]:
        path += 'D'
        n -= 1
    else:
        path += 'R'
        m -= 1

print (fin_coins)
print (path[::-1])
