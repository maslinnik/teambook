/**
 * Author: Vladimir Ragulin
 * Description: Maintains palindromic tree with support of adding new symbols to the end.
 * Time: O(n)
 */

template<int C> struct EERTREE {
    int top = 1, last = 0, sz = 2;
    vector<int> str, suff, len;
    vector<array<int, C>> nx;

    EERTREE(int n) : str(n + 1, -1), suff(n + 2)
                    , len(n + 2), nx(n + 2, array<int, C>()) {
        len[1] = -1, suff[0] = 1;
    }
    int get_link(int v) {
        while (str[top - len[v] - 2] != str[top - 1]) v = suff[v];
        return v;
    }
    void add_letter(int c) {
        str[top++] = c;
        last = get_link(last);
        if (!nx[last][c]) {
            len[sz] = len[last] + 2;
            suff[sz] = nx[get_link(suff[last])][c];
            nx[last][c] = sz++;
        }
        last = nx[last][c];
    }
};