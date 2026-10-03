#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "prelude.h"
#include "vector_io.h"

#include "strings/kmp.h"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    auto z = zf(s);
    z[0] = sz(s);
    cout << z << '\n';
}
