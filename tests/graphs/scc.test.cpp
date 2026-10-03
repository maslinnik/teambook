#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "prelude.h"
#include "vector_io.h"

#include "graphs/tarjan_scc.h"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    g.resize(n);
    tin.resize(n);
    up.resize(n);
    color.resize(n);
    comp.assign(n, -1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }
    for (int v = 0; v < n; ++v) {
        if (color[v] == 0) dfs(v);
    }
    vector<vector<int>> components(comp_col);
    for (int v = 0; v < n; ++v) {
        components[comp[v]].push_back(v);
    }
    reverse(all(components));
    cout << comp_col << '\n';
    for (auto& vertices : components) {
        cout << sz(vertices) << ' ' << vertices << '\n';
    }
}
