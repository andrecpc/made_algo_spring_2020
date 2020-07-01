#include <iostream>
#include <vector>

using namespace std;

int t = 0, l = 1;
vector<bool> b;
vector<int> tin, tout;
vector<vector<pair<int, int>>> v;
vector<vector<int>> up, min_up;


void dfs(int u, int p = 0, int w = 1000000) {

    up[u][0] = p;
    tin[u] = ++t;
    b[u] = true;
    min_up[u][0] = w;

    for (int i = 1; i <= l; ++i) {

        up[u][i] = up[up[u][i - 1]][i - 1];
        min_up[u][i] = min(min_up[up[u][i - 1]][i - 1], min_up[u][i - 1]);
    }

    for (int i = 0; i < v[u].size(); ++i) {

        int to = v[u][i].first;

        if (!b[to] && to != p) {
            dfs(to, u, v[u][i].second);
        }

    }
    tout[u] = ++t;
}
bool is_parent(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {

    if (is_parent(a, b))  return 1000000;
    int to = min_up[a][0];

    for (int i = l; i >= 0; --i) {

        if (!is_parent(up[a][i], b)) {
            to = min(to, min_up[a][i]);
            a = up[a][i];
        }
    }

    return min(min_up[a][0], to);
}

int main() {

    freopen ("minonpath.in", "r", stdin);
	freopen ("minonpath.out", "w", stdout);

    int n, m, a_t, b_t;

    cin >> n;

    b.resize(n, 0);
    v.resize(n);
    tin.resize(n);
    tout.resize(n);
    up.resize(n);
    min_up.resize(n);

    for (int i = 1; i < n; ++i) {

        cin >> a_t >> b_t;
        v[a_t - 1].push_back(make_pair(i, b_t));
    }

    cin >> m;

    while ((1 << l) <= n)  ++l;

    for (int i = 0; i<n; ++i) {

        up[i].resize(l + 1);
        min_up[i].resize(l + 1);
    }

    dfs(0);

    for (int i = 0; i < m; ++i) {

        cin >> a_t >> b_t;
        a_t -=1;
        b_t -=1;
        cout << min(lca(a_t, b_t), lca(b_t, a_t)) << '\n';
    }
    return 0;
}
