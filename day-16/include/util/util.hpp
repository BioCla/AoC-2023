#ifndef UTIL_HPP
#define UTIL_HPP

#include <map>
#include <set>
#include <complex>

namespace std {
    inline bool operator<(const std::complex<int>& lhs, const std::complex<int>& rhs){return lhs.real() < rhs.real() || (lhs.real() == rhs.real() && lhs.imag() < rhs.imag());}
}

int energized(std::set<std::pair<std::complex<int>, std::complex<int>>> to_visit, std::map<std::complex<int>, char> grid);

#endif // UTIL_HPP