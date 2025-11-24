/**
 * Author: Vladimir Ragulin
 * Description: Applies Walsh-Hadamard transform
 * Time: O(2^n \cdot n)
 */

vector<int> f(1 << n);
for (int k = 0; k < n; ++k) {
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (~mask >> k & 1) {
            int u = f[mask], v = f[mask ^ (1 << k)];
            f[mask] = u + v;
            f[mask ^ (1 << k)] = u - v;
        }
    }
}
