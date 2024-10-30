/**
 * Author: KACTL
 * Description: Pollard-rho randomized factorization algorithm. Returns prime factors of a number, in arbitrary order.
 * Time: O(n^{1/4}), less for numbers with small factors.
 */

ll pollard(ll n) {
    auto f = [n](ll x) { return mul(x, x, n) + 1; };
    ll x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    while (t++ % 40 || __gcd(prd, n) == 1) {
        if (x == y) x = ++i, y = f(x);
        if ((q = mul(prd, max(x,y) - min(x,y), n))) prd = q;
        x = f(x), y = f(f(y));
    }
    return __gcd(prd, n);
}

vector<ll> factor(ll n) {
    if (n == 1) return {};
    if (is_prime(n)) return {n};
    ll x = pollard(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), all(r));
    return l;
}
