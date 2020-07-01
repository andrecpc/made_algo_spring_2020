# -*- coding: utf-8 -*-
import random
import sys

n = int(sys.stdin.readline().strip())

def miller_rabin(n):

    if n in [0, 1, 4, 6, 8, 9]:
        return 'NO'

    if n in [2, 3, 5, 7]:
        return 'YES'
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
                return 'NO'
        return 'YES'

    for i in range(3):
        a = random.randrange(2, n)
        if check(a) == 'YES':
            return 'NO'

    return 'YES'

for _ in range(n):
    i = int(sys.stdin.readline().strip())
    print (miller_rabin(i))
