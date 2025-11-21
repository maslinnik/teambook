/**
 * Author: Vladimir Ragulin
 * Description: Calculates LCP array of the given string and its suffix array.
 * Time: O(n)
 */

vector<int> find_lcp(const string& s, const vector<int>& sa) {
    int n = sa.size();
    vector<int> pos(n), lcp(n);
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
    return lcp;
}