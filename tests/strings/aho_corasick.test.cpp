#define PROBLEM "https://judge.yosupo.jp/problem/aho_corasick"

#include "prelude.h"
#include "vector_io.h"

#include "strings/aho_corasick.h"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        add_word(s, i);
    }
    vector<int> parent(sz(t)), terminal(n);
    for (int v = 0; v < sz(t); ++v) {
        for (int u : t[v].nx) {
            if (u != -1) parent[u] = v;
        }
        for (int id : t[v].idx) terminal[id] = v;
    }
    build_aho();
    cout << sz(t) << '\n';
    for (int v = 1; v < sz(t); ++v) {
        cout << parent[v] << ' ' << t[v].suff << '\n';
    }
    cout << terminal << '\n';
}
