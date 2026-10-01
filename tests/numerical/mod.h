int add(int a, int b) {
    return a + b < MOD ? a + b : a + b - MOD;
}

int sub(int a, int b) {
    return add(a, MOD - b);
}

int mul(auto... a) {
    ll res = 1;
    return ((res = res * a % MOD), ...);
}

int binpow(int x, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) {
            res = mul(res, x);
        }
        x = mul(x, x);
        n /= 2;
    }
    return res;
}

int inv(int x) {
    return binpow(x, MOD - 2);
}
