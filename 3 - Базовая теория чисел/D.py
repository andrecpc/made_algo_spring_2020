# -*- coding: utf-8 -*-
import sys

a, b, c = list(map(int, sys.stdin.readline().strip().split(' ')))

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def gcd_2(a, b):
    x, xx, y, yy = 1, 0, 0, 1
    while b:
        q = a // b
        a, b = b, a % b
        x, xx = xx, x - xx*q
        y, yy = yy, y - yy*q
    return x, y

u, v = gcd_2(a, b)
x = u * (c // gcd(a, b))
y = v * (c // gcd(a, b))

if x * a + y * b + c == 0:
    print (x, y)
elif -x * a + y * b + c == 0:
    print (-x, y)
elif x * a - y * b + c == 0:
    print (x, -y)
elif -x * a - y * b + c == 0:
    print (-x, -y)
elif y * a + x * b + c == 0:
    print (y, x)
elif -y * a + x * b + c == 0:
    print (-y, x)
elif y * a - x * b + c == 0:
    print (y, -x)
elif -y * a - x * b + c == 0:
    print (-y, -x)
else:
    print (-1)
