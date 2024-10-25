/**
 * Author: Vladimir Ragulin
 * Description: Calculates prefix function and Z-function of the given string.
 * Time: O(n)
 */

vector<int> pi(const string& s) {
	vector<int> p(sz(s));
	for (int i = 1; i < sz(s); ++i) {
		int g = p[i - 1];
		while (g && s[i] != s[g]) g = p[g - 1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

vector<int> zf(const string& s) {
	vector<int> z(sz(s));
	int l = -1, r = -1;
	for (int i = 1; i < sz(s); ++i) {
		z[i] = i >= r ? 0 : min(r - i, z[i - l]);
		while (i + z[i] < sz(s) && s[i + z[i]] == s[z[i]]) ++z[i];
		if (i + z[i] > r) l = i, r = i + z[i];
	}
	return z;
}