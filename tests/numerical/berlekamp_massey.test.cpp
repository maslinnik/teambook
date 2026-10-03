#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"

#include "prelude.h"
#include "vector_io.h"

const int MOD = 998244353;

#include "number_theory/mod.h"
#include "numerical/berlekamp_massey.h"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    auto c = berlekamp_massey(a);
    c.erase(c.begin());
    for (int& x : c) x = sub(0, x);
    cout << sz(c) << '\n' << c << '\n';
}
