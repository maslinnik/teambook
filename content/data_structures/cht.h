/**
 * Author: Gleb Kostylev
 * Description: Stack-based convex hull trick.
 * Time: O(n)
 * Status: tested on Kalila & Dimna
 */

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