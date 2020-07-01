#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int SIZE = 524288;
const int SHIFT = 200000;

struct node {
    int dy, ty, delta, x;
};

bool cmp(node &a, node &b) {
    return (a.x != b.x ? a.x < b.x : a.delta > b.delta);
}

vector<int> a(4 * SIZE + 1, 0), lazy(4 * SIZE + 1, 0);

void push(size_t ind) {
    lazy[2 * ind + 1] += lazy[ind];
    lazy[2 * ind + 2] += lazy[ind];
    lazy[ind] = 0;
}

void add(size_t ind, int li, int ri, int l, int r, int delta) {

    if (li == l && ri == r) {
        lazy[ind] += delta;
        return;
    }

    push(ind);
    int c = (li + ri) / 2;
    if (r <= c) add(2 * ind + 1, li, c, l, r, delta);
    if (l >= c) add(2 * ind + 2, c, ri, l, r, delta);
    if (r > c && l < c) {
        add(2 * ind + 1, li, c, l, c, delta);
        add(2 * ind + 2, c, ri, c, r, delta);
    }

    int g = a[2 * ind + 1] + lazy[2 * ind + 1];
    int h = a[2 * ind + 2] + lazy[2 * ind + 2];
    a[ind] = max(g, h);
}

pair<int, int> query(size_t ind, size_t li, size_t ri) {

    if (li + 1 == ri) {

        a[ind] += lazy[ind];
        lazy[ind] = 0;
        return {a[ind], li};
    }

    push(ind);
    int g = a[2 * ind + 1] + lazy[2 * ind + 1];
    int h = a[2 * ind + 2] + lazy[2 * ind + 2];
    a[ind] = max(g, h);

    size_t c = (li + ri) / 2;

    if (g > h) {
        return query(2 * ind + 1, li, c);
    } else {
        return query(2 * ind + 2, c, ri);
    }
}

int main() {

    size_t n;
    cin >> n;
    int x1, y1, x2, y2;
    vector<node> s(2 * n);

    for (size_t i = 0; i < n; i++) {

        cin >> x1 >> y1 >> x2 >> y2;
        y1 += SHIFT;
        y2 += SHIFT;
        s[2 * i] = node{y1, y2, 1, x1 + SHIFT};
        s[2 * i + 1] = node{y1, y2, -1, x2 + SHIFT};
    }

    sort(s.begin(), s.end(), cmp);

    int max_res = -1, x = 0, y = 0;

    for (size_t i = 0; i < n * 2; i++) {

        add(0, 0, 4 * SHIFT + 1, s[i].dy, s[i].ty + 1, s[i].delta);
        auto tmp = query(0, 0, 4 * SHIFT + 1);

        if (tmp.first > max_res) {

            max_res = tmp.first;
            x = s[i].x;
            y = tmp.second;
        }
    }

    cout << max_res << endl << x - SHIFT << " " << y - SHIFT;

    return 0;
}
