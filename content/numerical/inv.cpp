/**
 * Author: Roman Pervutinskiy
 * Description: Finds first $n$ coefficients of $1/a$ modulo \texttt{MOD}.
 * Time: O(n \log n)
 */

vector<int> inv(vector<int> a, int n) {
    assert(a[0] != 0);
    vector res{inv(a[0])};
    for (int k = 1; k < n; k <<= 1) {
        auto tmp = mul(res, res);
        if ((int)tmp.size() > n) {
            tmp.resize(n);
        }
        tmp = mul(tmp, {a.begin(), a.begin() + min(2 * k, sz(a))});
        tmp.resize(2 * k);
        for (int i = 0; i < k; ++i) {
            tmp[i] = sub(add(res[i], res[i]), tmp[i]);
            tmp[k + i] = sub(0, tmp[k + i]);
        }
        res.swap(tmp);
    }
    res.resize(n);
    return res;
}
