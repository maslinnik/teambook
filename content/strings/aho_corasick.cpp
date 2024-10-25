/**
 * Author: Vladimir Ragulin
 * Description: Builds Aho-Corasick
 * Time: O(nC)
 */

const int C = 26;
struct node {
    int nx[C], first = -1, suff = -1;//, zsuff = -1;
    vector<int> idx;
    node() {
        fill(nx, nx + C, -1);
    }
};
vector<node> t(1);
void add_word(string& s, int id) {
    int v = 0;
    for (char ch : s) {
        int x = ch - 'a';
        if (t[v].nx[x] == -1) {
            t[v].nx[x] = sz(t);
            t.emplace_back();
        }
        v = t[v].nx[x];
    }
    t[v].idx.emplace_back(id);
}
void build_aho() {
    vector<pair<int, int>> q;
    for (int x = 0; x < C; ++x) {
        if (t[0].nx[x] == -1) {
            t[0].nx[x] = 0;
        } else {
            q.emplace_back(0, x);
        }
    }
    for (int st = 0; st < sz(q); ++st) {
        auto [par, x] = q[st];
        int a = t[par].nx[x];
        if (t[par].suff == -1) {
            t[a].suff = 0;
        } else {
            t[a].suff = t[t[par].suff].nx[x];
            // t[a].zsuff = t[t[a].suff].idx.empty() ? t[t[a].suff].zsuff : t[a].suff;
        }
        for (int y = 0; y < C; ++y) {
            if (t[a].nx[y] == -1) {
                t[a].nx[y] = t[t[a].suff].nx[y];
            } else {
                q.emplace_back(a, y);
            }
        }
    }
}