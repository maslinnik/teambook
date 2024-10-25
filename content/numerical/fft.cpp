/**
 * Author: Vladimir Ragulin
 * Description: Applies the discrete Fourier transform to a sequence of numbers modulo \texttt{MOD}.
 * Time: O(n \log n)
 */

int rev[N], root[N];

void init(int n) {
    static int last_init = -1;
    if (n == last_init) return;
    last_init = n;
    for (int i = 1; i < n; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | (i & 1) * (n >> 1);
    }
    const int root_n = binpow(ROOT, (MOD - 1) / n);
    for (int i = 0, cur = 1; i < n / 2; ++i) {
        root[i + n / 2] = cur;
        cur = mul(cur, root_n);
    }
    for (int i = n / 2 - 1; i >= 0; --i) {
        root[i] = root[i << 1];
    }
}

void dft(int* f, int n, bool inverse = false) {
    init(n);
    for (int i = 0; i < n; ++i) {
        if (i < rev[i]) swap(f[i], f[rev[i]]);
    }
    for (int k = 1; k < n; k <<= 1)
        for (int i = 0; i < n; i += (k << 1))
            for (int j = 0; j < k; ++j) {
                int z = mul(f[i + j + k], root[j + k]);
                f[i + j + k] = sub(f[i + j], z);
                f[i + j] = add(f[i + j], z);
            }
    if (inverse) {
        reverse(f + 1, f + n);
        const int inv_n = inv(n);
        for (int i = 0; i < n; ++i) f[i] = mul(f[i], inv_n);
    }
}
