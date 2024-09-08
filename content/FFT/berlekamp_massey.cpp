vector<ll> BerlekampMassey(vector<ll> s) {//1, -c1, -c2, -c3, -c4, ..., -cn //tested
    int n = sz(s), L = 0, m = 0;
    vector<ll> c(n), b(n), t;
    c[0] = b[0] = 1;
    ll eval = 1;
    for (int i = 0; i < n; ++i) {
        ++m;
        ll delta = 0;
        for (int j = 0; j <= L; ++j) delta = (delta + c[j] * s[i - j]) % MOD;
        if (delta == 0) continue;
        t = c;
        ll coef = delta * inv(eval) % MOD;
        for (int j = m; j < n; ++j) c[j] = ((c[j] - coef * b[j - m]) % MOD + MOD) % MOD;
        if (2 * L > i) continue;
        L = i + 1 - L, m  = 0, b = t, eval = delta;
    }
    c.resize(L + 1);
    return c;
}
