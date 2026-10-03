/**
 * Author: Vladimir Ragulin
 * Description: Finds maximum flow using Dinitz algorithm.
 * Time: O(n^2 m)
 */

struct Edge {
    int to, cap, flow;
};
vector<Edge> E;
vector<int> gr[N];

int n;
int d[N], ptr[N];

bool bfs(int v0 = 0, int cc = 1) {
    fill(d, d + n, -1);
    d[v0] = 0;
    vector<int> q{v0};
    for (int st = 0; st < sz(q); ++st) {
        int v = q[st];
        for (int id : gr[v]) {
            auto [to, cp, fl] = E[id];
            if (d[to] != -1 || cp - fl < cc) continue;
            d[to] = d[v] + 1;
            q.emplace_back(to);
        }
    }
    return d[n - 1] != -1;
}

int dfs(int v, int flow, int cc = 1) {
    if (v == n - 1 || !flow) return flow;
    for (; ptr[v] < sz(gr[v]); ++ptr[v]) {
        auto [to, cp, fl] = E[gr[v][ptr[v]]];
        if (d[to] != d[v] + 1 || cp - fl < cc) continue;
        int pushed = dfs(to, min(flow, cp - fl), cc);
        if (pushed) {
            int id = gr[v][ptr[v]];
            E[id].flow += pushed;
            E[id ^ 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

ll dinitz() {
    ll flow = 0;
    for (int c = INF; c > 0; c >>= 1) {
        while (bfs(0, c)) {
            fill(ptr, ptr + n, 0);
            while (int pushed = dfs(0, INF, c))
                flow += pushed;
        }
    }
    return flow;
}
