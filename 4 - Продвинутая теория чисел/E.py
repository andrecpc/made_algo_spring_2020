# -*- coding: utf-8 -*-
import sys
from random import randint
import random
#import time

n = int(sys.stdin.readline().strip())

def gcd(a, b):
    while b > 0:
        a, b = b, a % b
    return a

def f(x, c, m):
    return (x ** 2) * c + m

def miller_rabin(n):
    if n in [0, 1, 4, 6, 8, 9]:
        return False
    if n in [2, 3, 5, 7]:
        return True
    s = 0
    d = n - 1
    while d % 2 == 0:
        d >>= 1
        s += 1
    def check(a):
        if pow(a, d, n) == 1:
            return False
        for i in range(s):
            if pow(a, 2 ** i * d, n) == n - 1:
                return False
        return True
    for i in range(3):
        a = random.randrange(2, n)
        if check(a):
            return False
    return True

def search_fac(n):
    maxiterssq = 0.5 * n
    x = randint(1, n-1)
    y = x
    d = 1
    iters = 0
    c = randint(1, n-1)
    m = randint(1, n-1)
    while d == 1 or d == n:
        if iters ** 2 > maxiterssq:
            c = randint(1, n-1)
            m = randint(1, n-1)
            x = randint(1, n-1)
            y = x
            iters = 0
        x = f(x, c, m) % n
        y = f(f(y, c, m), c, m) % n
        d = gcd(abs(x - y), n)
        iters += 1
    return d

def search_prime_fac(n, factors):
    if miller_rabin(n):
        factors.append(n)
    else:
        temp = n // search_fac(n)
        search_prime_fac(temp, factors)

def factor(n, factors):
    while n % 2 == 0:
        factors.append(2)
        n //= 2
    while n % 3 == 0:
        factors.append(3)
        n //= 3
    while n > 1:
        search_prime_fac(n, factors)
        n //= factors[-1]

#n = 1000000000000000000001
#s = time.time()
factors = []
factor(n, factors)
factors.sort()
print(' '.join(map(str, factors)))

#print (time.time()-s)
