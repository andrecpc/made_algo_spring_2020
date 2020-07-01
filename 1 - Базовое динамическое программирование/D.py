# -*- coding: utf-8 -*-

import sys

word_1 = sys.stdin.readline().strip()
word_2 = sys.stdin.readline().strip()

# word_1 = 'ABCDEFGH'
# word_2 = 'ACDEXGIH'

a = len(word_1) + 1
b = len(word_2) + 1

dp = [ [0] * b for i in range(a) ]
dp[0][1:] = range(1, b)
for el in range(1, a):
    dp[el][0] = el

for i in range(1, a):
    for j in range(1, b):
        if word_1[i - 1] == word_2[j - 1]:
            dp[i][j] = dp[i - 1][j - 1]
        else:
            dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1])

print (dp[a-1][b-1])
