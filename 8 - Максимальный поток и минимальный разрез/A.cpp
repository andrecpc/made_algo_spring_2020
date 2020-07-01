#include <iostream>
#include <vector>

using namespace std;

int n;
int m;

struct Edge {

    int from = 0;
    int to = 0;
    int f = 0;
    int c = 0;
    Edge *rev = nullptr;

    Edge() = default;

    Edge(int from, int to, int c) : from(from), to(to), f(0), c(c) {}
};

vector<Edge> Edges;

vector<vector<Edge *>> graph;

vector<bool> used;

int dfs(int cur, int c) {

    if (cur == n - 1) {
        return c;
    }

    used[cur] = true;
    for (int i = 0; i < graph[cur].size(); ++i) {
        int next = graph[cur][i] -> to;
        Edge *e = graph[cur][i];
        if (!used[next] && e -> f < e -> c) {
            int diff = dfs(next, min(e -> c - e -> f, c));
            if (diff > 1e-5) {
                e -> f += diff;
                e -> rev -> f -= diff;
                return diff;
            }
        }
    }
    return 0;
}

int Dinic() {

    int ans = 0;
    int maxans = 0;

    do {

        ans = dfs(0, 1e9);
        fill(used.begin(), used.end(), false);
        maxans += ans;
    } while (ans > 1e-5);
    return maxans;
}

int main() {

    cin >> n;
    cin >> m;

    graph.resize(n, vector<Edge *>());

    Edges.resize(2 * m);

    for (int i = 0; i < 2 * m; i += 2) {

        int from;
        int to;
        int c;
        cin >> from >> to >> c;
        from--;
        to--;
        Edges[i] = Edge(from, to, c);
        Edges[i + 1] = Edge(to, from, c);
        Edges[i].rev = &Edges[i + 1];
        Edges[i + 1].rev = &Edges[i];
        graph[from].emplace_back(&Edges[i]);
        graph[to].emplace_back(&Edges[i + 1]);
    }

    used.resize(n, false);
    cout.precision(10);
    cout << Dinic() << endl;

    for (int i = 0; i < 2 * m; i += 2) {
        cout << Edges[i].f << '\n';
    }
    return 0;
}
