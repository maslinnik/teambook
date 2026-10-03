#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include "prelude.h"
#include "vector_io.h"

const int MOD = 998244353, ROOT = 3;
const int N = 1 << 20;

#include "number_theory/mod.h"
#include "numerical/fft.h"
#include "numerical/mul.h"
#include "numerical/inv.h"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    cout << inv(a, n) << '\n';
}
