/**
 * Author: Vladimir Ragulin
 * Description: Calculates suffix array, inverse suffix array and LCP array of the given string.
 * Time: O(n \log n)
 */

const int M = 1e5 + 10;
vector<int> sa, pos, lcp;

void suffix_array(string& s) {
    int n = sz(s);
    vector<int> c(n), cur(n);
    sa.resize(n), pos.resize(n), lcp.resize(n);
    for (int i = 0; i < n; ++i) {
        sa[i] = i, c[i] = s[i];
    }
    sort(all(sa), [&](int i, int j) { return c[i] < c[j]; });
    vector<int> cnt(M);
    for (int k = 1; k < n; k <<= 1) {
        fill(all(cnt), 0);
        for (int x : c) cnt[x]++;
        for (int i = 1; i < M; ++i) cnt[i] += cnt[i - 1];
        for (int i : sa) {
            int c2 = c[(i - k + n) % n] - 1;
            cur[cnt[c2]++] = (i - k + n) % n;
        }
        swap(cur, sa);
        int x = -1, y = -1, p = 0;
        for (int i : sa) {
            if (c[i] != x || c[(i + k) % n] != y) {
                x = c[i], y = c[(i + k) % n], p++;
            }
            cur[i] = p;
        }
        swap(cur, c);
    }
    for (int i = 0; i < n; ++i) pos[sa[i]] = i;
    int l = 0;
    for (int i = 0; i < n; ++i) {
        if (pos[i] == n - 1) {
            l = 0;
        } else {
            while (s[(i + l) % n] == s[(sa[pos[i] + 1] + l) % n]) ++l;
            lcp[pos[i]] = l;
            l = max(0, l - 1);
        }
    }
}