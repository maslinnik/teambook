#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include "prelude.h"

#include "strings/suffix_array.h"
#include "strings/lcp.h"

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    auto sa = suffix_array(s);
    auto lcp = find_lcp(s, sa);
    ll answer = (ll)sz(s) * (sz(s) + 1) / 2;
    for (int x : lcp) answer -= x;
    cout << answer << '\n';
}
