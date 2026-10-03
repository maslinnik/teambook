/**
 * Author: Roman Pervutinskiy
 * Description: Modular arithmetic on int64_t.
 */

ll mul(ll a, ll b, ll mod) {
    return (__int128)a * b % mod;
}

ll binpow(ll x, ll n, ll mod) {
    ll res = 1 % mod;
    while (n > 0) {
        if (n & 1) res = mul(res, x, mod);
        x = mul(x, x, mod);
        n >>= 1;
    }
    return res;
}
