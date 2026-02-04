// https://judge.yosupo.jp/problem/range_reverse_range_sum

#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define endl '\n'
using namespace std;
using ll = int64_t;

struct Node { // Splay tree. Root's pp contains tree's parent.
    Node* p = 0;
    // Node* pp = 0; // comment if you don't need it
    array<Node*, 2> c{};

    bool flip = 0;
    int cnt = 1;
    ll me = 0;
    ll sum = 0;
    // more fields if wanted

    Node(ll v): me(v) {
        fix();
    }

    void fix() {
        cnt = 1;
        sum = me;
        for (auto& ch : c) {
            if (ch) {
                ch->p = this;
                cnt += ch->cnt;
                sum += ch->sum;
                // more if wanted
            }
        }
    }

    void pushFlip() {
        if (flip) {
            flip = 0;
            swap(c[0], c[1]);
            if (c[0]) c[0]->flip ^= 1;
            if (c[1]) c[1]->flip ^= 1;
        }
        // more mass updates if wanted
    }

    int up() {
        return p ? p->c[1] == this : -1;
    }

    void rot(int i, int b) {
        int h = i ^ b;
        Node *x = c[i], *y = b == 2 ? x : x->c[h], *z = b ? y : x;
        if ((y->p = p)) p->c[up()] = y;
        c[i] = z->c[i ^ 1];
        if (b < 2) {
            x->c[h] = y->c[h ^ 1];
            y->c[h ^ 1] = x;
        }
        z->c[i ^ 1] = this;
        fix(); x->fix(); y->fix();
        if (p) p->fix();
        // swap(pp, y->pp);
    }

    void splay() { // Splay this up to the root. Always finishes without flip set.
        for (pushFlip(); p; ) {
            if (p->p) p->p->pushFlip();
            p->pushFlip(); pushFlip();
            int c1 = up(), c2 = p->up();
            if (c2 == -1) p->rot(c1, 2);
            else p->p->rot(c2, c1 != c2);
        }
    }

    Node* first() { // Return the min element of the subtree rooted at this, splayed to the top.
        pushFlip();
        return c[0] ? c[0]->first() : (splay(), this);
    }
};

enum class side {
    left = 1, // sic
    right = 0,
};

Node* merge(Node* le, Node* ri) {
    if (ri == nullptr) return le;
    ri = ri->first();
    ri->c[0] = le;
    ri->fix();
    return ri;
}

// f: Node* -> side (all "left" nodes & their left subtrees will be in left tree)
pair<Node*, Node*> split(Node* v, auto&& f) {
    if (v == nullptr) return {nullptr, nullptr};
    Node* last;
    side last_side;
    while (v != nullptr) {
        v->pushFlip();
        last = v;
        last_side = f(v);
        v = v->c[(int)last_side];
    }
    last->splay();
    int i = (int)last_side;
    Node* cut = last->c[i];
    if (cut) cut->p = nullptr;
    last->c[i] = nullptr;
    last->fix();
    if (i) return {last, cut};
    return {cut, last};
}

// example
pair<Node*, Node*> split_k(Node* v, int k) {
    return split(v, [k](Node* v) mutable {
        int left_sz = v->c[0] ? v->c[0]->cnt : 0;
        if (left_sz >= k) {
            return side::right;
        }
        k -= left_sz + 1;
        return side::left;
    });
}

void solve() {
    int n, q;
    cin >> n >> q;
    Node* splay = nullptr;
    for (int i = 0; i < n; ++i) {
        ll x;
        cin >> x;
        Node* v = new Node(x);
        v->c[0] = splay;
        splay = v;
        splay->fix();
    }
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (l == r) {
            if (t == 1) {
                cout << 0 << endl;
            }
            continue;
        }
        auto [mid1, ri] = split_k(splay, r);
        auto [le, mid] = split_k(mid1, l);
        if (t == 0) {
            mid->flip = true;
            mid->pushFlip();
        } else {
            cout << mid->sum << endl;
        }
        splay = merge(merge(le, mid), ri);
    }
}

int main() {
#ifdef LOCAL
    freopen("../stream.in", "r", stdin);
    freopen("../stream.out", "w", stdout);
    auto start = clock();
#else
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int tt = 1;
    // cin >> tt;
    while (tt--) solve();
#ifdef LOCAL
    cerr << fixed << setprecision(3) << "TIME: " << 1e3 * (clock() - start) / CLOCKS_PER_SEC << " ms" << endl;
#endif
    return 0;
}
