#define PROBLEM "https://judge.yosupo.jp/problem/eertree"

#include "prelude.h"
#include "vector_io.h"

#include "strings/eertree.h"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    EERTREE<26> tree(sz(s));
    auto id = [](int v) { return v == 0 ? 0 : v == 1 ? -1 : v - 1; };
    vector<int> last;
    for (char c : s) {
        tree.add_letter(c - 'a');
        last.push_back(id(tree.last));
    }
    vector<int> parent(tree.sz);
    for (int v = 0; v < tree.sz; ++v) {
        for (int u : tree.nx[v]) {
            if (u != 0) parent[u] = v;
        }
    }
    cout << tree.sz - 2 << '\n';
    for (int v = 2; v < tree.sz; ++v) {
        cout << id(parent[v]) << ' ' << id(tree.suff[v]) << '\n';
    }
    cout << last << '\n';
}
