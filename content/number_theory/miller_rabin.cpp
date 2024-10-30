/**
 * Author: KACTL
 * Description: Deterministic Miller-Rabin primality test. Guaranteed to work for numbers up to $7 \cdot 10^{18}$
 * Time: 7 times the complexity of $a^b \text{ mod } c$.
 */

bool is_prime(ll n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ll A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    ll s = __builtin_ctzll(n - 1), d = n >> s;
    for (ll a : A) {
        ll p = binpow(a % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--) 
            p = mul(p, p, n);
        if (p != n - 1 && i != s) return 0;
    }
    return 1;
}