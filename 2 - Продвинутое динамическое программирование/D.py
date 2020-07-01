# -*- coding: utf-8 -*
import sys

n = int(sys.stdin.readline().strip())
a = [0] * n
for i in range(n):
    a[i] = list(map(int, sys.stdin.readline().strip().split(' ')))

inf = 100000001
finish_mask = 1 << n
dp = [[inf] * (n) for i in range(finish_mask)]
path = [[0] * (n) for i in range(finish_mask)]

k = 1
for i in range(1, n + 1):
    k *= 2
ans = inf

for i in range(n):
    dp[1 << i][i] = 0

for i in range(k):
    for j in range(n):
        m = inf
        for l in range(n):
            if l != j:
                if (dp[(i ^ (1 << j))][l] + a[l][j]) < m:
                    m = dp[i ^ (1 << j)][l] + a[l][j]
                    dp[i][j] = m
                    path[i][j] = l

for i in range(n):
    if dp[k - 1][i] < ans:
        ans = dp[k - 1][i]
        last = i

print (ans)

mask = k - 1
res = ''

for i in range(n):
    res += str(last + 1) + ' '
    pr, last = last, path[mask][last]
    mask = mask ^ (1 << pr)

res = res[:-1].split(' ')
print (' '.join(res[::-1]) + ' ')
