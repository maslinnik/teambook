#include <bits/stdc++.h>

using namespace std;

template <class T> ostream& operator<<(ostream& os, const vector<T>& a) {for (auto x : a) os << x << ' '; return os << endl;}

#include "../../content/strings/suffix_array.cpp"
#include "../../content/strings/linear_suffix_array.cpp"
#include "../../content/strings/lcp.cpp"

int main() {
    cerr << "Cyclic sorting" << endl;
    mt19937 gen(31);
    for (auto mx_size : {7, 20, 1000}) {
        for (auto mx : {2, 3, 4, 26}) {
            for (int i = 0; i < 100'000 / mx_size; ++i) {
                int n = gen() % mx_size + 1;
                string s;
                while (true) {
                    s.assign(n, 'a');
                    for (auto& c : s) {
                        c += gen() % mx;
                    }
                    set<string> shifts;
                    for (int i = 0; i < n; ++i) {
                        shifts.insert(s.substr(i) + s.substr(0, i));
                    }
                    if (shifts.size() == n) {
                        break;
                    }
                }
                vector<int> right_sa(n);
                iota(right_sa.begin(), right_sa.end(), 0);
                ranges::stable_sort(right_sa, [&](int i, int j) {
                    return s.substr(i) + s.substr(0, i) < s.substr(j) + s.substr(0, j);
                });
                vector<int> sa = suffix_array(s, false);
                if (right_sa != sa) {
                    cerr << "Wrong cyclic sorting" << endl << "Expected: " << right_sa << "Got: " << sa;
                    exit(1);
                }
            }
        }
    }
    cerr << "Cyclic sorting: Ok" << endl;
}