/**
 * Author: Roman Pervutinskiy
 * Description: Fast reduction by arbitrary modulo. \texttt{Barrett(n).calc(x)} returns $x \bmod n$ for $x < n^2$.
 */

struct Barrett {
    constexpr Barrett(ull n) : n(n), r(UINT64_MAX / n) {}

    ull calc(ull x) const {
        ull q = (__uint128_t)x * r >> 64;
        q = x - q * n;
        if (q >= n) q -= n;
        return q;
    }

    ull n, r;
};