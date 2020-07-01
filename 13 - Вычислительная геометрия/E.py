# -*- coding: utf-8 -*-
import sys
from random import shuffle

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.o = (x, y)
    def dot(self, p):
        return self.x * p.y - self.y * p.x
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

class Line:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c
    def get_intersection(self, l):
        d = self.a * l.b - self.b * l.a
        x = (self.b * l.c - self.c * l.b) / d
        y = (self.c * l.a - self.a * l.c) / d
        return Point(x, y)

class Circle:
    def __init__(self, p1 = None, p2 = None, p3 = None, x = 0, y = 0, r = 0):
        if (p1 != None) and (p2 != None) and (p3 == None):
            self.p1 = p1
            self.p2 = p2
            self.p = Point((p2.x - p1.x) / 2, (p2.y - p1.y) / 2).plus(p1)
            self.x = self.p.x
            self.y = self.p.y
            self.r_kv = self.p.minus(p1).x ** 2 + self.p.minus(p1).y ** 2
            self.r = self.r_kv ** 0.5
        elif (p1 != None) and (p2 != None) and (p3 != None):
            self.p1 = p1
            self.p2 = p2
            self.p3 = p3
            self.line1 = self.perp_bisect(p1, p2)
            self.line2 = self.perp_bisect(p1, p3)
            self.p = self.line1.get_intersection(self.line2)
            self.x = self.p.x
            self.y = self.p.y
            self.r_kv = self.p.minus(p1).x ** 2 + self.p.minus(p1).y ** 2
            self.r = self.r_kv ** 0.5
        else:
            self.p = Point(x, y)
            self.r = r
            self.x = x
            self.y = y
            self.r_kv = r ** 2

    def include(self, p):
        help_p = Point(p.x - self.x, p.y - self.y)
        return self.r_kv > help_p.x ** 2 + help_p.y ** 2

    def perp_bisect(self, p1, p2):
        a = p1.x - p2.x
        b = p1.y - p2.y
        tmp = p2.minus(p1)
        h = p1.plus(Point(tmp.x / 2, tmp.y / 2))
        c = -a * h.x - b * h.y
        return Line(a, b, c)

def circ_by_three_points(points, i_, j_):
    circ = Circle(points[i_], points[j_])
    for i in range(i_):
        if not circ.include(points[i]):
            circ = Circle(points[i], points[i_], points[j_])
    return circ

def circ_by_two_points(points, j):
    d = points[0:j]
    shuffle(d)
    points[0:j] = d
    circ = Circle(points[0], points[j])

    for i in range(1, j):
        if not circ.include(points[i]):
            circ = circ_by_three_points(points, i, j)
    return circ

if __name__ == "__main__":

    n = int(sys.stdin.readline().strip())
    points = []

    for _ in range(n):
        x, y = list(map(int, sys.stdin.readline().strip().split(' ')))
        points.append(Point(x, y))

    shuffle(points)
    circ = Circle(points[0], points[1])

    for i in range(2, len(points)):
        if not circ.include(points[i]):
            circ = circ_by_two_points(points, i)

    print(str(format(circ.x, '.20f')) + ' ' + str(format(circ.y, '.20f')))
    print(format(circ.r, '.20f'))
