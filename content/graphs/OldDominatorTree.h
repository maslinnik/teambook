/**
 * Author: Ilya Stepanov (probably)
 * Date: 2018-10-09
 * Source: https://codeforces.com/gym/100513/submission/44041205
 * Description: Finds dominators for all vertices in a graph for a given starting vertex.
 * Usage: Look at example(). Modify rmax if N > 1e6.
 * Time: O(M \log N)
 * Status: AC in basic problem about dominator trees
 */

class Dominator {
public:
	Dominator(vector<vector<int>> h, int s) {
		n = sz(h);
		newId.assign(n, -1);
		g = h;
		timer = 0;
		parent.resize(n);
		dfs(s);
		n = timer;
		vector<vector<int>> tmp(n);
		for (int i = 0; i < sz(newId); ++i) {
			if (newId[i] == -1) {
				continue;
			}
			for (int to : g[i]) {
				tmp[newId[i]].push_back(newId[to]);
			}
		}
		g.swap(tmp);
		gr.resize(n);
		for (int i = 0; i < n; ++i) {
			for (int to : g[i]) {
				gr[to].push_back(i);
			}
		}
		sdom.resize(n);
		label.resize(n);
		dsu.resize(n);
		for (int i = 0; i < n; ++i) {
			label[i] = i;
			dsu[i] = i;
		}
		for (int w = n - 1; w >= 0; --w) {
			sdom[w] = w;
			for (int v : gr[w]) {
				if (v < w) {
					sdom[w] = min(sdom[w], v);
				} else {
					pair<int, int> p = getDSU(v);
					sdom[w] = min(sdom[w], sdom[p.second]);
				}
			}
			if (w) {
				dsu[w] = parent[w];
			}
		}
		calcIdom();
	}
 
	void get(vector<int>& res1, vector<int>& res2) const {
		res1 = newId;
		res2 = idom;
	}
private:
	vector<int> newId;
	vector<vector<int>> g, gr;
	vector<int> sdom;
	vector<int> idom;
	int timer;
	const int rmax = 20;
	vector<vector<int>> shifts;
	vector<int> parent;
	vector<int> label;
	vector<int> dsu;
	vector<int> depth;
	int n;
 
	void dfs(int v) {
		newId[v] = timer++;
		for (int to : g[v]) {
			if (newId[to] == -1) {
				dfs(to);
				parent[newId[to]] = newId[v];
			}
		}
	}
 
	pair<int, int> getDSU(int v) {
		if (dsu[v] == v) {
			return {-1, -1};
		}
		pair<int, int> p = getDSU(dsu[v]);
		if (p.first == -1) {
			return {v, label[v]};
		}
		int u = p.second;
		if (sdom[u] < sdom[label[v]]) {
			label[v] = u;
		}
		dsu[v] = p.first;
		return {p.first, label[v]};
	}
 
	int lca(int u, int v) {
		if (depth[u] > depth[v]) {
			swap(u, v);
		}
		for (int r = rmax - 1; r >= 0; --r) {
			if (depth[v] - (1 << r) >= depth[u]) {
				v = shifts[r][v];
			}
		}
		assert(depth[u] == depth[v]);
		if (u == v) {
			return u;
		}
		for (int r = rmax - 1; r >= 0; --r) {
			if (shifts[r][u] != shifts[r][v]) {
				u = shifts[r][u];
				v = shifts[r][v];
			}
		}
		assert(u != v && shifts[0][u] == shifts[0][v]);
		return shifts[0][u];
	}
 
	void calcIdom() {
		idom.resize(n);
		depth.resize(n);
		shifts = vector<vector<int>>(rmax, vector<int>(n));
		for (int i = 0; i < n; ++i) {
			if (i == 0) {
				idom[i] = i;
				depth[i] = 0;
			} else {
				idom[i] = lca(parent[i], sdom[i]);
				depth[i] = depth[idom[i]] + 1;
			}
			shifts[0][i] = idom[i];
			for (int r = 0; r + 1 < rmax; ++r) {
				int j = shifts[r][i];
				shifts[r + 1][i] = shifts[r][j];
			}
		}
	}
};

void example() {
    vector<vector<int>> g(n);
    // ...
    Dominator D(g, starting_vertex);
    vector<int> newId, idom;
    D.get(newId, idom);
    for (int i = 0; i < sz(edges); ++i) {
    	int u = edges[i].first, v = edges[i].second;
        u = newId[u], v = newId[v];
        // ...
    }
}
