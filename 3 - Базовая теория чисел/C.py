# -*- coding: utf-8 -*-

import sys

n = int(sys.stdin.readline().strip())
e = int(sys.stdin.readline().strip())
c = int(sys.stdin.readline().strip())

#n, e, c = 143, 113, 41
#n, e, c = 9173503, 3, 4051753

def euler(n):
    result = n
    i = 2
    while i * i <= n:
        if n % i == 0:
            while n % i == 0:
                n /= i
            result -= result / i
        i += 1
    if n > 1:
        result -= result / n
    return int(result)

def binpow(a, n, mod):
    if n == 0:
        return 1
    if int(n) & 1:
        return (a * binpow(a, n - 1, mod)) % mod
    return binpow((a * a) % mod, n / 2, mod)

p = euler(n)
pp = euler(p)
d = binpow(e, pp - 1, p)
print (binpow(c, d, n))
