/**
 * Author: Some guy from yosupo
 * Description: Calculates suffix array of the given string.
 * Usage: SA::suffix_sort(s.size(), s.begin());
 * Time: Fastest
 * Source: https://judge.yosupo.jp/submission/296441
 */

#define For(i, j, k) for ( int i = (j) ; i <= (k) ; i++ )
#define Fol(i, j, k) for ( int i = (j) ; i >= (k) ; i-- )

namespace SA {
	template <class IT> inline void induced_sort(int n, int m, IT s, int o,
												   int *val, int *ty, int *cnt, int *sa) {
		int *c = cnt + m + 1; fill(sa, sa + n + 1, 0), copy(cnt, c, c);
		Fol(i, o, 0) sa[--c[s[val[i]]]] = val[i];
		copy(cnt, cnt + m, c + 1);
		For(i, 0, n) if ( sa[i] && !ty[sa[i] - 1] ) sa[c[s[sa[i] - 1]]++] = sa[i] - 1;
		copy(cnt, c, c);
		Fol(i, n, 0) if ( sa[i] &&  ty[sa[i] - 1] ) sa[--c[s[sa[i] - 1]]] = sa[i] - 1;
	}
	template <class IT> inline bool lms_equal(int x, int y, IT s, int *ty) {
		if ( s[x] != s[y] ) return false;
		while ( s[++x] == s[++y] && ty[x] == ty[y] ) if ( ty[x] == 2 ) return true;
		return false;
	}
	template <class IT> inline void sa_is(int n, int m, IT s, int *ty, int *lms, int *cnt, int *sa) {
		int o = -1, c = -1, *t = sa;
		ty[n] = 1; Fol(i, n - 1, 0) ty[i] = s[i] == s[i + 1] ? ty[i + 1] : s[i] < s[i + 1];
		fill(cnt, cnt + m + 1, 0); For(i, 0, n) cnt[s[i]]++; partial_sum(cnt, cnt + m + 1, cnt);
		For(i, 1, n) if ( !ty[i - 1] && ty[i] ) ty[i] = 2, lms[++o] = i;
		induced_sort(n, m, s, o, lms, ty, cnt, sa);
		For(i, 0, n) if ( ty[sa[i]] == 2 ) *t++ = sa[i];
		For(i, 0, o) c += c <= 0 || !lms_equal(sa[i], sa[i - 1], s, ty), t[sa[i] >> 1] = c;
		For(i, 0, o) t[i] = t[lms[i] >> 1];
		if ( c < o ) sa_is(o, c, t, ty + n + 1, lms + o + 1, cnt + m + 1, sa);
		else For(i, 0, o) sa[t[i]] = i;
		For(i, 0, o) lms[o + 1 + i] = lms[sa[i]];
		induced_sort(n, m, s, o, lms + o + 1, ty, cnt, sa);
	}
	vector<int> suffix_sort(const auto& str) {
		using T = std::decay_t<decltype(str[0])>;
		int n = str.size();
		auto s = str.begin();
        vector<T> t(n + 1);
		auto o = minmax_element(s, s + n); int d = *o.first - 1, m = *o.second - d;
		vector<int> ty(2 * (n + m + 2)), lms(n + 1), cnt(2 * (n + m + 2)), sa(n + 1);
		For(i, 0, n - 1) t[i] = s[i] - d; t[n] = 0;
		sa_is(n, m, t.data(), ty.data(), lms.data(), cnt.data(), sa.data()); For(i, 1, n) sa[i]++;
        for (auto& x : sa) --x;
		++sa[0];
        return sa;
	}
}
