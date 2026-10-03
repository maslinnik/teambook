/**
 * Author: Vladimir Ragulin
 * Description: Calculates middle-product of two arrays using Tellegen's principle.
 * Time: O(n \log n)
 */

vector<int> mulT(vector<int> a, vector<int> b) {
    int n = sz(a), m = sz(b), k = 1;
    while (k < n) k <<= 1;
    a.resize(k), b.resize(k);
    dft(a, k, true), dft(b, k);
    for (int i = 0; i < k; ++i) a[i] = mul(a[i], b[i]);
    dft(a, k);
    return {a.begin(), a.begin() + (n - m + 1)};
}
