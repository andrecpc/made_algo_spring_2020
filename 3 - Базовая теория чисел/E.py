# -*- coding: utf-8 -*-
import sys

n = int(sys.stdin.readline().strip())

for i in range(n):
    a, b, n, m = list(map(int, sys.stdin.readline().strip().split(' ')))

#a, b, n, m = 3, 2, 5, 9
#a,b,n,m = 1, 0, 2, 3

    def gcd(a, b):
        global x
        global y
        if b == 0:
            x = 1
            y = 0
            return a
        g = gcd(b, a % b)
        tmp = y
        y = x - int(a / b) * y
        x = tmp
        return int(g)

    A = n
    B = m
    G = b - a
    x, y = 0, 0
    mod = n * m
    g = gcd(A, B)
    x *= A
    x %= mod
    x += mod
    x %= mod
    x *= G
    x %= mod
    x += mod
    x %= mod
    x += a
    x %= mod
    x += mod
    x %= mod
    print (x)
