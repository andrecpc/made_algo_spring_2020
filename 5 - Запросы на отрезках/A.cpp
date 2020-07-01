#include <iostream>

using namespace std;

int main() {

    int n, x, y, a0, m, z, t, b0;
    cin >> n >> x >> y >> a0;
    cin >> m >> z >> t >> b0;

    int* a = new int[n];
    long long* pref = new long long[n];
    int* b = new int[2 * m];
    int* c = new int[2 * m];
    a[0] = a0;
    pref[0] = a0;
    b[0] = b0;

    for (int i = 1; i < 2 * m; i++) {

        if (i < n) {
           a[i] = (x * a[i - 1] + y) % (1 << 16);
           pref[i] = a[i] + pref[i - 1];
        }

        b[i] = (z * b[i - 1] + t) % (1 << 30);
        if (b[i] < 0) b[i] = (1 << 30) + b[i];

        c[i] = b[i] % n;
    }

    c[0] = b[0] % n;

    long long out = 0;

    for (int i = 0; i < m; i++) {
        int r = max(c[2 * i], c[2 * i + 1]);
        int l = min(c[2 * i], c[2 * i + 1]);
        if (l > 0) out += pref[r] - pref[l - 1];
        else out += pref[r];
    }

    cout << out;
    return 0;
}
