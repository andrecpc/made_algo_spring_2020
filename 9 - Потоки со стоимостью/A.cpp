#include<iostream>
#include <vector>
#include <set>

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
    vector<Edge *> previous;

    Graph() {}

    Graph(ll n, ll m, ll start, ll finish) : n(n), m(m), start(start), finish(finish) {}

    void resize() {

        Nodes.resize(n);
        previous.resize(n);
    }

    void read() {

        cin >> n;
        cin >> m;
        start = 0;
        finish = n - 1;
        resize();

        for (ll i = 0; i < m; ++i) {

            ll from, to, capacity, cost;

            cin >> from >> to >> capacity >> cost;

            --from;
            --to;
            Edges.emplace_back(from, to, capacity, cost);
            Edges.emplace_back(to, from, 0, -cost);
        }

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

    ll Dijkstra() {

        vector<ll> dist(n, INF);
        dist[start] = 0;
        set<pair<ll, ll>> vertexes;
        vertexes.insert({dist[start], start});

        while (!vertexes.empty()) {

            auto top = vertexes.begin();
            ll cur = top -> second;
            ll cost = top -> first;
            vertexes.erase(top);

            for(ll i = 0; i < Nodes[cur].list.size(); ++i) {

                Edge *e = Nodes[cur].list[i];

                if (dist[cur] != INF && e -> flow < e -> capacity && dist[cur] + e -> cost < dist[e -> to]) {

                    dist[e -> to] = dist[cur] + e -> cost;
                    previous[e -> to] = e;
                    vertexes.insert({dist[e -> to], e -> to});
                }
            }
        }

        return dist[finish];
    }

    ll find_flow() {

        ll cur = finish;
        ll cur_flow = INF;

        while (cur != start) {

            cur_flow = min(cur_flow, previous[cur] -> capacity - previous[cur] -> flow);
            cur = previous[cur] -> from;
        }

        return cur_flow;
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
        ll distance = Dijkstra();
        ll min_cost = 0;

        while (distance != INF) {

            ll flow = find_flow();
            min_cost += flow * distance;
            update_flow(flow);
            distance = Dijkstra();
        }

        return min_cost;
    }

    void accepted() {
        cout << mincost();
    }
};

int main() {

    Graph graph;
    graph.accepted();

    return 0;
}
