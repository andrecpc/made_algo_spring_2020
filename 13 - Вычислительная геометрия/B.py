# -*- coding: utf-8 -*-
import sys

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.o = (x, y)
    def dot(self, p):
        return self.x * p.y - self.y * p.x

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

class HalfPlane(Line):
    def __init__(self, a, b, c):
        super().__init__(a, b, c)
    def has_point(self, p):
        return self.a * p.x + self.b * p.y +self.c >= 0

class Poly:
    def __init__(self):
        self.max_cell = 20000
        self.points = [[-self.max_cell, -self.max_cell],
                       [+self.max_cell, -self.max_cell],
                       [+self.max_cell, +self.max_cell],
                       [-self.max_cell, +self.max_cell]]
        self.lines =  [[0, 1, self.max_cell],
                       [-1, 0, self.max_cell],
                       [0, -1, self.max_cell],
                       [1, 0, self.max_cell]]

    def area(self):
        a = Point(self.points[0][0], self.points[0][1])
        area = 0

        for i in range(1, len(self.points) - 1):
            b = Point(self.points[i][0], self.points[i][1])
            c = Point(self.points[i + 1][0], self.points[i + 1][1])
            area += Point(b.x - a.x, b.y - a.y).dot(Point(c.x - a.x, c.y - a.y))

        area *= 0.5
        return area

    def intersec(self, hp):
        new_points = []
        new_lines = []
        size = len(self.points)

        for i in range(size):
            j = (i + 1) % size
            p1_belongs = hp.has_point(Point(self.points[i][0], self.points[i][1]))
            p2_belongs = hp.has_point(Point(self.points[j][0], self.points[j][1]))
            line = Line(self.lines[i][0], self.lines[i][1], self.lines[i][2])

            if p1_belongs:
                new_points.append(self.points[i]);
                new_lines.append([line.a, line.b, line.c])

                if not p2_belongs:
                    intersec_point = hp.get_intersection(line)
                    new_points.append([intersec_point.x, intersec_point.y])
                    new_lines.append([hp.a, hp.b, hp.c])

            elif p2_belongs:
                intersec_point = hp.get_intersection(line);
                new_points.append([intersec_point.x, intersec_point.y])
                new_lines.append([line.a, line.b, line.c])

        self.points = new_points
        self.lines = new_lines

if __name__ == "__main__":

    poly = Poly()
    n = int(sys.stdin.readline().strip())

    for _ in range(n):
        a, b, c = list(map(int, sys.stdin.readline().strip().split(' ')))
        hp = HalfPlane(a, b, c)
        poly.intersec(hp)
    print(poly.area())
