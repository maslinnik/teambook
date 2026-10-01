#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "prelude.h"
#include "io.h"
const int MOD = 998244353, ROOT = 3;
const int N = 1 << 20;
#include "mod.h"
#include "numerical/fft.h"
#include "mul.h"

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    cin >> a >> b;
    auto c = mul(a, b);
    cout << c << '\n';
}
