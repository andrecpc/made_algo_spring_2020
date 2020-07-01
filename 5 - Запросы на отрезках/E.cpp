#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

long long r, n, m, q, w;

struct node {

    long long a11, a12, a21, a22;

    void normalize() {

        a11 %= r;
        a12 %= r;
        a21 %= r;
        a22 %= r;
    }
};

node operator*(node m1, node m2) {

    node res;
    res.a11 = m1.a11 * m2.a11 + m1.a12 * m2.a21;
    res.a12 = m1.a11 * m2.a12 + m1.a12 * m2.a22;
    res.a21 = m1.a21 * m2.a11 + m1.a22 * m2.a21;
    res.a22 = m1.a21 * m2.a12 + m1.a22 * m2.a22;
    res.normalize();
    return res;
}

vector<node> a;
vector<node> t;

void build(int ind, int l, int r) {

    if (l < r - 1) {

        int c = (l + r) / 2;
        build(2 * ind + 1, l, c);
        build(2 * ind + 2, c, r);
        t[ind] = t[2 * ind + 1] * t[2 * ind + 2];

    } else {
        t[ind] = a[l];
    }
}

node rmq(int ind, int li, int ri, int l, int r) {

    if (li == l && ri == r) return t[ind];
    int c = (li + ri) / 2;
    if (r <= c) return rmq(2 * ind + 1, li, c, l, r);
    if (l >= c) return rmq(2 * ind + 2, c, ri, l, r);
    node m1 = rmq(2 * ind + 1, li, c, l, c), m2 = rmq(2 * ind + 2, c, ri, c, r);

    return m1 * m2;
}

int main() {
    ios_base::sync_with_stdio(false);
    freopen ("crypto.in", "r", stdin);
	freopen ("crypto.out", "w", stdout);
    cin >> r >> n >> m;
    a.resize(n);
    t.resize(4 * n);

    for (int i = 0; i < n; i++) {

        cin >> a[i].a11 >> a[i].a12 >> a[i].a21 >> a[i].a22;
        a[i].normalize();
    }

    build(0, 0, n);

    for (int i = 0; i < m; i++) {

        cin >> q >> w;
        node t = rmq(0, 0, n, q - 1, w);
        cout << t.a11 << " " << t.a12 << endl << t.a21 << " " << t.a22 << "\n\n";
    }
}
