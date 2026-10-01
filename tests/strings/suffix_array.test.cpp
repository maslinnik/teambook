#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include <bits/stdc++.h>
#include "strings/suffix_array.h"

using namespace std;

int main() {
	string s;
	cin >> s;
	auto sa = suffix_array(s);
	for (int x : sa | views::drop(1)) {
		cout << x << ' ';		
	}
	cout << '\n';
}
