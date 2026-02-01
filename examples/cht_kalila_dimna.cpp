#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
#include <bits/stdc++.h>
#define sz(n) (int)(n).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define endl '\n'
using namespace std;
using ll = __int128;

const ll INF18 = 1'000'000'000'000'000'018;
const ll INF12 = 1'000'000'000'012;

struct Line {
    ll k;
    ll b;

    ll operator()(ll x) const {
        return k * x + b;
    }

    bool operator==(const Line&) const = default;
    strong_ordering operator<=>(const Line&) const = default;
};

Line& operator-=(Line& a, Line b) {
    a.k -= b.k;
    a.b -= b.b;
    return a;
}

template <class Better>
struct CHT {
    vector<Line> st;

    void add(Line l) {
        if (!st.empty() && st.back().k == l.k) {
            if (Better()(l.b, st.back().b)) {
                st.back() = l;
            }
            return;
        }
        while (st.size() >= 2) {
            Line l0 = st[st.size() - 2];
            Line l1 = st.back();
            Line l2 = l;
            l2 -= l0;
            l1 -= l0;
            if (l2.b * l1.k < l1.b * l2.k) {
                break;
            }
            st.pop_back();
        }
        st.push_back(l);
    }

    ll operator()(ll x) const {
        int l = 0, r = (int)st.size() - 1;
        while (r - l > 2) {
            int l1 = (l + l + r) / 3;
            int r1 = (l + r + r) / 3;
            ll v_l1 = st[l1](x);
            ll v_r1 = st[r1](x);
            if (Better()(v_l1, v_r1)) {
                r = r1;
            } else {
                l = l1;
            }
        }
        ll ans = st[l](x);
        for (int i = l + 1; i <= r; ++i) {
            ll v = st[i](x);
            if (Better()(v, ans)) {
                ans = v;
            }
        }
        return ans;
    }
};

template <class Comp>
void merge(const CHT<Comp>& a, const CHT<Comp>& b, CHT<Comp>& result) {
    vector<Line> st;
    st.reserve(a.st.size() + b.st.size());
    ranges::merge(views::reverse(a.st), views::reverse(b.st), back_inserter(st), Comp());
    CHT<Comp> ans;
    for (auto x : views::reverse(st)) {
        result.add(x);
    }
}

using MaxCHT = CHT<greater<>>;
using MinCHT = CHT<less<>>;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    vector<int> b(n);
    for (auto& x : b) cin >> x;
    vector<ll> dp(n);
    dp[0] = 0;
    MinCHT cht;
    cht.add({b[0], dp[0]});
    for (int i = 1; i < n; ++i) {
        dp[i] = cht(a[i]);
        cht.add({b[i], dp[i]});
    }
    cout << (int64_t)dp.back() << endl;
}

// void solve() {
//     vector<pair<int, MinCHT>> x;
//     int n;
//     cin >> n;
//     vector<int> a(n);
//     for (auto& x : a) cin >> x;
//     vector<int> b(n);
//     for (auto& x : b) cin >> x;
//     vector<ll> dp(n);
//     dp[0] = 0;
//     auto add = [&](Line l) {
//         MinCHT v;
//         v.add(l);
//         x.push_back({1, v});
//         while (x.size() >= 2 && x.back().first == x[x.size() - 2].first) {
//             auto v0 = x.back();
//             x.pop_back();
//             auto v1 = x.back();
//             x.pop_back();
//             x.emplace_back();
//             x.back().first = v0.first + 1;
//             merge(v0.second, v1.second, x.back().second);
//         }
//     };
//     add({b[0], dp[0]});
//     auto get = [&](ll p) {
//         ll ans = INF18;
//         for (auto& v : x) {
//             ans = min(ans, v.second(p));
//         }
//         return ans;
//     };
//     for (int i = 1; i < n; ++i) {
//         dp[i] = get(a[i]);
//         add({b[i], dp[i]});
//     }
//     cout << (int64_t)dp.back() << endl;
// }

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
