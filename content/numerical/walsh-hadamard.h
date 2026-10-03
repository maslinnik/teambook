/**
 * Author: Vladimir Ragulin
 * Description: Applies Walsh-Hadamard transform.
 * Time: O(n \log n)
 */

void walsh_hadamard(vector<int>& f) {
    int n = sz(f);
    for (int k = 1; k < n; k <<= 1) {
        for (int mask = 0; mask < n; ++mask) {
            if (!(mask & k)) {
                int u = f[mask], v = f[mask ^ k];
                f[mask] = add(u, v);
                f[mask ^ k] = sub(u, v);
            }
        }
    }
}
