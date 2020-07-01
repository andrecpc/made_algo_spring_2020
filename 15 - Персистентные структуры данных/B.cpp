#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int val;
    Node* lchild;
    Node* rchild;
};

void build(Node* node, int* base, int l, int r) {
    if (l == r) {
        node -> val = base[l - 1];
    }

    else {
        int m = (l + r) / 2;
        node -> lchild = new Node();
        build(node -> lchild, base, l, m);
        node -> rchild = new  Node();
        build(node -> rchild, base, m + 1, r);
    }
}

void add(Node* to, Node* from, int l, int r, int npos, int nv) {
    if (l == r) {
        to -> val = nv;
    }

    else {
        int m = (l + r) / 2;
        if (npos <= m) {
            to -> rchild = from -> rchild;
            Node* left = new Node();
            add(left, from -> lchild, l, m, npos, nv);
            to -> lchild = left;
        }

        else {
            to -> lchild = from -> lchild;
            Node* right = new Node();
            add(right, from -> rchild, m + 1, r, npos, nv);
            to -> rchild = right;
        }
    }
}

int get(Node* node, int l, int r, int pos) {
    if (l == r) {
        return node -> val;
    }

    else {
        int m = (l + r) / 2;
        if (pos <= m) {
            return get(node -> lchild, l, m, pos);
        }

        else {
            return get(node -> rchild, m + 1, r, pos);
        }
    }
}

int main() {
    int n;
    cin >> n;
    int base[n];

    for (int i = 0; i < n; i++) {
        cin >> base[i];
    }

    vector<Node*> parray;
    parray.push_back(new Node());
    build(parray.at(0), base, 1, n);
    int m;

    cin >> m;

    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;

        if (s == "create") {
            int rootPos, newPos, newVal;
            cin >> rootPos >> newPos >> newVal;
            parray.push_back(new Node());
            add(parray.back(), parray.at(rootPos-1), 1, n, newPos, newVal);
        }

        else {
            int rootPos, valPos;
            cin >> rootPos >> valPos;
            cout << get(parray.at(rootPos-1), 1, n, valPos) << '\n';
        }
    }

    return 0;
}
