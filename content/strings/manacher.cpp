/**
 * Author: Gleb Kostylev
 * Description: Manacher's algorithm
 * Time: O(n)
 * Source: https://judge.yosupo.jp/submission/265135
 */

vector<int> manacher(const std::string& s) {
    int n = s.size();
    vector<int> res(2 * n + 1);
    int longest = 0, root_longest = 0;
    for (int i = 1; i < 2 * n + 1; ++i) {
        int pal;
        if (i > longest) {
            pal = 1;
        } else {
            pal = min(longest - i, res[2 * root_longest - i]);
        }
        while (pal < i && i + pal < 2 * n && s[(i - pal - 2) / 2] == s[(i + pal) / 2]) {
            pal += 2;
        }
        res[i] = pal;
        if (i + pal > longest) {
            longest = i + pal;
            root_longest = i;
        }
    }
    return res;
}
