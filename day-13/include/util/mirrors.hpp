#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

class Complex {
  private:
    int _re;
    int _im;
  public:
    Complex(int re, int im) : _re(re), _im(im) {}
    int real() { return _re; }
    int imag() { return _im; }
    bool operator==(const Complex& other) const { return _re == other._re && _im == other._im; }
};

std::vector<std::vector<std::string>> subdivide_maps(std::vector<std::string> document);
int solve(std::vector<Complex> grid, int maxX, int maxY, bool part2 = false);
std::vector<Complex> make_complex(std::vector<std::string> map);

#endif // COMPLEX_HPP