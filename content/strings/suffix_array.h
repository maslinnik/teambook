/**
 * Author: Vladimir Ragulin
 * Description: Sorts cyclic shifts of the given string. To get the actual suffix array, don't forget to push back a zero.
 * Usage: suffix_array(ranges::subrange(s.begin(), s.end() + 1)) // for suffix array of the std::string
 * Time: O((\max(s) - \min(s)) + n \log n)
 */

vector<int> suffix_array(const auto& s) {
    int n = s.size();
    auto [mn, mx] = minmax_element(s.begin(), s.begin() + n);
    vector<int> c(n), cur(n), sa(n), cnt(max<int>(*mx - *mn + 1, n) + 1);
    iota(sa.begin(), sa.end(), 0);
    for (int i = 0; i < n; ++i) {
        c[i] = s[i] - *mn + 1;
    }
    ranges::sort(sa, [&](int i, int j) { return c[i] < c[j]; });
    for (int k = 1; k < n; k <<= 1) {
        ranges::fill(cnt, 0);
        for (int x : c) cnt[x]++;
        for (int i = 1; i < cnt.size(); ++i) cnt[i] += cnt[i - 1];
        for (int i : sa) {
            i -= k;
            if (i < 0) i += n;
            int c2 = c[i] - 1;
            cur[cnt[c2]++] = i;
        }
        swap(cur, sa);
        int x = -1, y = -1, p = 0;
        for (int i : sa) {
            int nxt = i + k;
            if (nxt >= n) nxt -= n;
            if (c[i] != x || c[nxt] != y) {
                x = c[i], y = c[nxt], p++;
            }
            cur[i] = p;
        }
        swap(cur, c);
    }
    return sa;
}
