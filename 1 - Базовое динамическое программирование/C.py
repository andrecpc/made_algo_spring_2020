# -*- coding: utf-8 -*-

# n = 5
# a = [1, 3, 5, 4, 2]

import sys

n = int(sys.stdin.readline().strip())
a = list( map( int, sys.stdin.readline().strip().split(' ') ) )
out = []

dp = [0] * n
for i in range(n):
    for j in range(i):
        if a[i] > a[j] and dp[j] > dp[i]:
            dp[i] = dp[j]
    dp[i] += 1

ind = dp.index(max(dp))
out.append(a[ind])

while dp[ind] != 1:
    j = ind - 1
    while (dp[j] != dp[ind] - 1) or (a[j] >= a[ind]):
        j -= 1
    ind = j
    out.append(a[ind])

print (len(out))
print (' '.join(map( str, out[::-1]) ))
