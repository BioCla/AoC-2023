#ifndef UTIL_HPP
#define UTIL_HPP

#include <complex>
#include <map>
#include <set>

inline std::complex<int> operator""_i(unsigned long long int x) { return {0, static_cast<int>(x)}; }
namespace std {
    inline bool operator<(const std::complex<int>& lhs, const std::complex<int>& rhs){return lhs.real() < rhs.real() || (lhs.real() == rhs.real() && lhs.imag() < rhs.imag());}
    inline std::complex<int> operator/(const std::complex<int> &lhs, const std::complex<int> &rhs) { return lhs * std::conj(rhs) / std::norm(rhs); }
}

int minimum_heat_dispersal(int min_steps, int max_steps, std::map<std::complex<int>, int> grid, int steps = 0);

#endif // UTIL_HPP