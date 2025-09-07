/**
 * Author: Gleb Kostylev
 * Date: 2025-09-08
 * Source: https://contest.ucup.ac/submission/1299010
 * Description: Finds maximum weighed matroid intersection.
 * m.may\_be\_added(set as a vector of items) - items that may be added to independent set for it to still be independent.
 * Time: O(|answer| \cdot n \cdot (m.may\_be\_added + n))
 * Status: AC in ucup task about matroids
 */
template <class M1, class M2>
vector<int> matroid_intersection(M1& m1, M2& m2, int n, auto&& cost = [](int) {return 1;}) {
    const ll INF18 = 4'000'000'000'000'000'000;
    vector<int> result;
    vector<ll> potential(n, 0);
    while (true) {
        vector<int> start_zone = m1.may_be_added(result);
        vector<int> end_zone = m2.may_be_added(result);
        vector<vector<int>> g(n);
        for (int i = 0; i < result.size(); ++i) {
            int val = result[i];
            swap(result[i], result.back());
            result.pop_back();
            vector<int> forward_edges = m1.may_be_added(result);
            vector<int> backward_edges = m2.may_be_added(result);
            for (auto x : forward_edges) {
                if (x == val) continue;
                g[val].push_back(x);
            }
            for (auto x : backward_edges) {
                if (x == val) continue;
                g[x].push_back(val);
            }
            result.push_back(val);
            swap(result[i], result.back());
        }
        set<pair<pair<ll, int>, int>> d;
        vector<pair<ll, int>> dist(n, {INF18, -1});
        vector<int> parent(n, -1);
        vector<char> is_used(n);
        for (auto v : start_zone) {
            dist[v] = {-cost(v) - potential[v], 0};
        }
        while (true) {
            int v = -1;
            for (int i = 0; i < n; ++i) {
                if (is_used[i] || dist[i] == pair{INF18, -1}) {
                    continue;
                }
                if (v == -1 || dist[i] < dist[v]) {
                    v = i;
                }
            }
            if (v == -1) break;
            is_used[v] = 1;
            for (auto u : g[v]) {
                ll w = potential[v] - potential[u] + (dist[v].second & 1 ? cost(v) - cost(u) : 0);
                if (w < 0) {
                    exit(1);
                }
                pair<ll, int> u_dist = dist[v];
                ++u_dist.second;
                u_dist.first += w;
                if (dist[u] > u_dist) {
                    dist[u] = u_dist;
                    parent[u] = v;
                }
            }
        }
        pair<ll, int> best_dist = {1, -1};
        int best_end = -1;
        for (auto v : end_zone) {
            pair<ll, int> dist_now = dist[v];
            if (dist_now == pair{INF18, -1}) {
                continue;
            }
            dist_now.first += potential[v];
            if (dist_now < best_dist) {
                best_dist = dist_now;
                best_end = v;
            }
        }
        if (best_end == -1) {
            break;
        }
        vector<int> xr;
        while (best_end != -1) {
            xr.push_back(best_end);
            best_end = parent[best_end];
        }
        ranges::sort(xr);
        ranges::sort(result);
        vector<int> new_result;
        new_result.reserve(xr.size() + result.size());
        ranges::merge(xr, result, back_inserter((new_result)));
        int sz = 0;
        for (int i = 0; i < new_result.size(); ++i) {
            if (i + 1 != new_result.size() && new_result[i] == new_result[i + 1]) {
                ++i;
                continue;
            }
            new_result[sz++] = new_result[i];
        }
        new_result.resize(sz);
        result = std::move(new_result);
        for (int i = 0; i < n; ++i) {
            potential[i] += dist[i].first;
        }
    }
    return result;
}