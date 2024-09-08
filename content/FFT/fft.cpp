
const int N = 1 << 21;
const int MOD = 998244353, GROOT = 62;// 3
//(5 << 25) + 1, GROOT = 62// 3
//(7 << 26 + 1), GROOT = 62// 3
//(479 << 21) + 1, GROOT = 62// 3
//(483 << 21) + 1, GROOT = 62
int rev[N], root[N];
void init(int n ) {
    static int last_init = -1;
    if (n == last_init) return;
    last_init = n;
    for (int i = 1; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | (i & 1) * (n >> 1);
    const int R2 = binpow(GROOT, (MOD - 1) / n);
    for (int i = 0, cur = 1; i < n / 2; ++i, cur = mul(cur, R2)) root[i + n / 2] = cur;
    for (int i = n / 2 - 1; i >= 0; --i) root[i] = root[i << 1];
}

int fft1[N], fft2[N];

void dft(int* f, int n, bool inverse = false) {
    init(n);
    for (int i = 0; i < n; ++i) if (i < rev[i]) swap(f[i], f[rev[i]]);
    for (int k = 1; k < n; k <<= 1) for (int i = 0; i < n; i += (k << 1)) for (int j = 0; j < k; ++j) {
        int z = mul(f[i + j + k], root[j + k]);
        f[i + j + k] = add(f[i + j], MOD - z);
        f[i + j] = add(f[i + j], z);
    }
    if (inverse) {
        reverse(f + 1, f + n);
        const int invn = inv(n);
        for (int i = 0; i < n; ++i) f[i] = mul(f[i], invn);
    }
}
