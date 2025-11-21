// https://codeforces.com/problemset/problem/128/B

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int C = 26;
int m;

struct Node {
    inline static int timer = 0;

    array<Node*, C> nxt{};
    Node* par = nullptr;
    Node* suf = nullptr;

    // for multi-string automaton
    int last_used = -1;
    
    // more fields if you want
    bool is_terminal = false;
    ll cnt = 0;
    ll total = 0;
};

Node* root = new Node();

Node* add(Node* a, int ch) {
    Node* b = new Node();
    b->suf = root;
    b->par = a;
    while (a != nullptr) {
        if (a->nxt[ch] == nullptr) {
            a->nxt[ch] = b;
            a = a->suf;
            continue;
        }
        Node* c = a->nxt[ch];
        if (c->par == a) {
            b->suf = c;
            break;
        }
        Node* d = new Node();
        d->suf = c->suf;
        c->suf = d;
        b->suf = d;
        d->par = a;
        d->nxt = c->nxt;
        while (a != nullptr && a->nxt[ch] == c) {
            a->nxt[ch] = d;
            a = a->suf;
        }
        break;
    }
    return b->par->nxt[ch];
}

void visit_subautomaton(Node* v, auto&& cb = []{}) {
    if (v->last_used == Node::timer) {
        return;
    }
    v->last_used = Node::timer;
    cb(v);
    visit_subautomaton(v->par, cb);
    visit_subautomaton(v->suf, cb);
}

void dfs(Node* v) {
    v->last_used = Node::timer;
    v->cnt = v->is_terminal;
    for (int i = 0; i < C; ++i) {
        if (v->nxt[i] != nullptr) {
            if (v->nxt[i]->last_used != Node::timer) dfs(v->nxt[i]);
            v->cnt += v->nxt[i]->cnt;
        }
    }
}

void dfs2(Node* v) {
    v->last_used = Node::timer;
    v->total = v->cnt;
    for (int i = 0; i < C; ++i) {
        if (v->nxt[i] != nullptr) {
            if (v->nxt[i]->last_used != Node::timer) dfs2(v->nxt[i]);
            v->total += v->nxt[i]->total;
        }
    }
}

void find(Node* v, string& ans, ll& k) {
    if (k < v->cnt) {
        k = -1;
        return;
    }
    k -= v->cnt;
    for (int i = 0; i < C; ++i) {
        if (v->nxt[i] != nullptr) {
            if (k >= v->nxt[i]->total) {
                k -= v->nxt[i]->total;
            } else {
                ans += char('a' + i);
                find(v->nxt[i], ans, k);
                return;
            }
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    const auto start = clock();
#endif
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    string s;
    ll k;
    cin >> s >> k;
    k += s.size();
    Node* v = root;
    for (auto c : s) {
        v = add(v, c - 'a');
    }
    while (v != nullptr) {
        v->is_terminal = true;
        v = v->suf;
    }
    dfs(root);
    ++Node::timer;
    dfs2(root);
    string ans;
    find(root, ans, k);
    if (k != -1) {
        ans = "No such line.";
    }
    cout << ans << endl;
}