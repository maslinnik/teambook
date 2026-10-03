#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_xor_convolution"

#include "prelude.h"
#include "vector_io.h"

const int MOD = 998244353;

#include "number_theory/mod.h"
#include "numerical/walsh_hadamard.h"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    int size = 1 << n;
    vector<int> a(size), b(size);
    cin >> a >> b;
    walsh_hadamard(a);
    walsh_hadamard(b);
    for (int i = 0; i < size; ++i) a[i] = mul(a[i], b[i]);
    walsh_hadamard(a);
    int inv_size = inv(size);
    for (int& x : a) x = mul(x, inv_size);
    cout << a << '\n';
}
