/**
 * Author: kactl
 * Description:  Chinese Remainder Theorem. \texttt{crt(a, m, b, n)} computes $x$ s.t. $x \equiv a \mod m, x \equiv b \mod n$.
 * Time:  $O(\log n)$
 */

ll crt(ll a, ll m, ll b, ll n) {
    if (n > m) swap(a, b), swap(m, n);
    ll x, y, g = exgcd(m, n, x, y);
    assert((a - b) % g == 0); // else no solution
    x = (b - a) % n * x % n / g * m + a;
    return x < 0 ? x + m * n / g : x;
}
