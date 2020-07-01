#include <iostream>
#include <vector>

using namespace std;

int t = 0, l = 1;
vector<bool> b;
vector<vector<int>> v, up;
vector<int> tin, tout;

void dfs(int u, int p = 0) {

    int to;
    tin[u] = ++t;
    up[u][0] = p;
    b[u] = true;

    for (int i = 1; i <= l; ++i) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }

    for (int i = 0; i < v[u].size(); ++i) {

        to = v[u][i];
        if (!b[to] && to != p) {
            dfs(to, u);
        }
    }
    tout[u] = ++t;
}

bool is_parent(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {

    if (is_parent(a, b))  return a;
    if (is_parent(b, a))  return b;

    for (int i = l; i >= 0; --i) {

        if (!is_parent(up[a][i], b))
            a = up[a][i];
    }

    return up[a][0];
}


int main() {

    int n, m, a, bb;

    cin >> n;

    v.resize(n);
    b.resize(n, 0);
    tin.resize(n);
    tout.resize(n);
    up.resize(n);

    for (int i = 1; i < n; ++i) {

        cin >> a;
        v[--a].push_back(i);
    }

    cin >> m;

    while ((1 << l) <= n)  ++l;

    for (int i = 0; i < n; ++i) {
        up[i].resize(l + 1);
    }

    dfs(0);

    for (int i = 0; i < m; ++i) {

        cin >> a >> bb;
        cout << lca(a - 1, bb - 1) + 1 << '\n';
    }
    return 0;
}
