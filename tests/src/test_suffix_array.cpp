#include <bits/stdc++.h>

using namespace std;

template <class T> ostream& operator<<(ostream& os, const vector<T>& a) {for (auto x : a) os << x << ' '; return os << endl;}

#include "../../content/strings/suffix_array.cpp"
#include "../../content/strings/linear_suffix_array.cpp"
#include "../../content/strings/lcp.cpp"

int main() {
    cerr << "Suffix array and LCP" << endl;
    mt19937 gen(31);
    for (auto mx_size : {7, 20, 1000}) {
        for (auto mx : {1, 2, 3, 4, 26}) {
            for (int i = 0; i < 100'000 / mx_size; ++i) {
                int n = gen() % mx_size + 1;
                string s(n, 'a');
                for (auto& c : s) {
                    c += gen() % mx;
                }
                vector<int> right_sa(n + 1);
                iota(right_sa.begin(), right_sa.end(), 0);
                ranges::sort(right_sa, [&](int i, int j) {
                    return s.substr(i) < s.substr(j);
                });
                vector<int> nlog_sa = suffix_array(s);
                vector<int> linear_sa = SA::suffix_sort(s);
                for (const auto& sa : {nlog_sa, linear_sa}) {
                    if (right_sa != sa) {
                        cerr << "Wrong suffix array" << endl << "Expected: " << right_sa << "Got: " << sa;
                        exit(1);
                    }
                }
                vector<int> lcp = find_lcp(s, right_sa);
                vector<int> right_lcp(n + 1);
                for (int i = 0; i < n; ++i) {
                    while (s[right_sa[i] + right_lcp[i]] == s[right_sa[i + 1] + right_lcp[i]]) {
                        ++right_lcp[i];
                    }
                }
                if (right_lcp != lcp) {
                    cerr << "Wrong LCP" << endl << "Expected: " << right_lcp << "Got: " << lcp;
                    exit(1);
                }
            }
        }
    }
    cerr << "Suffix array and LCP: Ok" << endl;
}