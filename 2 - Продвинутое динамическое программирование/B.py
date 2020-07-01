# -*- coding: utf-8 -*-
import sys

line = sys.stdin.readline().strip()

n = len(line)
dp = [[None] * n for el in range(n)]
positions = [[None] * n for el in range(n)]
answer = ''

def searcher(l, r):
    global answer
    if dp[l][r] == r - l + 1:
        return
    if dp[l][r] == 0:
        answer += line[l:r + 1]
        return
    if positions[l][r] == -999:
        answer += line[l]
        searcher(l + 1, r - 1)
        answer += line[r]
        return
    searcher(l, positions[l][r])
    searcher(positions[l][r] + 1, r)


if n > 0:
    for i in range(n):
        for j in range(n):
            if j < i:
                dp[i][j] = 0
            if i == j:
                dp[i][j] = 1
    for r in range(n):
        for l in range(r, -1, -1):
            if l == r:
                dp[l][r] = 1
            else:
                minval = 999
                mink = -999
                if ((line[l] == '(') & (line[r] == ')')) | ((line[l] == '[') & (line[r] == ']')) | ((line[l] == '{') & (line[r] == '}')):
                    minval = dp[l + 1][r - 1]
                for k in range(l, r):
                    if (minval > dp[l][k] + dp[k + 1][r]):
                        minval = dp[l][k] + dp[k + 1][r]
                        mink = k
                dp[l][r] = minval
                positions[l][r] = mink
    searcher(0, n - 1)

print (answer)
