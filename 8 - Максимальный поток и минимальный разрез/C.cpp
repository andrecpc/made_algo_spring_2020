#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int m;
int s;
int t;


struct Edge {

    int from = 0;
    int to = 0;
    int f = 0;
    int c = 0;
    Edge *rev = nullptr;
    int index = 0;

    Edge() = default;

    Edge(int from, int to, int c, int index) : from(from), to(to), f(0), c(c), index(index) {}
};

vector<Edge> Edges;

vector<vector<Edge *>> graph;

vector<bool> used;

int dfs(int cur, int c) {

    if (cur == t) {
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

        ans = dfs(s, 1e9);
        fill(used.begin(), used.end(), false);
        maxans += ans;
    } while (ans > 1e-5);
    return maxans;
}

void draw(int cur) {

    used[cur] = true;

    for (int i = 0; i < graph[cur].size(); ++i) {

        Edge *e = graph[cur][i];
        int next = e->to;

        if (!used[next] && e -> c - e -> f > 1e-5) {
            draw(next);
        }
    }
}


vector<Edge *> incut;

void find_edges() {

    for (int i = 0; i < 2 * m; i += 2) {

        if (used[Edges[i].from] ^ used[Edges[i].to]) {
            incut.emplace_back(&Edges[i]);
        }
    }
}

vector<int> pred;

void find_pred(int cur) {

    pred.emplace_back(cur);

    if (cur == t) {
        return;
    }

    for (auto it : graph[cur]) {
        int next = it -> to;

        if (it -> f == 1) {

            it -> f = 0;
            find_pred(next);
            return;
        }
    }
}

int main() {

    cin >> n;
    cin >> m;
    cin >> s;
    cin >> t;

    s--;
    t--;

    graph.resize(n, vector<Edge *>());

    Edges.resize(2 * m);

    for (int i = 0; i < 2 * m; i += 2) {

        int from;
        int to;
        int c;

        cin >> from >> to;

        from--;
        to--;
        Edges[i] = Edge(from, to, 1, i);
        Edges[i + 1] = Edge(to, from, 0, i + 1);
        Edges[i].rev = &Edges[i + 1];
        Edges[i + 1].rev = &Edges[i];
        graph[from].emplace_back(&Edges[i]);
        graph[to].emplace_back(&Edges[i + 1]);
    }

    used.resize(n, false);
    cout.precision(10);
    int F = Dinic();

    if (F < 2) {
        cout << "NO";
        return 0;
    }

    cout << "YES\n";
    find_pred(s);

    for (auto it : pred) {
        cout << it + 1 << ' ';
    }

    pred.clear();
    find_pred(s);
    cout << endl;

    for (auto it : pred) {
        cout << it + 1 << ' ';
    }

    return 0;
}
