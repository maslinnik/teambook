#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "prelude.h"
#include "vector_io.h"

#include "strings/suffix_array.h"

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	string s;
	cin >> s;
	auto sa = suffix_array(ranges::subrange(s.begin(), s.end() + 1));
	sa.erase(sa.begin());
	cout << sa << '\n';
}
