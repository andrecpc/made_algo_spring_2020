# -*- coding: utf-8 -*-
import sys

n = int(sys.stdin.readline().strip())
a = [0] * n
for i in range(n):
    a[i] = sys.stdin.readline().strip()



dp = [0] * (1 << n)

n2 = 1 << n
for i in range(n2):
    for j in range(n):
        if (i & 1 << j):
            for k in range(j + 1, n):
                if (i & 1 << k):
                    if (a[j][k] == 'Y'):
                        dp[i]=max(dp[i], 2 + dp[i &~ (1 << j) &~ (1 << k)])
print (dp[n2 - 1])
