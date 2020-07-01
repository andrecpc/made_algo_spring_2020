from math import sqrt
import sys

def prime(n):
    if n == 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    while(i * i <= n):
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i = i + 6
    return True

def power(x, y, p):
    res = 1
    x = x % p
    while y > 0:
        if y & 1:
            res = (res * x) % p
        y = y >> 1
        x = (x * x) % p
    return res

def find_prime_factors(s, n):
    while n % 2 == 0:
        s.add(2)
        n = n // 2
    for i in range(3, int(sqrt(n)), 2):
        while n % i == 0:
            s.add(i)
            n = n // i
    if n > 2:
        s.add(n)


def find_prim_root(n):
    s = set()
    if prime(n) == False:
        return -1
    phi = n - 1
    find_prime_factors(s, phi)
    for r in range(2, phi + 1):
        flag = False
        for it in s:
            if power(r, phi // it, n) == 1:
                flag = True
                break
        if flag == False:
            return r
    return -1

p = int(sys.stdin.readline().strip())
#p = 2393
print(find_prim_root(p))
