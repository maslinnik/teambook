#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include "prelude.h"
#include "vector_io.h"

#include "strings/manacher.h"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    auto p = manacher(s);
    p = {p.begin() + 1, p.end() - 1};
    cout << p << '\n';
}
