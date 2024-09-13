struct Edge {
    ll to, f, c, w;
};

vector<Edge> edges;

void add_edge(int u, int v, ll c, ll w) {
    gr[u].push_back(sz(edges));
    edges.emplace_back(v, 0, c, w);
    gr[v].push_back(sz(edges));
    edges.emplace_back(u, 0, 0, -w);
}

pair<ll, ll> mcmf(int n) {
    vector<ll> dist(n);
    vector<ll> pr(n);
    vector<ll> phi(n);
    auto dijkstra = [&] {
        fill(all(dist), INF);
        dist[0] = 0;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        pq.emplace(0, 0);
        while (!pq.empty()) {
            auto [d, v] = pq.top();
            pq.pop();
            if (d != dist[v]) continue;
            for (int idx : gr[v]) {
                if (edges[idx].c == edges[idx].f) continue;
                int to = edges[idx].to;
                ll w = edges[idx].w + phi[v] - phi[to];
                if (dist[to] > d + w) {
                    dist[to] = d + w;
                    pr[to] = idx;
                    pq.emplace(d + w, to);
                }
            }
        }
    };

    ll total_cost = 0, total_flow = 0;
    while (true) {
        dijkstra();
        if (dist[n - 1] == INF) break;
        ll min_cap = INF;
        int cur = n - 1;
        while (cur != 0) {
            min_cap = min(min_cap, edges[pr[cur]].c - edges[pr[cur]].f);
            cur = edges[pr[cur] ^ 1].to;
        }
        cur = n - 1;
        while (cur != 0) {
            edges[pr[cur]].f += min_cap;
            edges[pr[cur] ^ 1].f -= min_cap;
            total_cost += min_cap * edges[pr[cur]].w;
            cur = edges[pr[cur] ^ 1].to;
        }
        total_flow += min_cap;
        for (int i = 0; i < n; ++i) {
            phi[i] += dist[i];
        }
    }

    return {total_flow, total_cost};
}
