#include <iostream>

using namespace std;

int get_mid(int l, int r) {
    return l + (r - l) / 2;
}

void update(long long* tree, int tl, int tr, int i, long long diff, int ind) {
    if (i < tl || i > tr) {
        return;
    }

    tree[ind] = tree[ind] + diff;
    if (tr != tl) {
        int mid = get_mid(tl, tr);
        update(tree, tl, mid, i, diff, 2 * ind + 1);
        update(tree, mid + 1, tr, i, diff, 2 * ind + 2);
    }
}

long long summa(long long* tree, int tl, int tr, int l, int r, int ind) {
    if (l <= tl && r >= tr) {
        return tree[ind];
    }

    if (tr < l || tl > r) {
        return 0;
    }

    int mid = get_mid(tl, tr);

    return summa(tree, tl, mid, l, r, 2 * ind + 1) + summa(tree, mid + 1, tr, l, r, 2 * ind + 2);

}

long long build(long long* a, int tl, int tr, long long* tree, int ind) {
    if (tl == tr) {
        tree[ind] = a[tl];
        return a[tl];
    }

    int mid = get_mid(tl, tr);
    tree[ind] = build(a, tl, mid, tree, ind * 2 + 1) + build(a, mid + 1, tr, tree, ind * 2 + 2);

    return tree[ind];
}

int main() {

    int n;
    cin >> n;

    long long a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long* tree = new long long[4 * n];
    build(a, 0, n - 1, tree, 0);
    string oper;

    while (cin >> oper) {

        if (oper == "sum") {
            int i, j;
            cin >> i;
            cin >> j;
            cout << summa(tree, 0, n - 1, i - 1, j - 1, 0) << "\n";
        }

        if (oper == "set") {
            int i;
            long long x, diff;
            cin >> i;
            cin >> x;
            diff = x - a[i - 1];
            a[i - 1] = x;
            update(tree, 0, n - 1, i - 1, diff, 0);
        }
    }

    return 0;
}
