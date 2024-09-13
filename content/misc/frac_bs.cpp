/**
 * Author: Vladimir Ragulin
 * Description: Finds the smallest fraction $p / q \in [0, 1]$ s.t. $f(p / q)$ is true and $p, q \le N$.
 * Time: O(\log N)
 */

struct frac { ll p, q; };

frac fracBS(auto&& f, ll N) {
    bool dir = true, A = true, B = true;
    frac lo{0, 1}, hi{1, 1}; // Set hi to 1/0 to search (0, N]
    if (f(lo)) return lo;
    assert(f(hi));
    while (A || B) {
        ll adv = 0, step = 1;
        for (int si = 0; step; (step *= 2) >>= si) {
            adv += step;
            frac mid{lo.p * adv + hi.p, lo.q * adv + hi.q};
            if (abs(mid.p) > N || mid.q > N || dir == !f(mid)) {
                adv -= step; si = 2;
            }
        }
        hi.p += lo.p * adv;
        hi.q += lo.q * adv;
        dir = !dir;
        swap(lo, hi);
        A = B; B = !!adv;
    }
    return dir ? hi : lo;
}
