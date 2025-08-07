/**
 * Author: Roman Pervutinskiy
 * Source: https://asfjwd.github.io/2020-04-24-floor-sum-ap/
 * Description: Calculates a tuple containing $f(a, b, c, n)$, $g(a, b, c, n)$ and $h(a, b, c, n)$.
 * Time: O(\log C)
 */

tuple<ll, ll, ll> floor_sum(ll a, ll b, ll c, ll n) {
    if (a == 0) {
        return {
                mul(n + 1, b / c),
                mul(b / c, n, n + 1, INV_2),
                mul(n + 1, b / c, b / c)
        };
    }
    if (a >= c || b >= c) {
        auto [f, g, h] = get(a % c, b % c, c, n);
        return {
                (f + mul(n, n + 1, INV_2, a / c) + mul(n + 1, b / c)) % MOD,
                (g + mul(a / c, n, n + 1, 2 * n + 1, INV_6) + mul(b / c, n, n + 1, INV_2)) % MOD,
                (h + 2 * mul(b / c, f) + 2 * mul(a / c, g) + mul(a / c, a / c, n, n + 1, 2 * n + 1, INV_6) + mul(b / c, b / c, n + 1) + mul(a / c, b / c, n, n + 1)) % MOD
        };
    }
    ll m = (a * n + b) / c;
    auto [f, g, h] = get(c, c - b - 1, a, m - 1);
    return {
            (mul(m, n) + MOD - f) % MOD,
            mul((mul(m, n, n + 1) + MOD * 2ll - f - h) % MOD, INV_2),
            (mul(n, m, m) + MOD * 3ll - f - 2 * g) % MOD
    };
}