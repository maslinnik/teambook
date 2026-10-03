#include <iostream>
#include <vector>

template<typename T>
std::istream& operator>>(std::istream& in, std::vector<T>& v) {
    for (auto& x : v) {
        in >> x;
    }
    return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    for (const auto& x : v) {
        out << x << ' ';
    }
    return out;
}
