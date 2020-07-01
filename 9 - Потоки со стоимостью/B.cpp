#include<iostream>
#include <vector>

using namespace std;

typedef long long ll;

#define INF (ll)1e18

struct Edge {

    ll from = 0;
    ll to = 0;
    ll capacity = 0;
    ll cost = 0;
    ll flow = 0;
    Edge *reverse = nullptr;

    Edge() {}

    Edge(ll from, ll to, ll capacity, ll cost) : from(from), to(to), capacity(capacity), cost(cost) {}
};


struct Node {

    ll ind = 0;
    vector<Edge *> list;

    Node() {}

    Node(ll ind) : ind(ind) {}

    void add_edge(Edge *e) {
        list.push_back(e);
    }
};

struct Graph {

    ll n = 0;
    ll m = 0;
    ll start = 0;
    ll finish = 0;
    vector<Node> Nodes;
    vector<Edge> Edges;
    vector<ll> potential;
    vector<vector<ll>> w;
    vector<Edge *> previous;

    Graph() {}

    Graph(ll n, ll m, ll start, ll finish) : n(n), m(m), start(start), finish(finish) {}

    void resize() {

        Nodes.resize(2 * n + 2);
        previous.resize(2 * n + 2);
        w.resize(n, vector<ll>(n, 0));
        potential.resize(2 * n + 2, INF);
    }

    void read() {

        cin >> n;

        start = 0;
        finish = 2 * n + 1;
        resize();

        for (ll i = 0; i < n; ++i) {

            for (ll j = 0; j < n; ++j) {

                cin >> w[i][j];
            }
        }

        for(ll i = start + 1; i < 1 + n; ++i) {

            Edges.emplace_back(start, i, 1, 0);
            Edges.emplace_back(i, start, 0, 0);
        }

        for(ll i = start + 1; i < 1 + n; ++i) {

            for(ll j = 1 + n; j < finish; ++j) {

                ll from = i;
                ll to = j;
                ll ind_from = i - 1;
                ll ind_to = j - 1 - n;
                Edges.emplace_back(from, to, 1, w[ind_from][ind_to]);
                Edges.emplace_back(to, from, 0, -w[ind_from][ind_to]);
            }
        }

        for(ll i = 1 + n; i < finish; ++i) {

            Edges.emplace_back(i, finish, 1, 0);
            Edges.emplace_back(finish, i, 0, 0);
        }

        m = Edges.size() / 2;

        for (ll i = 0; i < m; ++i) {

            ll ind = 2 * i;
            Edges[ind].reverse = &Edges[ind + 1];
            Edges[ind + 1].reverse = &Edges[ind];
        }

        for (ll i = 0; i < m; ++i) {

            ll ind = 2 * i;
            ll from = Edges[ind].from;
            ll to = Edges[ind].to;
            Nodes[from].add_edge(&Edges[ind]);
            Nodes[to].add_edge(&Edges[ind + 1]);
        }
    }

    void BellmanFord() {

        for (ll i = 0; i < 2 * n + 2; ++i) {

            for (ll j = 0; j < 2 * n + 2; ++j) {

                if (potential[j] < INF) {

                    for (ll k = 0; k < Nodes[j].list.size(); ++k) {

                        Edge *e = Nodes[j].list[k];

                        if (e -> capacity > 0 && potential[e -> to] > potential[j] + e -> cost) {
                            potential[e -> to] = potential[j] + e -> cost;
                        }
                    }
                }
            }
        }
    }

    void init_potential() {

        potential[start] = 0;
        BellmanFord();
    }

    ll Dijkstra() {

        vector<ll> dist(2 * n + 2, INF);
        vector<int> used(2 * n + 2, 0);
        dist[start] = 0;

        while (true) {

            ll cur = -1;

            for (ll i = 0; i < 2 * n + 2; ++i) {

                if (!used[i] && dist[i] < INF && (cur == -1 || dist[i] < dist[cur])) {
                    cur = i;
                }
            }

            if (cur == -1) {
                break;
            }

            used[cur] = 1;

            for(ll i = 0; i < Nodes[cur].list.size(); ++i) {

                Edge *e = Nodes[cur].list[i];

                if (e -> flow < e -> capacity && !used[e -> to] && dist[cur] + e -> cost + potential[cur] - potential[e -> to] < dist[e -> to]) {

                    dist[e -> to] = dist[cur] + e -> cost + potential[cur] - potential[e -> to];
                    previous[e -> to] = e;
                }
            }
        }

        for (ll i = 0; i < 2 * n + 2; ++i) {
            potential[i] += dist[i];
        }

        return dist[finish];
    }

    pair<ll, ll> find_flow() {

        ll cur = finish;
        ll cur_flow = INF;
        ll cur_cost = 0;

        while (cur != start) {

            cur_flow = min(cur_flow, previous[cur] -> capacity - previous[cur] -> flow);
            cur_cost += previous[cur] -> cost;
            cur = previous[cur] -> from;
        }

        return {cur_flow, cur_cost};
    }

    void update_flow(ll &flow) {

        if (flow != 0) {
            ll cur = finish;

            while (cur != start) {

                previous[cur] -> flow += flow;
                previous[cur] -> reverse -> flow -= flow;
                cur = previous[cur] -> from;
            }
        }
    }

    ll mincost() {

        read();
        init_potential();
        ll distance = Dijkstra();
        ll min_cost = 0;

        while (distance != INF) {

            auto tmp = find_flow();
            ll flow = tmp.first;
            ll cost = tmp.second;
            min_cost += flow * cost;
            update_flow(flow);
            distance = Dijkstra();
        }

        return min_cost;
    }

    void accepted() {

        cout << mincost() << endl;

        for(ll i = start + 1; i < 1 + n; ++i) {

            for(ll j = 0; j < Nodes[i].list.size(); ++j) {

                Edge *e = Nodes[i].list[j];
                ll from = e -> from;
                ll to = e -> to;
                ll ind_from = from - 1;
                ll ind_to = to - 1 - n;

                if (e -> flow == 1) {

                    cout << ind_from + 1 << ' ' << ind_to + 1 << '\n';
                }
            }
        }
    }
};

int main() {

    Graph graph;
    graph.accepted();

    return 0;
}
