#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "prelude.h"
#include "vector_io.h"

#include "strings/suffix_array.h"

int main() {
	string s;
	cin >> s;
	auto sa = suffix_array(s);
	sa.erase(sa.begin());
	cout << sa << '\n';
}
