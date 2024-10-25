/**
 * Author: Vladimir Ragulin
 * Description: Calculates middle-product of two arrays using Tellegen's principle.
 * Time: O(n \log n)
 */

vector<int> mulT(const vector<int>& a, const vector<int>& b) {
    int n = sz(a), m = sz(b), k = 1;
    while (k < n) k <<= 1;
    fill_n(fft1, k, 0), fill_n(fft2, k, 0);
    copy(all(a), fft1), copy(all(b), fft2);
    dft(fft1, k, true), dft(fft2, k);
    for (int i = 0; i < k; ++i) fft1[i] = mul(fft1[i], fft2[i]);
    dft(fft1, k);
    return {fft1, fft1 + n - m + 1};
}