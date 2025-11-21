/**
 * Author: Vladimir Ragulin
 * Date: 2025-11-20
 * Description: Finds SCC for oriented graph in reverse topsort order.
 * Time: O(n + m)
 * Status: AC in basic problem on SCC
 */

vector<vector<int>> g;
vector<int> tin, up, color, comp, stk;
int timer = 0, comp_col = 0;

void dfs(int v) {
    color[v] = 1;
    tin[v] = timer++;
    up[v] = tin[v];
    stk.push_back(v);
    for (int to : g[v]) {
        if (color[to] == 0) {
            dfs(to);
            up[v] = min(up[v], up[to]);
        } else if (color[to] == 1) {
            up[v] = min(up[v], tin[to]);
        } else if (comp[to] == -1) {
            up[v] = min(up[v], up[to]);
        }
    }
    if (up[v] >= tin[v]) {
        while (true) {
            int u = stk.back();
            stk.pop_back();
            comp[u] = comp_col;
            if (u == v) break;
        }
        ++comp_col;
    }
    color[v] = 2;
}
