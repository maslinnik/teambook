/**
 * Author: Vladimir Ragulin
 * Description: Returns the polynomial of a recurrent sequence of order $n$ from the first $2n$ terms.
 * Usage: berlekamp_massey({0, 1, 1, 3, 5, 11}) // {1, -1, -2}
 * Time: O(n^2)
 */

vector<int> berlekamp_massey(vector<int> s) {
    int n = sz(s), L = 0, m = 0;
    vector<int> c(n), b(n), t;
    c[0] = b[0] = 1;
    int eval = 1;
    for (int i = 0; i < n; ++i) {
        m++;
        int delta = 0;
        for (int j = 0; j <= L; ++j) {
            delta = add(delta, mul(c[j], s[i - j]));
        }
        if (delta == 0) continue;
        t = c;
        int coef = mul(delta, inv(eval));
        for (int j = m; j < n; ++j) {
            c[j] = sub(c[j], mul(coef, b[j - m]));
        }
        if (2 * L > i) continue;
        L = i + 1 - L, m = 0, b = t, eval = delta;
    }
    c.resize(L + 1);
    return c;
}
