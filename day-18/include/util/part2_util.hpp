#ifndef PART_2_UTIL_HPP
#define PART_2_UTIL_HPP

#include "util.hpp"

std::vector<Instruction> parse_instructions2(std::vector<std::string> document);
std::vector<std::complex<int64_t>> get_points(std::vector<Instruction> instructions);
u_int64_t shoelace(std::vector<std::complex<int64_t>> points);

#endif // PART_2_UTIL_HPP