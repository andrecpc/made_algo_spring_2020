#include <iostream>
#include <string>
#include <array>

using namespace std;

class SufTree {

 private:

    static const int ALPH_SIZE = 26;

 private:

    struct SufNode;

    struct SufEdge {

        SufNode *from;
        SufNode *to;
        int left;
        int right;

        SufEdge(SufNode *start, SufNode *end)
                : from(start), to(end), left(0), right(0) {}

        SufEdge(SufNode *start, SufNode *end, pair<int, int> bounds)
                : from(start), to(end), left(bounds.first), right(bounds.second) {}

        void set_left(int l) {
            left = l;
        }

        void set_right(int r) {
            right = r;
        }

        void set_bounds(pair<int, int> bounds) {

            left = bounds.first;
            right = bounds.second;
        }

        pair<int, int> get_bounds() {
            return {left, right};
        }

        int get_len() {
            return right - left;
        }
    };

 private:

    struct SufNode {

        int id;
        SufNode *link;

        array<SufEdge*, ALPH_SIZE> kids{{nullptr}};
        explicit SufNode(int id) : id(id), link(nullptr) {}

        void set_link(SufNode *node) {
            link = node;
        }

        SufNode *get_link() {
            return link;
        }

        void set_kid(int ind, SufEdge *res) {
            kids[ind] = res;
        }

        SufEdge *get_kid(int ind) {
            return kids[ind];
        }
    };

    int node_cnt = 0;
    int depth = 0;
    SufNode * const root;
    SufNode *pre;
    SufNode *cur;

 private:

    void dfs(SufNode *node, ostream &out) {

        if (!node) return;

        for (SufEdge *edge : node->kids) {

            if (!edge) continue;

            out << node -> id << ' '
                << edge -> to -> id << ' '
                <<edge -> left + 1 << ' '
                << edge -> right << '\n';

            dfs(edge -> to, out);
        }
    }

    int get_char(char c) {
        return c - 'a';
    }

    SufNode *gen_node() {
        return new SufNode(++node_cnt);
    }

 public:

    explicit SufTree(string const &s) : root(gen_node()), cur(root) {

        for (int i = 0; i < s.size(); i++) {

            pre = nullptr;
            depth++;

            while (depth > 0) {

                while (true) {

                    SufEdge *edge = cur -> get_kid(get_char(s[i - depth + 1]));
                    if (!edge) break;
                    int len = edge -> get_len();
                    if (depth <= len) break;
                    depth -= len;
                    cur = edge -> to;
                }

                SufEdge *edge = cur->get_kid(get_char(s[i - depth + 1]));

                if (edge) {
                    int next_char = edge->left + depth - 1;

                    if (s[next_char] == s[i]) {

                        if (pre) pre->set_link(cur);
                        break;
                    }

                    else {
                        auto *new_node = gen_node();
                        auto *new_node2 = gen_node();
                        auto *new_edge = new SufEdge(new_node, edge -> to);
                        new_edge -> set_bounds({next_char, edge -> right});
                        auto *new_edge2 = new SufEdge(new_node, new_node2, {i, s.size()});
                        new_node -> set_kid(get_char(s[next_char]), new_edge);
                        new_node -> set_kid(get_char(s[i]), new_edge2);
                        edge -> right = next_char;
                        edge -> to = new_node;
                        if (pre) pre -> set_link(new_node);
                        pre = new_node;
                    }

                }

                else {
                    auto *new_node = gen_node();
                    auto *new_edge = new SufEdge(cur, new_node, {i, s.size()});
                    cur -> set_kid(get_char(s[i]), new_edge);
                    if (pre) pre -> set_link(cur);
                    pre = nullptr;
                }

                if (cur == root) depth--;
                else cur = cur -> get_link();
            }
        }
    }

    void dfs(ostream &out) {

        out << node_cnt << ' ' << node_cnt - 1 << '\n';
        dfs(root, out);
    }
};

int main() {

    string s;
    cin >> s;
    SufTree suf_tree(s);
    suf_tree.dfs(cout);

    return 0;
}
