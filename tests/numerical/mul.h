vector<int> mul(vector<int> a, vector<int> b) {
    int n = sz(a), m = sz(b), k = 1;
    while (k < n + m - 1) k <<= 1;
    a.resize(k), b.resize(k);
    dft(a, k), dft(b, k);
    for (int i = 0; i < k; ++i) a[i] = mul(a[i], b[i]);
    dft(a, k, true);
    return {a.begin(), a.begin() + (n + m - 1)};
}
