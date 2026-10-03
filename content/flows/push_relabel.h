/**
 * Author: Gleb Kostylev
 * Description: Finds maximum flow using push-relabel algorithm.
 * Time: O(n^3)
 * Status: AC on Zvenigorod camp
 */

const int N = 100;
const int S = N - 2;
const int T = N - 1;

struct Edge {
    int to, cap;
};

int n = N;
vector<int> gr[N];
vector<Edge> E;
int h[N], nxt[N], extra[N];

void add_edge(int from, int to, int cap_forw, int cap_back) {
    E.emplace_back(to, cap_forw);
    E.emplace_back(from, cap_back);
    gr[from].push_back(E.size() - 2);
    gr[to].push_back(E.size() - 1);
}

void push(int v, int i) {
    int val = min(extra[v], E[i].cap);
    E[i].cap -= val;
    E[i ^ 1].cap += val;
    extra[v] -= val;
    extra[E[i].to] += val;
}

void relabel(int v) {
    int mn = INF;
    for (auto i : gr[v]) {
        if (E[i].cap > 0) {
            mn = min(mn, h[E[i].to]);
        }
    }
    h[v] = mn + 1;
}

void discharge(int v) {
    while (extra[v]) {
        int i = gr[v][nxt[v]];
        if (E[i].cap > 0 && h[E[i].to] < h[v]) {
            push(v, i);
        }
        if (extra[v]) {
            nxt[v]++;
            if (nxt[v] == gr[v].size()) {
                nxt[v] = 0;
                relabel(v);
            }
        }
    }
}

int push_relabel() {
    fill_n(h, n, 0);
    fill_n(nxt, n, 0);
    extra[T] = 0;
    h[S] = n;
    for (auto i : gr[S]) {
        int val = E[i].cap;
        extra[E[i].to] += val;
        E[i].cap -= val;
        E[i ^ 1].cap += val;
    }
    for (int f = 1; f;) {
        f = 0;
        for (int i = 0; i < n; i++) {
            if (extra[i] && i != T && i != S) {
                f = 1;
                discharge(i);
            }
        }
    }
    return extra[T];
}