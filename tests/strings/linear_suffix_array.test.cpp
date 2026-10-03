#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "prelude.h"
#include "vector_io.h"

#include "strings/linear_suffix_array.h"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    auto sa = SA::suffix_sort(s);
    sa.erase(sa.begin());
    cout << sa << '\n';
}
