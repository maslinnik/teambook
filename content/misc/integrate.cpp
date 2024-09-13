/**
 * Author: Vladimir Ragulin
 * Description: Function integration over an interval using Simpson's rule. The error is proportional to $h^4$.
 */

double integrate(double a, double b, auto&& f, int n = 1000) {
    double h = (b - a) / 2 / n, rs = f(a) + f(b);
    for (int i = 1; i < n * 2; ++i) {
        rs += f(a + i * h) * (i & 1 ? 4 : 2);
    }
    return rs * h / 3;
}
