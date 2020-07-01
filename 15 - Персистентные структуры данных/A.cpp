#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int num;
    long long val;
};

vector <Node> p;

void push(int i, long long m) {
    Node k;
    k.num = i;
    k.val = m;
    p.push_back(k);
}

long long pop(int i) {
    p.push_back(p[p[i].num]);
    return p[i].val;
}

int main() {
    int n;
    cin >> n;
    Node k;
    k.num = 0, k.val = 0;
    p.push_back(k);

    for (int i = 0; i < n; ++i) {
        int t;
        long long m;
        cin >> t >> m;

        if (m != 0) {
            push(t, m);
        }

        else {
            long long ans;
            ans = pop(t);
            cout << ans << '\n';
        }
    }

    return 0;
}
