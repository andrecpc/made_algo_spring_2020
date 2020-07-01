# -*- coding: utf-8 -*-
import sys

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.o = (x, y)
    def minus(self, p):
        x = self.x - p.x
        y = self.y - p.y
        return Point(x, y)
    def plus(self, p):
        x = self.x + p.x
        y = self.y + p.y
        return Point(x, y)
    def __str__(self):
         return str(format(self.x, '.10f')) + ' ' + str(format(self.y, '.10f'))

class Circle:
    def __init__(self, x, y, r):
        self.p = Point(x, y)
        self.r = r

class Line:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c

if __name__ == "__main__":

    n = int(sys.stdin.readline().strip())

    for _ in range(n):

        x1, y1, r1 = list(map(int, sys.stdin.readline().strip().split(' ')))
        x2, y2, r2 = list(map(int, sys.stdin.readline().strip().split(' ')))

        c1, c2 = Circle(x1, y1, r1), Circle(x2, y2, r2)

        if (c1.p.o == c2.p.o):
            if (c1.r == c2.r):
                print("3")
                continue
            else:
                print("0")
                continue

        o1 = c1.p
        o2 = c2.p
        o2 = o2.minus(o1)
        line = Line(-2 * o2.x, -2 * o2.y, (o2.x) ** 2 + (o2.y) ** 2 - (c2.r) ** 2 + (c1.r) ** 2)

        a_kv_b_kv = (line.a) ** 2 + (line.b) ** 2
        c_kv = (line.c) ** 2
        r_kv = (c1.r) ** 2
        r_kv_a_kv_b_kv = r_kv * a_kv_b_kv

        if (c_kv > r_kv_a_kv_b_kv):
            print ("0")
            continue

        h = Point(-1 * line.a * line.c / a_kv_b_kv, -1 * line.b * line.c / a_kv_b_kv)

        if (c_kv == r_kv_a_kv_b_kv):
            print("1")
            print(h.plus(o1))
            continue

        c_kv_a_kv_b_kv = c_kv / a_kv_b_kv
        len_hp_kv = r_kv - c_kv_a_kv_b_kv
        oh = (c_kv_a_kv_b_kv) ** 0.5
        len_hp = (len_hp_kv) ** 0.5
        mult = (len_hp_kv / a_kv_b_kv) ** 0.5
        hp = Point(line.b * mult, -line.a * mult)
        p1 = h.plus(hp)
        p2 = h.minus(hp)

        print("2")
        print(h.plus(o1))
        print(str(format(oh, '.10f')) + " " + str(format(len_hp, '.10f')))
        print(p1.plus(o1))
        print(p2.plus(o1))
