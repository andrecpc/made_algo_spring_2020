#include <iostream>
#include <vector>
#include <string>

using namespace std;

int precount(int const& x) {

        if (x == 1) return 0;
        return precount(x / 2) + 1;
}

int main() {

    int n, m, u, v;
    cin >> n >> m;
    vector<int> logs(n + 1, 0);
    vector<int> a(n + 1);
    cin >> a[1] >> u >> v;

    for (int i = 2; i <= n; i++) {
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
        logs[i] = precount(i);
    }

    vector<vector<int>> st(n + 1, vector<int>(logs[n] + 1));

    for (int j = 0; j <= logs[n]; j++) {
        for (int i = 1; i <= n; i++) {
            if (j > logs[n - i + 1]) break;

            if (j) st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            else st[i][0] = a[i];
        }
    }

    int ans = 0;
    for (int i = 1; i <= m; i++) {

        int l = min(u, v);
        int r = max(u, v);
        int j = logs[r - l + 1];

        ans = min(st[l][j], st[r - (1 << j) + 1][j]);

        if (i != m) {
            u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
            v = ((13 * v + 593 + ans + 5 * i) % n) + 1;
        }
    }
    cout << u << " " << v << " " << ans;
}
