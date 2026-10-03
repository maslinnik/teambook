/**
 * Author: Roman Pervutinskiy
 * Description: Rotates the given string until it is lexicographically minimal, returns shift.
 * Time: O(n)
 * Source: http://e-maxx.ru/algo/duval_algorithm
 */

int min_rotation(string& s, int len) {
    s += s;
    int i = 0, ans = 0;
    while (i < len) {
        ans = i;
        int j = i + 1, k = i;
        while (j < len * 2 && s[k] <= s[j]) {
            if (s[k] < s[j]) {
                k = i;
            } else {
                k += 1;
            }
            j += 1;
        }
        while (i <= k) {
            i += j - k;
        }
    }
    s = s.substr(ans, len);
    return ans;
}