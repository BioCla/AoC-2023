#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <complex>

struct Instruction
{
    u_int direction;
    u_int64_t distance;
    std::string color;
};

std::vector<std::string> split(std::string str, std::string delimiter);

#endif // UTIL_HPP