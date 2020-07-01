# -*- coding: utf-8 -*-
import sys

a, b, m = list(map(int, (sys.stdin.readline().strip().split(' '))))

def dlog(a, b, m):

    k = int(m ** 0.5 + 1)
    baby_steps = {}
    baby_step = 1

    for r in range(k + 1):
        baby_steps[baby_step] = r
        baby_step = baby_step * a % m

    g = pow(a, (m - 2) * k, m)
    giant_step = b

    for s in range(k + 1):
        if giant_step in baby_steps:
            return s * k + baby_steps[giant_step]
        else:
            giant_step = giant_step * g % m

    return -1

print(dlog(a, b, m))
