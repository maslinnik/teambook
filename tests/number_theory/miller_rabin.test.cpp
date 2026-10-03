#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"

#include "prelude.h"
#include "vector_io.h"

#include "number_theory/mod64.h"
#include "number_theory/miller_rabin.h"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    cin >> q;
    while (q--) {
        ll n;
        cin >> n;
        cout << (is_prime(n) ? "Yes" : "No") << '\n';
    }
}
