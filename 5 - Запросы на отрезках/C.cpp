#include <bits/stdc++.h>

using namespace std;

struct Node{
    int oper = 0;
    long long set_value;
    long long ans;
    long long add_value;
};

vector <Node> tree;
const long long inf = pow(10, 18);

void build(vector <Node> a) {

    for (int i = 0; i < a.size(); i++) {
        tree[tree.size() / 2 + i].ans = a[i].ans;
    }
    for (int i = a.size() - 2; i >= 0; i--) {
        tree[i].ans = min(tree[2 * i + 1].ans, tree[2 * i + 2].ans);
    }
}

void push(int v) {

	if (tree[v].oper == 1 && (2 * v + 1) < tree.size()) {
		tree[2 * v + 1].set_value = tree[v].set_value;
		tree[2 * v + 1].ans = tree[v].set_value;
		tree[2 * v + 1].oper = 1;
		tree[2 * v + 2].set_value = tree[v].set_value;
		tree[2 * v + 2].ans = tree[v].set_value;
		tree[2 * v + 2].oper = 1;
		tree[v].oper = 0;
	} else if (tree[v].oper == 2 && (2 * v + 1) < tree.size()) {
        tree[2 * v + 1].ans += tree[v].add_value;
        tree[2 * v + 2].ans += tree[v].add_value;
        push(2 * v + 1);
        tree[2 * v + 1].add_value = tree[v].add_value;
        push(2 * v + 2);
        tree[2 * v + 2].add_value = tree[v].add_value;
        tree[2 * v + 1].oper = 2;
        tree[2 * v + 2].oper = 2;
        tree[v].oper = 0;
	}

}

void update_min(int v) {

    if (v == 0){
        return;
    }
    if (v == (v - 1) / 2 * 2 + 1) {
        tree[(v - 1) / 2].ans = min(tree[v].ans, tree[((v - 1) / 2) * 2 + 2].ans);
    } else {
        tree[(v - 1) / 2].ans = min(tree[v].ans, tree[((v - 1) / 2) * 2 + 1].ans);
    }
    update_min((v - 1) / 2);
}

void update_add(int v, int left, int right, int a, int b, long long add_val) {

    if (a > b)
        return;
	if (a == left && right == b) {
        if (tree[v].oper == 2) {
            tree[v].ans += add_val;
            update_min(v);
            tree[v].add_value += add_val;
        } else if (tree[v].oper == 1) {
            push(v);
            tree[v].ans += add_val;
            update_min(v);
            tree[v].oper = 2;
            tree[v].add_value = add_val;
        } else {
            tree[v].ans += add_val;
            update_min(v);
            tree[v].oper = 2;
            tree[v].add_value = add_val;
        }

	} else {
	    push(v);
		int tm = (left + right) / 2;
		update_add (2 * v + 1, left, tm, a, min(b, tm), add_val);
		update_add (2 * v + 2, tm + 1, right, max(a, tm + 1), b, add_val);
	}

}

void update_set(int v, int left, int right, int a, int b, long long set_val) {

    if (a > b)
		return;
	if (a == left && right == b) {
		tree[v].ans = set_val;
		tree[v].set_value = set_val;
		tree[v].oper = 1;
		update_min(v);
	}
	else {
		push (v);
		int tm = (left + right) / 2;
		update_set (2 * v + 1, left, tm, a, min(b,tm), set_val);
		update_set (2 * v + 2, tm + 1, right, max(a, tm + 1), b, set_val);
	}
}

long long get_min(int v, int left, int right, int a, int b) {

    if (a > b) return inf;
    if (a == left && b == right) {
        if (tree[v].oper == 2 && (2 * v + 1 < tree.size()))
            return tree[v].ans;
        else return tree[v].ans;
    }
    push(v);
    int m = (left + right) / 2;

    return min(get_min(2 * v + 1, left, m , a, min(b, m)),
        get_min(2 * v + 2, m + 1, right, max(a, m + 1), b));

}


int main()
{
    int n;
    cin >> n;
    long long p = 1;

    while (p < n) p *= 2;

    p *= 2;
    vector <Node> a;
    a.resize(p / 2);

    for (int i = 0; i < n; i++) {
        cin >> a[i].ans;
    }

    for (int i = n; i < a.size(); i++) {
        a[i].ans = inf;
    }

    tree.resize(p - 1);

    if (n == 1) {
        tree = a;
    } else {
        build(a);
    }

    string oper;
    while (cin >> oper) {

        if (oper == "min") {
            int i, j;
            cin >> i >> j;
            cout << get_min(0, 0 , a.size() - 1, --i, --j) << endl;

        } else if (oper == "set") {
            int i, j, x;
            cin >> i >> j >> x;
            update_set(0, 0, a.size() - 1, --i, --j, x);

        } else if (oper == "add") {
            int i, j, x;
            cin >> i >> j >> x;
            update_add(0, 0 , a.size() - 1, --i, --j, x);

        }
    }

    return 0;
}
